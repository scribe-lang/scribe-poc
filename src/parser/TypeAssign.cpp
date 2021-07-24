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

#include "Error.hpp"
#include "parser/Stmts.hpp"
#include "parser/TypeMgr.hpp"

namespace sc
{
namespace parser
{
static bool init_templ_func(TypeMgr &types, stmt_base_t *lhs,
			    const std::vector<Type *> &calltemplates, const bool &comptime)
{
	if(calltemplates.empty() && !comptime) return true;
	// TODO: handle comptime
	stmt_base_t *templfnparent = lhs->vtyp->parent->get_parent_with_type(BLOCK);
	TypeFunc *origsig	   = static_cast<TypeFunc *>(lhs->vtyp);
	if(!templfnparent) {
		err::set(lhs->line, lhs->col,
			 "function definition for specialization is not in a block!");
		return false;
	}
	stmt_base_t *fndefvar = lhs->vtyp->parent->get_parent_with_type(VAR);
	if(!fndefvar) {
		err::set(lhs->line, lhs->col,
			 "could not find function definition's variable declaration!");
		return false;
	}
	fndefvar	= fndefvar->copy(false);
	stmt_var_t *var = as<stmt_var_t>(fndefvar);
	assert(var->val && var->val->type == FNDEF && var->val &&
	       "expected function definition as variable value for template initialization");
	stmt_fndef_t *fn = as<stmt_fndef_t>(var->val);
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
	types.pushfret(origsig->rettype);
	// for each types add signature variables
	for(size_t i = 0; i < fn->sig->templates.size(); ++i) {
		const std::string &t = fn->sig->templates[i].data.s;
		types.add_copy(t, calltemplates[i]);
	}
	fn->sig->templates.clear();
	if(origsig->args.size() > 0 && origsig->args.back()->type == TVARIADIC) {
		std::string tname = fn->sig->params.back()->vtype->getname();
		types.add_copy(tname, origsig->args.back());
	}
	fn->sig->comptime = false; // because body of function is not read if comptime is true
	if(!fn->assign_type(types)) {
		err::set(lhs->line, lhs->col,
			 "failed to specialize template function definition: %s",
			 lhs->vtyp->str().c_str());
		delete fndefvar;
		return false;
	}
	fn->sig->comptime = comptime;
	types.popfret();
	types.poplayer();
	if(types.current_src() == fn->src_id) {
		types.unlock_scope();
	}
	var->is_specialized = true;

	stmt_block_t *tfnparent = static_cast<stmt_block_t *>(templfnparent);
	tfnparent->stmts.push_back(var);
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_block_t::assign_type(TypeMgr &types)
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
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_type_t::assign_type(TypeMgr &types)
{
	std::vector<Type *> resolvabletemplates;
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) {
			Type *v = types.get(templates[i].data.s, this);
			resolvabletemplates.push_back(v);
			continue;
		}
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, tname));
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
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_simple_t::assign_type(TypeMgr &types)
{
	switch(val.tok.val) {
	case lex::VOID: vtyp = types.get_copy("void", this); break;
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL: vtyp = types.get_copy("i1", this); break;
	case lex::INT: vtyp = types.get_copy("i32", this); break;
	case lex::FLT: vtyp = types.get_copy("f32", this); break;
	case lex::CHAR: vtyp = types.get_copy("u8", this); break;
	case lex::STR: vtyp = types.get_copy("*const u8", this); break;
	case lex::IDEN:
		vtyp = types.get_copy(val.data.s, this);
		if(vtyp == nullptr) return false;
		break;
	default: return false;
	}
	if(!vtyp) err::set(val, "failed to determine type of this statement");
	return vtyp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// stmt_fncallinfo_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fncallinfo_t::assign_type(TypeMgr &types)
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
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_expr_t::assign_type(TypeMgr &types)
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
		stmt_simple_t *rsim = static_cast<stmt_simple_t *>(rhs);
		size_t ptr	    = lst->ptr;
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
		stmt_fncallinfo_t *finfo = static_cast<stmt_fncallinfo_t *>(rhs);
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
			if(!fn->intrin_fn) vtyp = fn->rettype->copy();
			if(fn->intrin_fn && !fn->call_intrinsic(types, this)) {
				err::set(line, col,
					 "failed to call intrinsic "
					 "function during type assignment");
				return false;
			}
			comptime = fn->comptime;
			if(!vtyp) vtyp = fn->rettype->copy();
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
			if(!found_compat) {
				err::set(line, col,
					 "variadics can only take one of the "
					 "primitive numeric types (as index), found: %s",
					 rhs->vtyp->str().c_str());
				return false;
			}
			err::reset();
			vtyp = types.get_copy("any", this);
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
		stmt_base_t *store = lhs;
		lhs		   = rhs;
		rhs		   = store;
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
		stmt_fncallinfo_t *fci = new stmt_fncallinfo_t(src_id, line, col, {}, {lhs});
		if(rhs) fci->args.push_back(rhs);
		std::vector<Type *> calltemplates;
		TypeFunc *decidedfn = fn->decide_func(fci, calltemplates);
		if(!decidedfn) {
			err::set(line, col, "function '%s' does not exist for type: %s",
				 oper.tok.str().c_str(), lhs->vtyp->str().c_str());
			fci->args.clear();
			delete fci;
			return false;
		}
		if(!init_templ_func(types, lhs, calltemplates, false)) return false;
		fci->args.clear();
		vtyp = static_cast<TypeFunc *>(decidedfn)->rettype->copy();
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
///////////////////////////////////////// stmt_var_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_var_t::assign_type(TypeMgr &types)
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
	if(vtype) {
		vtyp = vtype->vtyp->copy();
	} else if(val) {
		vtyp = val->vtyp->copy();
	}
	if(val && val->type == FNDEF) return types.add_func_copy(name.data.s, vtyp);
	return types.add_copy(name.data.s, vtyp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fnsig_t::assign_type(TypeMgr &types)
{
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) continue;
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, tname));
	}
	for(auto &p : params) {
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
	vtyp =
	new TypeFunc(this, 0, 0, layer, templates.size(), comptime, args, rettype->vtyp->copy());
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fndef_t::assign_type(TypeMgr &types)
{
	types.pushlayer();
	if(!sig->assign_type(types)) {
		err::set(sig->line, sig->col, "failed to assign type to function signature");
		return false;
	}
	if(sig->templates.empty() && !sig->comptime && blk) {
		types.pushfret(sig->rettype->vtyp);
		if(!blk->assign_type(types)) {
			err::set(blk->line, blk->col, "failed to assign type in function block");
			return false;
		}
		types.popfret();
	}
	vtyp	     = sig->vtyp->copy();
	vtyp->parent = this;
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_header_t::assign_type(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_lib_t::assign_type(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_extern_t::assign_type(TypeMgr &types)
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
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_enumdef_t::assign_type(TypeMgr &types)
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
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_struct_t::assign_type(TypeMgr &types)
{
	types.pushlayer();
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) continue;
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, tname));
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
	vtyp = new TypeStruct(this, 0, 0, false, templates.size(), field_type_orders,
			      field_types); // comment for correct auto formatting of this
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_vardecl_t::assign_type(TypeMgr &types)
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
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cond_t::assign_type(TypeMgr &types)
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
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_forin_t::assign_type(TypeMgr &types)
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
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_for_t::assign_type(TypeMgr &types)
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
	if(!blk->assign_type(types)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	types.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_while_t::assign_type(TypeMgr &types)
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
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_ret_t::assign_type(TypeMgr &types)
{
	if(val && !val->assign_type(types)) {
		err::set(val->line, val->col, "failed to determine type of the return argument");
		return false;
	}
	Type *valtype = val ? val->vtyp->copy() : types.get_copy("void", parent);
	if(!types.hasfret()) {
		err::set(line, col, "return statements can be in functions only");
		return false;
	}
	if(!types.getfret()->compatible(valtype, val ? val->line : line, val ? val->col : col)) {
		err::set(val ? val->line : line, val ? val->col : col,
			 "function return type and deduced return type are"
			 " incompatible (function return type: %s, deduced: %s)",
			 types.getfret()->str().c_str(), valtype->str().c_str());
		delete valtype;
		return false;
	}
	vtyp = valtype;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cont_t::assign_type(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_break_t::assign_type(TypeMgr &types)
{
	return true;
}
} // namespace parser
} // namespace sc