/*
	MIT License

	Copyright (c) 2021 Scribe Language Repositories

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"), to
	deal in the Software without restriction, including without limitation the
	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#include <cassert>
#include <cinttypes>

#include "Error.hpp"
#include "parser/Stmts.hpp"
#include "parser/TypeMgr.hpp"

#define CHECK_VALUE(x) (x && x->vtyp && x->vtyp->val && x->vtyp->val->type != VUNKNOWN)

namespace sc
{
namespace parser
{
// TODO: add a macro to each assign_type function that checks if vtyp is already set
// don't add this macro to a function where vtyp has no relevance (continue, break)
static bool init_templ_func(TypeMgr &types, Stmt *lhs, const std::vector<Type *> &calltemplates,
			    const bool &comptime)
{
	if(calltemplates.empty() && !comptime) return true;
	// TODO: handle comptime
	assert(lhs->vtyp && "LHS has no vtype assigned!");
	// if this function has no definition (template intrinsic, extern, for example)
	// do nothing
	if(!lhs->vtyp->parent) return true;
	Stmt *templfnparent = lhs->vtyp->parent->get_parent_with_type(BLOCK);
	TypeFunc *origsig   = static_cast<TypeFunc *>(lhs->vtyp);
	if(!templfnparent) {
		err::set(lhs->line, lhs->col,
			 "function definition for specialization is not in a block!");
		return false;
	}
	Stmt *fndefvar = lhs->vtyp->parent->get_parent_with_type(VAR);
	if(!fndefvar) {
		err::set(lhs->line, lhs->col,
			 "could not find function definition's variable declaration!");
		return false;
	}
	fndefvar     = fndefvar->copy(false, false);
	StmtVar *var = as<StmtVar>(fndefvar);
	assert(var->val && var->val->type == FNDEF && var->val &&
	       "expected function definition as variable value for template initialization");
	StmtFnDef *fn = as<StmtFnDef>(var->val);
	if(!fn->blk) {
		delete fndefvar;
		return false;
	}
	if(types.current_src() == fn->src_id) {
		types.lock_scopes_before(origsig->scope);
	} else {
		types.pushsrc(fn->src_id);
	}
	types.pushlayer();
	types.pushfunc(origsig);
	// for each types add signature variables
	for(size_t i = 0; i < fn->sig->templates.size(); ++i) {
		const std::string &t = fn->sig->templates[i].data.s;
		Type *cp	     = calltemplates[i]->copy();
		cp->set_all_val(types.get(VUNKNOWN));
		types.add(t, cp);
	}
	fn->sig->templates.clear();
	fn->sig->comptime = false;
	if(origsig->args.size() > 0 && origsig->args.back()->type == TVARIADIC) {
		std::string tname = fn->sig->params.back()->vtype->getname();
		types.add_copy(tname, origsig->args.back());
	}
	for(size_t i = 0; i < fn->sig->params.size(); ++i) {
		types.add_copy(fn->sig->params[i]->name.data.s, origsig->args[i]);
	}
	// sig and blk must be separately assigned as variables added above will be shadowed
	// by new layer created in fn->assign_type()
	if(!fn->sig->assign_type(types)) {
		delete fndefvar;
		return false;
	}
	if(!fn->blk->assign_type(types)) {
		err::set(lhs->line, lhs->col,
			 "failed to specialize template function definition: %s",
			 lhs->vtyp->str().c_str());
		delete fndefvar;
		return false;
	}
	fn->vtyp = fn->sig->vtyp->copy();
	if(comptime) {
		// TODO: execute comptime() here
	}
	fn->sig->comptime = comptime;
	fn->sig->templates.clear();
	types.popfunc();
	types.poplayer();
	if(types.current_src() == fn->src_id) {
		types.unlock_scope();
	}
	var->is_specialized = true;

	// lhs must point to correct vtyp
	delete lhs->vtyp;
	lhs->vtyp	  = fn->vtyp->copy();
	lhs->vtyp->parent = lhs;

	StmtBlock *tfnparent = static_cast<StmtBlock *>(templfnparent);
	tfnparent->stmts.push_back(var);
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBlock::assign_type(TypeMgr &types)
{
	types.pushlayer();
	for(size_t i = 0; i < stmts.size(); ++i) {
		auto &s = stmts[i];
		if(s->is_specialized) continue;
		if(!s->assign_type(types)) {
			err::set(s->line, s->col,
				 "failed to perform type analysis on this statement");
			return false;
		}
	}
	if(parent) types.poplayer(); // do not remove the top layer if this block is top level
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtType::assign_type(TypeMgr &types)
{
	std::vector<Type *> resolvabletemplates;
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) {
			Type *v = types.get(templates[i].data.s, this);
			resolvabletemplates.push_back(v);
			continue;
		}
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, nullptr, tname));
	}
	if(func) {
		if(!fn->assign_type(types)) {
			err::set(line, col, "failed to determine type from the function type");
			return false;
		}
		vtyp = fn->vtyp->copy();
		return true;
	}
	Type *res = nullptr;
	if(info & VARIADIC && (res = types.get(this->getname(), nullptr))) {
		vtyp	   = res->copy();
		vtyp->info = info;
		vtyp->ptr += ptr;
		vtyp->info &= ~VARIADIC;
		return res;
	}
	res = types.get(name.front().data.s, this);
	if(res == nullptr) {
		err::set(name.front(), "variable '%s' does not exist", name.front().data.s.c_str());
		return false;
	}
	for(size_t i = 1; i < name.size(); ++i) {
		if(res->type != TSTRUCT) {
			err::set(name[i - 1], "expected this to be a struct, found: '%s'",
				 res->str().c_str());
			return false;
		}
		res = ((TypeStruct *)res)->get_field(name[i].data.s);
		if(!res) {
			err::set(name[i], "variable '%s' does not exist", name[i].data.s.c_str());
			return false;
		}
	}
	if(resolvabletemplates.empty()) {
		vtyp = res->copy();
	} else {
		vtyp = res->specialize(resolvabletemplates);
	}
	vtyp->info = info;
	vtyp->ptr += ptr;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtSimple ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtSimple::assign_type(TypeMgr &types)
{
	if(CHECK_VALUE(this)) return true;
	switch(val.tok.val) {
	case lex::VOID: vtyp = types.get_copy("void", this); break;
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL: vtyp = types.get_copy("i1", this); break;
	case lex::INT: vtyp = types.get_copy("i32", this); break;
	case lex::FLT: vtyp = types.get_copy("f32", this); break;
	case lex::CHAR: vtyp = types.get_copy("u8", this); break;
	case lex::STR: vtyp = types.get_copy("*const u8", this); break;
	case lex::IDEN: vtyp = types.get_copy(val.data.s, this); return vtyp;
	default: return false;
	}
	if(!vtyp) {
		err::set(val, "failed to determine type of this statement");
		return false;
	}
	switch(val.tok.val) {
	case lex::VOID: vtyp->val = types.get(VVOID); break;
	case lex::TRUE: vtyp->val = types.get((int64_t)1); break;
	case lex::FALSE: // fallthrough
	case lex::NIL: vtyp->val = types.get((int64_t)0); break;
	case lex::INT: vtyp->val = types.get(val.data.i); break;
	case lex::FLT: vtyp->val = types.get((double)val.data.f); break;
	case lex::CHAR: vtyp->val = types.get((int64_t)val.data.s[0]); break;
	case lex::STR: vtyp->val = types.get(val.data.s); break;
	// no need of lex::IDEN here as value is in vtyp itself
	default: return false;
	}
	return vtyp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnCallInfo::assign_type(TypeMgr &types)
{
	types.pushlayer();
	for(auto &t : templates) {
		if(!t->assign_type(types)) {
			err::set(t->line, t->col, "failed to determine type of template");
			return false;
		}
	}
	for(auto &a : args) {
		if(!a->assign_type(types)) {
			err::set(a->line, a->col, "failed to determine type of argument");
			return false;
		}
	}
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExpr::assign_type(TypeMgr &types)
{
	if(lhs && !lhs->assign_type(types)) {
		err::set(lhs->line, lhs->col, "failed to determine type of LHS");
		return false;
	}
	if(oper.tok.val != lex::DOT && oper.tok.val != lex::ARROW && rhs &&
	   !rhs->assign_type(types)) {
		err::set(rhs->line, rhs->col, "failed to determine type of RHS");
		return false;
	}
	// TODO: or-var & or-blk
	switch(oper.tok.val) {
	case lex::ARROW:
		if(lhs->vtyp->ptr == 0) {
			err::set(line, col, "arrow operator only works for pointer types");
			return false;
		}
	case lex::DOT: {
		assert(rhs->type == SIMPLE && "RHS for dot/arrow MUST be a simple type");
		if(lhs->vtyp->type != TSTRUCT) {
			err::set(line, col,
				 "LHS must be a structure to use the dot operator, found: %s",
				 lhs->vtyp->str().c_str());
			return false;
		}
		TypeStruct *lst = static_cast<TypeStruct *>(lhs->vtyp);
		if(lst->is_def) {
			err::set(line, col,
				 "cannot use dot operator on a struct"
				 " definition; instantiate it first");
			return false;
		}
		StmtSimple *rsim = static_cast<StmtSimple *>(rhs);
		size_t ptr	 = lst->ptr;
		if(oper.tok.val == lex::ARROW) --ptr;
		Type *res = ptr == 0 ? lst->get_field(rsim->val.data.s) : nullptr;
		if(!res && !(res = types.get_funcmap_copy(rsim->val.data.s, this))) {
			err::set(line, col,
				 "no function or struct field (in '%s') named '%s' exists",
				 lst->str().c_str(), rsim->val.data.s.c_str());
			return false;
		}
		rhs->vtyp	  = res;
		rhs->vtyp->parent = rhs;
		vtyp		  = res->copy();
		vtyp->parent	  = this;
		break;
	}
	case lex::FNCALL: {
		assert(rhs && rhs->type == FNCALLINFO &&
		       "RHS for function call must be a call info (compiler failure)");
		StmtFnCallInfo *finfo = static_cast<StmtFnCallInfo *>(rhs);
		std::vector<Type *> calltemplates;
		bool comptime = false;
		if(lhs->vtyp->type != TFUNC && lhs->vtyp->type != TSTRUCT &&
		   lhs->vtyp->type != TFUNCMAP) {
			err::set(lhs->line, lhs->col,
				 "function call can be performed "
				 "only on a function or struct type, attempted on: %s",
				 lhs->vtyp->str().c_str());
			return false;
		}
		if(lhs->vtyp->type == TFUNCMAP) {
			TypeFuncMap *fmap = static_cast<TypeFuncMap *>(lhs->vtyp);
			if(!(vtyp = fmap->decide_func(finfo, calltemplates))) {
				err::set(line, col,
					 "failed to decide the function "
					 "to execute, need more info");
				return false;
			}
			delete lhs->vtyp;
			lhs->vtyp = vtyp;
			comptime  = static_cast<TypeFunc *>(vtyp)->comptime;
			vtyp	  = static_cast<TypeFunc *>(lhs->vtyp)->rettype->copy();
		} else if(lhs->vtyp->type == TFUNC) {
			TypeFunc *oldfn = static_cast<TypeFunc *>(lhs->vtyp);
			TypeFunc *fn	= nullptr;
			if(!(fn = oldfn->specialize_compatible_call(finfo, calltemplates))) {
				err::set(line, col,
					 "function '%s' incompatible with call arguments",
					 oldfn->str().c_str());
				return false;
			}
			delete oldfn;
			lhs->vtyp = fn;
			if(vtyp) delete vtyp;
			vtyp = fn->rettype->copy();
			if(fn->intrin_fn && !fn->call_intrinsic(types, this, fn, finfo)) {
				err::set(line, col,
					 "failed to call intrinsic "
					 "function during type assignment");
				return false;
			}
			comptime = fn->comptime;
		} else if(lhs->vtyp->type == TSTRUCT) {
			TypeStruct *st = static_cast<TypeStruct *>(lhs->vtyp);
			if(!st->is_def) {
				err::set(line, col,
					 "only structure definitions can be called (instantiated)");
				return false;
			}
			// call the <struct>() function
			// maybe <struct>.init() in future if required
			if(!(vtyp = st->specialize_compatible_call(finfo, calltemplates))) {
				err::set(line, col,
					 "failed to instantiate struct with given arguments");
				return false;
			}
			delete lhs->vtyp;
			lhs->vtyp = vtyp;
			vtyp	  = lhs->vtyp->copy();
			break; // no need to clone the struct
		}
		// apply stmt template specialization
		if(!init_templ_func(types, lhs, calltemplates, comptime)) return false;
		break;
	}
	case lex::SUBS: {
		if(lhs->vtyp->type == TVARIADIC) {
			bool found_compat = false;
			for(auto &bn : basenumtypes()) {
				if(rhs->vtyp->compatible(types.get(bn, this), line, col)) {
					found_compat = true;
					break;
				}
			}
			err::reset();
			if(!found_compat) {
				err::set(line, col,
					 "variadics can only take one of the "
					 "primitive numeric types (as index), found: %s",
					 rhs->vtyp->str().c_str());
				return false;
			}
			if(!CHECK_VALUE(rhs) || rhs->vtyp->val->type != VINT) {
				err::set(line, col,
					 "variadic subscript expression MUST be an integral value "
					 "that can be determined at compile time");
				return false;
			}
			TypeVariadic *va   = static_cast<TypeVariadic *>(lhs->vtyp);
			const int64_t &idx = rhs->vtyp->val->i;
			if(va->args.size() <= idx) {
				err::set(line, col, "variadic index '" PRId64 "' out of bounds",
					 idx);
				return false;
			}
			vtyp = va->args[idx]->copy();
			break;
		}
		if(lhs->vtyp->ptr > 0) {
			bool found_compat = false;
			for(auto &bn : basenumtypes()) {
				if(rhs->vtyp->compatible(types.get(bn, this), line, col)) {
					found_compat = true;
					break;
				}
			}
			if(!found_compat) {
				err::set(line, col,
					 "pointer subscript can only take one of the "
					 "primitive numeric types (as index), found: %s",
					 rhs->vtyp->str().c_str());
				return false;
			}
			vtyp = lhs->vtyp->copy();
			--vtyp->ptr;
			break;
		}
		err::set(line, col, "unimplemented subscript for type: %s",
			 lhs->vtyp->str().c_str());
		return false;
	}
	// address of
	case lex::UAND: {
		vtyp = lhs->vtyp->copy();
		++vtyp->ptr;
		break;
	}
	// dereference
	case lex::UMUL: {
		if(lhs->vtyp->ptr == 0) {
			err::set(line, col, "cannot dereference non pointer type: %s",
				 lhs->vtyp->str().c_str());
			return false;
		}
		vtyp = lhs->vtyp->copy();
		--vtyp->ptr;
		break;
	}
	case lex::ASSN: {
		Stmt *store = lhs;
		lhs	    = rhs;
		rhs	    = store;
	}
	// Arithmetic
	case lex::ADD:
	case lex::SUB:
	case lex::MUL:
	case lex::DIV:
	case lex::MOD:
	case lex::ADD_ASSN:
	case lex::SUB_ASSN:
	case lex::MUL_ASSN:
	case lex::DIV_ASSN:
	case lex::MOD_ASSN:
	// Post/Pre Inc/Dec
	case lex::XINC:
	case lex::INCX:
	case lex::XDEC:
	case lex::DECX:
	// Unary
	case lex::UADD:
	case lex::USUB:
	// Logic
	case lex::LAND:
	case lex::LOR:
	case lex::LNOT:
	// Comparison
	case lex::EQ:
	case lex::LT:
	case lex::GT:
	case lex::LE:
	case lex::GE:
	case lex::NE:
	// Bitwise
	case lex::BAND:
	case lex::BOR:
	case lex::BNOT:
	case lex::BXOR:
	case lex::BAND_ASSN:
	case lex::BOR_ASSN:
	case lex::BNOT_ASSN:
	case lex::BXOR_ASSN:
	// Others
	case lex::LSHIFT:
	case lex::RSHIFT:
	case lex::LSHIFT_ASSN:
	case lex::RSHIFT_ASSN: {
		if(lhs->vtyp->type != TSIMPLE && lhs->vtyp->type != TSTRUCT) {
			err::set(line, col,
				 "operators are only usable on primitive types or structs");
			return false;
		}
		TypeFuncMap *fn = types.get_funcmap(oper.tok.str(), this);
		if(!fn) {
			err::set(line, col, "function '%s' does not exist", oper.tok.str().c_str());
			return false;
		}
		StmtFnCallInfo *fci = new StmtFnCallInfo(src_id, line, col, {}, {lhs});
		if(rhs) fci->args.push_back(rhs);
		std::vector<Type *> calltemplates;
		TypeFunc *decidedfn = fn->decide_func(fci, calltemplates);
		err::reset();
		if(!decidedfn) {
			err::set(line, col, "function '%s' does not exist for type: %s",
				 oper.tok.str().c_str(), lhs->vtyp->str().c_str());
			fci->args.clear();
			delete fci;
			return false;
		}
		if(vtyp) delete vtyp;
		vtyp = decidedfn->rettype->copy();
		if(decidedfn->intrin_fn && !decidedfn->call_intrinsic(types, this, decidedfn, fci))
		{
			err::set(line, col,
				 "failed to call intrinsic "
				 "function during type assignment");
			delete fci;
			delete decidedfn;
			return false;
		}
		if(!init_templ_func(types, lhs, calltemplates, false)) return false;
		fci->args.clear();
		delete fci;
		delete decidedfn;
		break;
	}
	default: err::set(oper, "nonexistent operator"); return false;
	}
	if(commas > 0) {
		if(vtyp) delete vtyp;
		vtyp = nullptr;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVar::assign_type(TypeMgr &types)
{
	if(types.exists(name.data.s, true, false)) {
		err::set(name, "variable '%s' already exists in scope", name.data.s.c_str());
		return false;
	}
	if(val && !val->assign_type(types)) {
		err::set(name, "unable to determine type of value of this variable");
		return false;
	}
	if(vtype && !vtype->assign_type(types)) {
		err::set(name, "unable to determine type from the given type of this variable");
		return false;
	}
	if(val && val->vtyp->type == TSIMPLE) {
		if(static_cast<TypeSimple *>(val->vtyp)->name == "void") {
			err::set(line, col,
				 "expression returns void, which cannot be assigned to a var");
			return false;
		}
	}
	if(vtype && val && !vtype->vtyp->compatible(val->vtyp, line, col)) {
		err::set(line, col, "incompatible given type and value of the variable decl");
		return false;
	}
	if(val) {
		vtyp = val->vtyp->copy();
	} else if(vtype) {
		vtyp = vtype->vtyp->copy();
	}
	if(val && val->type == FNDEF) return types.add_func_copy(name.data.s, vtyp);
	return types.add_copy(name.data.s, vtyp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnSig::assign_type(TypeMgr &types)
{
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) continue;
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, nullptr, tname));
	}
	for(auto &p : params) {
		// this is added because init_templ_func() generates values for this by itself
		if(types.exists(p->name.data.s, true, false)) {
			p->vtyp = types.get_copy(p->name.data.s, this);
			continue;
		}
		if(!p->assign_type(types)) {
			err::set(p->line, p->col, "failed to assign type of this function param");
			return false;
		}
	}
	if(!rettype->assign_type(types)) {
		err::set(rettype->line, rettype->col, "failed to assign function return type");
		return false;
	}
	std::vector<Type *> args;
	for(auto &p : params) {
		args.push_back(p->vtyp->copy());
	}
	size_t layer = types.getlayer() - 1;
	if(parent && parent->type == FNDEF) --layer;
	vtyp = new TypeFunc(this, 0, 0, nullptr, layer, templates.size(), comptime, args,
			    rettype->vtyp->copy());
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnDef::assign_type(TypeMgr &types)
{
	types.pushlayer();
	if(!sig->assign_type(types)) {
		err::set(sig->line, sig->col, "failed to assign type to function signature");
		return false;
	}
	if(sig->templates.empty() && !sig->comptime && blk) {
		types.pushfunc(static_cast<TypeFunc *>(sig->vtyp));
		if(!blk->assign_type(types)) {
			err::set(blk->line, blk->col, "failed to assign type in function block");
			return false;
		}
		types.popfunc();
	}
	vtyp	     = sig->vtyp->copy();
	vtyp->parent = this;
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtHeader ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtHeader::assign_type(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtLib //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtLib::assign_type(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtExtern ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExtern::assign_type(TypeMgr &types)
{
	types.pushlayer();
	if(!sig->assign_type(types)) {
		err::set(sig->line, sig->col, "failed to assign type to function signature");
		return false;
	}
	if(headers && !headers->assign_type(types)) {
		err::set(headers->line, headers->col, "failed to assign header type");
		return false;
	}
	if(libs && !libs->assign_type(types)) {
		err::set(libs->line, libs->col, "failed to assign lib type");
		return false;
	}
	vtyp	     = sig->vtyp->copy();
	vtyp->parent = this;
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtEnum ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtEnum::assign_type(TypeMgr &types)
{
	types.pushlayer();
	for(auto &i : items) {
		if(!i->assign_type(types)) {
			err::set(i->line, i->col, "failed to assign type to enum");
			return false;
		}
	}
	types.poplayer();
	// TODO: create vtyp
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtStruct //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtStruct::assign_type(TypeMgr &types)
{
	types.pushlayer();
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) continue;
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, nullptr, tname));
	}
	std::vector<std::string> field_type_orders;
	for(auto &f : fields) {
		if(!f->assign_type(types)) {
			err::set(f->name, "unable to assign type of struct field");
			return false;
		}
		field_type_orders.push_back(f->name.data.s);
	}
	std::unordered_map<std::string, Type *> field_types;
	for(size_t i = 0; i < field_type_orders.size(); ++i) {
		field_types[field_type_orders[i]] = fields[i]->vtyp->copy();
	}
	vtyp = new TypeStruct(this, 0, 0, nullptr, false, templates.size(), field_type_orders,
			      field_types); // comment for correct auto formatting of this
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtVarDecl ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVarDecl::assign_type(TypeMgr &types)
{
	for(auto &d : decls) {
		if(!d->assign_type(types)) {
			err::set(d->name, "failed to determine type of this variable declaration");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtCond::assign_type(TypeMgr &types)
{
	for(auto &c : conds) {
		if(!c.cond->assign_type(types)) {
			err::set(c.cond->line, c.cond->col,
				 "failed to determine type of condition");
			return false;
		}
		if(!c.blk->assign_type(types)) {
			err::set(c.blk->line, c.blk->col, "failed to determine type of block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtForIn ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtForIn::assign_type(TypeMgr &types)
{
	types.pushlayer();
	if(!in->assign_type(types)) {
		err::set(in->line, in->col, "failed to determine type of 'in' expression");
		return false;
	}
	if(!types.add_copy(iter.data.s, in->vtyp)) {
		err::set(iter, "variable '%s' already exists in this scope", iter.data.s.c_str());
		return false;
	}
	if(!blk->assign_type(types)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFor::assign_type(TypeMgr &types)
{
	types.pushlayer();
	if(init && !init->assign_type(types)) {
		err::set(init->line, init->col, "failed to determine type of 'init' statement");
		return false;
	}
	if(cond && !cond->assign_type(types)) {
		err::set(cond->line, cond->col,
			 "failed to determine type of 'condition' expression");
		return false;
	}
	if(incr && !incr->assign_type(types)) {
		err::set(incr->line, incr->col,
			 "failed to determine type of 'increment' expression");
		return false;
	}
	// if(types.hasfunc() && types.getfunc()->comptime) {
	// 	if(!CHECK_VALUE(init) || !CHECK_VALUE(cond) || !CHECK_VALUE(incr)) {
	// 	}
	// }
	if(!blk->assign_type(types)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtWhile::assign_type(TypeMgr &types)
{
	if(cond && !cond->assign_type(types)) {
		err::set(cond->line, cond->col,
			 "failed to determine type of 'condition' expression");
		return false;
	}
	if(!blk->assign_type(types)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtRet::assign_type(TypeMgr &types)
{
	if(val && !val->assign_type(types)) {
		err::set(val->line, val->col, "failed to determine type of the return argument");
		return false;
	}
	Type *valtype = val ? val->vtyp->copy() : types.get_copy("void", parent);
	if(!types.hasfunc()) {
		err::set(line, col, "return statements can be in functions only");
		return false;
	}
	if(!types.getfunc()->rettype->compatible(valtype, val ? val->line : line,
						 val ? val->col : col)) {
		err::set(val ? val->line : line, val ? val->col : col,
			 "function return type and deduced return type are"
			 " incompatible (function return type: %s, deduced: %s)",
			 types.getfunc()->rettype->str().c_str(), valtype->str().c_str());
		delete valtype;
		return false;
	}
	vtyp = valtype;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtContinue /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtContinue::assign_type(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBreak::assign_type(TypeMgr &types)
{
	return true;
}
} // namespace parser
} // namespace sc