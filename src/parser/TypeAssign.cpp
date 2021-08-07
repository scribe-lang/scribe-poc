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
#include "Parser.hpp"
#include "parser/Stmts.hpp"
#include "parser/TypeMgr.hpp"

#define CHECK_VALUE(x) (x && x->type && x->type->val && x->type->val->type != VUNKNOWN)

namespace sc
{
namespace parser
{
// TODO: add a macro to each assignType function that checks if type is already set
// don't add this macro to a function where type has no relevance (continue, break)
static bool InitTemplateFn(TypeMgr &types, Stmt *lhs, const std::vector<Type *> &calltemplates,
			   const bool &has_va)
{
	if(calltemplates.empty() && !has_va) return true;
	// TODO: handle has_va
	assert(lhs->type && "LHS has no type assigned!");
	// if this function has no definition (template intrinsic, extern, for example)
	// do nothing
	if(!lhs->type->parent) return true;
	Stmt *templfnparent = lhs->type->parent->getParentWithType(BLOCK);
	TypeFunc *origsig   = as<TypeFunc>(lhs->type);
	if(!templfnparent) {
		err::set(lhs->line, lhs->col,
			 "function definition for specialization is not in a block!");
		return false;
	}
	Stmt *fndefvar = lhs->type->parent->getParentWithType(VAR);
	if(!fndefvar) {
		err::set(lhs->line, lhs->col,
			 "could not find function definition's variable declaration!");
		return false;
	}
	fndefvar     = fndefvar->copy(false, false);
	StmtVar *var = as<StmtVar>(fndefvar);
	assert(var->val && var->val->stmt_type == FNDEF && var->val &&
	       "expected function definition as variable value for template initialization");
	StmtFnDef *fn = as<StmtFnDef>(var->val);
	if(!fn->blk) {
		delete fndefvar;
		return false;
	}
	if(types.getCurrentModule() == fn->mod->getPath()) {
		types.lockScopesBefore(origsig->scope);
	} else {
		types.pushModule(fn->mod->getPath());
	}
	types.pushLayer();
	types.pushFunc(origsig);
	// for each types add signature variables
	for(size_t i = 0; i < fn->sig->templates.size(); ++i) {
		const std::string &t = fn->sig->templates[i].data.s;
		types.addCopy(t, calltemplates[i]);
	}
	fn->sig->templates.clear();
	fn->sig->has_variadic = false;
	if(origsig->args.size() > 0 && origsig->args.back()->type == TVARIADIC) {
		std::string tname = fn->sig->args.back()->vtype->getname();
		types.addCopy(tname, origsig->args.back());
	}
	for(size_t i = 0; i < fn->sig->args.size(); ++i) {
		types.addCopy(fn->sig->args[i]->name.data.s, origsig->args[i]);
	}
	// sig and blk must be separately assigned as variables added above will be shadowed
	// by new layer created in fn->assignType()
	if(!fn->sig->assignType(types)) {
		delete fndefvar;
		return false;
	}
	if(!fn->blk->assignType(types)) {
		err::set(lhs->line, lhs->col,
			 "failed to specialize template function definition: %s",
			 lhs->type->str().c_str());
		delete fndefvar;
		return false;
	}
	fn->type = fn->sig->type->copy();
	if(has_va) {
		// TODO: execute has_va() here
	}
	types.popFunc();
	types.popLayer();
	if(types.getCurrentModule() == fn->mod->getPath()) {
		types.unlockScope();
	}
	var->is_specialized = true;

	// lhs must point to correct type
	delete lhs->type;
	lhs->type	  = fn->type->copy();
	lhs->type->parent = lhs;

	StmtBlock *tfnparent = as<StmtBlock>(templfnparent);
	tfnparent->stmts.push_back(var);
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBlock::assignType(TypeMgr &types)
{
	types.pushLayer();
	for(size_t i = 0; i < stmts.size(); ++i) {
		auto &s = stmts[i];
		if(s->is_specialized) continue;
		if(!s->assignType(types)) {
			err::set(s->line, s->col,
				 "failed to perform type analysis on this statement");
			return false;
		}
	}
	if(parent) types.popLayer(); // do not remove the top layer if this block is top level
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtType::assignType(TypeMgr &types)
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
		if(!fn->assignType(types)) {
			err::set(line, col, "failed to determine type from the function type");
			return false;
		}
		type = fn->type->copy();
		return true;
	}
	Type *res = nullptr;
	if(info & VARIADIC && (res = types.get(this->getname(), nullptr))) {
		type	   = res->copy();
		type->info = info;
		type->ptr += ptr;
		type->info &= ~VARIADIC;
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
		type = res->copy();
	} else {
		type = res->specialize(resolvabletemplates);
	}
	type->info = info;
	type->ptr += ptr;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtSimple ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtSimple::assignType(TypeMgr &types)
{
	switch(val.tok.val) {
	case lex::VOID: type = types.getCopy("void", this); break;
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL: type = types.getCopy("i1", this); break;
	case lex::INT: type = types.getCopy("i32", this); break;
	case lex::FLT: type = types.getCopy("f32", this); break;
	case lex::CHAR: type = types.getCopy("u8", this); break;
	case lex::STR: type = types.getCopy("*const u8", this); break;
	case lex::IDEN: type = types.getCopy(val.data.s, this); break;
	default: return false;
	}
	if(!type) {
		err::set(val, "failed to determine type of this statement");
		return false;
	}
	return type;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnCallInfo::assignType(TypeMgr &types)
{
	types.pushLayer();
	for(auto &t : templates) {
		if(!t->assignType(types)) {
			err::set(t->line, t->col, "failed to determine type of template");
			return false;
		}
	}
	for(auto &a : args) {
		if(!a->assignType(types)) {
			err::set(a->line, a->col, "failed to determine type of argument");
			return false;
		}
	}
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExpr::assignType(TypeMgr &types)
{
	if(lhs && !lhs->assignType(types)) {
		err::set(lhs->line, lhs->col, "failed to determine type of LHS");
		return false;
	}
	if(oper.tok.val != lex::DOT && oper.tok.val != lex::ARROW && rhs && !rhs->assignType(types))
	{
		err::set(rhs->line, rhs->col, "failed to determine type of RHS");
		return false;
	}
	// TODO: or-var & or-blk
	switch(oper.tok.val) {
	case lex::ARROW:
		if(lhs->type->ptr == 0) {
			err::set(line, col, "arrow operator only works for pointer types");
			return false;
		}
	case lex::DOT: {
		assert(rhs->stmt_type == SIMPLE && "RHS for dot/arrow MUST be a simple type");
		if(lhs->type->type != TSTRUCT && lhs->type->type != TVARIADIC) {
			err::set(line, col,
				 "LHS must be a structure to use the dot operator, found: %s",
				 lhs->type->str().c_str());
			return false;
		}
		if(lhs->type->type == TVARIADIC) {
			TypeVariadic *v = as<TypeVariadic>(lhs->type);
			if(!v->isIndexed()) {
				err::set(line, col, "variadic variable must be indexed to use");
				return false;
			}
			// TODO: loop through variadic to ensure the dot operator is valid
			break;
		}
		TypeStruct *lst = as<TypeStruct>(lhs->type);
		if(lst->is_def) {
			err::set(line, col,
				 "cannot use dot operator on a struct"
				 " definition; instantiate it first");
			return false;
		}
		StmtSimple *rsim = as<StmtSimple>(rhs);
		size_t ptr	 = lst->ptr;
		if(oper.tok.val == lex::ARROW) --ptr;
		Type *res = ptr == 0 ? lst->get_field(rsim->val.data.s) : nullptr;
		if(!res && !(res = types.getFuncMapCopy(rsim->val.data.s, this))) {
			err::set(line, col,
				 "no function or struct field (in '%s') named '%s' exists",
				 lst->str().c_str(), rsim->val.data.s.c_str());
			return false;
		}
		rhs->type	  = res;
		rhs->type->parent = rhs;
		type		  = res->copy();
		type->parent	  = this;
		break;
	}
	case lex::FNCALL: {
		assert(rhs && rhs->stmt_type == FNCALLINFO &&
		       "RHS for function call must be a call info (compiler failure)");
		StmtFnCallInfo *finfo = as<StmtFnCallInfo>(rhs);
		std::vector<Type *> calltemplates;
		bool has_va = false;
		if(lhs->type->type != TFUNC && lhs->type->type != TSTRUCT &&
		   lhs->type->type != TFUNCMAP) {
			err::set(lhs->line, lhs->col,
				 "function call can be performed "
				 "only on a function or struct type, attempted on: %s",
				 lhs->type->str().c_str());
			return false;
		}
		if(lhs->type->type == TFUNCMAP) {
			TypeFuncMap *fmap = as<TypeFuncMap>(lhs->type);
			if(!(type = fmap->decide_func(finfo, calltemplates))) {
				err::set(line, col,
					 "failed to decide the function "
					 "to execute, need more info");
				return false;
			}
			delete lhs->type;
			lhs->type = type;
			has_va	  = as<TypeFunc>(type)->has_va;
			type	  = as<TypeFunc>(lhs->type)->rettype->copy();
		} else if(lhs->type->type == TFUNC) {
			TypeFunc *oldfn = as<TypeFunc>(lhs->type);
			TypeFunc *fn	= nullptr;
			if(!(fn = oldfn->specialize_compatible_call(finfo, calltemplates))) {
				err::set(line, col,
					 "function '%s' incompatible with call arguments",
					 oldfn->str().c_str());
				return false;
			}
			delete oldfn;
			lhs->type = fn;
			if(type) delete type;
			type = fn->rettype->copy();
			if(fn->intrin_fn && !fn->call_intrinsic(types, this, fn, finfo)) {
				err::set(line, col,
					 "failed to call intrinsic "
					 "function during type assignment");
				return false;
			}
			has_va = fn->has_va;
		} else if(lhs->type->type == TSTRUCT) {
			TypeStruct *st = as<TypeStruct>(lhs->type);
			if(!st->is_def) {
				err::set(line, col,
					 "only structure definitions can be called (instantiated)");
				return false;
			}
			// call the <struct>() function
			// maybe <struct>.init() in future if required
			if(!(type = st->specialize_compatible_call(finfo, calltemplates))) {
				err::set(line, col,
					 "failed to instantiate struct with given arguments");
				return false;
			}
			delete lhs->type;
			lhs->type = type;
			type	  = lhs->type->copy();
			break; // no need to clone the struct
		}
		// apply stmt template specialization
		if(!InitTemplateFn(types, lhs, calltemplates, has_va)) return false;
		break;
	}
	case lex::SUBS: {
		if(lhs->type->type == TVARIADIC) {
			bool found_compat = false;
			for(auto &bn : basenumtypes()) {
				if(rhs->type->compatible(types.get(bn, this), line, col)) {
					found_compat = true;
					break;
				}
			}
			err::reset();
			if(!found_compat) {
				err::set(line, col,
					 "variadics can only take one of the "
					 "primitive numeric types (as index), found: %s",
					 rhs->type->str().c_str());
				return false;
			}
			TypeVariadic *va = as<TypeVariadic>(lhs->type->copy());
			va->setIndexed(true);
			type = va;
			break;
		}
		if(lhs->type->ptr > 0) {
			bool found_compat = false;
			for(auto &bn : basenumtypes()) {
				if(rhs->type->compatible(types.get(bn, this), line, col)) {
					found_compat = true;
					break;
				}
			}
			if(!found_compat) {
				err::set(line, col,
					 "pointer subscript can only take one of the "
					 "primitive numeric types (as index), found: %s",
					 rhs->type->str().c_str());
				return false;
			}
			type = lhs->type->copy();
			--type->ptr;
			break;
		}
		err::set(line, col, "unimplemented subscript for type: %s",
			 lhs->type->str().c_str());
		return false;
	}
	// address of
	case lex::UAND: {
		type = lhs->type->copy();
		++type->ptr;
		break;
	}
	// dereference
	case lex::UMUL: {
		if(lhs->type->ptr == 0) {
			err::set(line, col, "cannot dereference non pointer type: %s",
				 lhs->type->str().c_str());
			return false;
		}
		type = lhs->type->copy();
		--type->ptr;
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
		if(lhs->type->type != TSIMPLE && lhs->type->type != TSTRUCT) {
			err::set(line, col,
				 "operators are only usable on primitive types or structs");
			return false;
		}
		TypeFuncMap *fn = types.getFuncMap(oper.tok.str(), this);
		if(!fn) {
			err::set(line, col, "function '%s' does not exist", oper.tok.str().c_str());
			return false;
		}
		StmtFnCallInfo *fci = new StmtFnCallInfo(mod, line, col, {}, {lhs});
		if(rhs) fci->args.push_back(rhs);
		std::vector<Type *> calltemplates;
		TypeFunc *decidedfn = fn->decide_func(fci, calltemplates);
		err::reset();
		if(!decidedfn) {
			err::set(line, col, "function '%s' does not exist for type: %s",
				 oper.tok.str().c_str(), lhs->type->str().c_str());
			fci->args.clear();
			delete fci;
			return false;
		}
		if(type) delete type;
		type = decidedfn->rettype->copy();
		if(decidedfn->intrin_fn && !decidedfn->call_intrinsic(types, this, decidedfn, fci))
		{
			err::set(line, col,
				 "failed to call intrinsic "
				 "function during type assignment");
			delete fci;
			delete decidedfn;
			return false;
		}
		if(!InitTemplateFn(types, lhs, calltemplates, false)) return false;
		fci->args.clear();
		delete fci;
		delete decidedfn;
		break;
	}
	default: err::set(oper, "nonexistent operator"); return false;
	}
	if(commas > 0) {
		if(type) delete type;
		type = nullptr;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVar::assignType(TypeMgr &types)
{
	if(types.exists(name.data.s, true, false)) {
		err::set(name, "variable '%s' already exists in scope", name.data.s.c_str());
		return false;
	}
	if(val && !val->assignType(types)) {
		err::set(name, "unable to determine type of value of this variable");
		return false;
	}
	if(vtype && !vtype->assignType(types)) {
		err::set(name, "unable to determine type from the given type of this variable");
		return false;
	}
	if(val && val->type->type == TSIMPLE) {
		if(as<TypeSimple>(val->type)->name == "void") {
			err::set(line, col,
				 "expression returns void, which cannot be assigned to a var");
			return false;
		}
	}
	if(vtype && val && !vtype->type->compatible(val->type, line, col)) {
		err::set(line, col, "incompatible given type and value of the variable decl");
		return false;
	}
	if(val) {
		type = val->type->copy();
	} else if(vtype) {
		type = vtype->type->copy();
	}
	if(val && val->stmt_type == FNDEF) return types.addFuncCopy(name.data.s, type);
	return types.addCopy(name.data.s, type);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnSig::assignType(TypeMgr &types)
{
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) continue;
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, tname));
	}
	for(auto &p : args) {
		// this is added because InitTemplateFn() generates values for this by itself
		if(types.exists(p->name.data.s, true, false)) {
			p->type = types.getCopy(p->name.data.s, this);
			continue;
		}
		if(!p->assignType(types)) {
			err::set(p->line, p->col, "failed to assign type of this function param");
			return false;
		}
	}
	if(!rettype->assignType(types)) {
		err::set(rettype->line, rettype->col, "failed to assign function return type");
		return false;
	}
	std::vector<Type *> newargs;
	for(auto &p : args) {
		newargs.push_back(p->type->copy());
	}
	size_t layer = types.getLayer() - 1;
	if(parent && parent->stmt_type == FNDEF) --layer;
	type = new TypeFunc(this, 0, 0, layer, templates.size(), has_variadic, newargs,
			    rettype->type->copy());
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnDef::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(!sig->assignType(types)) {
		err::set(sig->line, sig->col, "failed to assign type to function signature");
		return false;
	}
	if(sig->templates.empty() && !sig->has_variadic && blk) {
		types.pushFunc(as<TypeFunc>(sig->type));
		if(!blk->assignType(types)) {
			err::set(blk->line, blk->col, "failed to assign type in function block");
			return false;
		}
		types.popFunc();
	}
	type	     = sig->type->copy();
	type->parent = this;
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtHeader ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtHeader::assignType(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtLib //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtLib::assignType(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtExtern ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExtern::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(!sig->assignType(types)) {
		err::set(sig->line, sig->col, "failed to assign type to function signature");
		return false;
	}
	if(headers && !headers->assignType(types)) {
		err::set(headers->line, headers->col, "failed to assign header type");
		return false;
	}
	if(libs && !libs->assignType(types)) {
		err::set(libs->line, libs->col, "failed to assign lib type");
		return false;
	}
	type	     = sig->type->copy();
	type->parent = this;
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtEnum ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtEnum::assignType(TypeMgr &types)
{
	types.pushLayer();
	// for(auto &i : items) {
	// 	if(!i->assignType(types)) {
	// 		err::set(i->line, i->col, "failed to assign type to enum");
	// 		return false;
	// 	}
	// }
	types.popLayer();
	// TODO: create type
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtStruct //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtStruct::assignType(TypeMgr &types)
{
	types.pushLayer();
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) continue;
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, tname));
	}
	std::vector<std::string> field_type_orders;
	for(auto &f : fields) {
		if(!f->assignType(types)) {
			err::set(f->name, "unable to assign type of struct field");
			return false;
		}
		field_type_orders.push_back(f->name.data.s);
	}
	std::unordered_map<std::string, Type *> field_types;
	for(size_t i = 0; i < field_type_orders.size(); ++i) {
		field_types[field_type_orders[i]] = fields[i]->type->copy();
	}
	type = new TypeStruct(this, 0, 0, false, templates.size(), field_type_orders,
			      field_types); // comment for correct auto formatting of this
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtVarDecl ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVarDecl::assignType(TypeMgr &types)
{
	for(auto &d : decls) {
		if(!d->assignType(types)) {
			err::set(d->name, "failed to determine type of this variable declaration");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtCond::assignType(TypeMgr &types)
{
	for(auto &c : conds) {
		if(!c.cond->assignType(types)) {
			err::set(c.cond->line, c.cond->col,
				 "failed to determine type of condition");
			return false;
		}
		if(!c.blk->assignType(types)) {
			err::set(c.blk->line, c.blk->col, "failed to determine type of block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtForIn ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtForIn::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(!in->assignType(types)) {
		err::set(in->line, in->col, "failed to determine type of 'in' expression");
		return false;
	}
	if(!types.addCopy(iter.data.s, in->type)) {
		err::set(iter, "variable '%s' already exists in this scope", iter.data.s.c_str());
		return false;
	}
	if(!blk->assignType(types)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFor::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(init && !init->assignType(types)) {
		err::set(init->line, init->col, "failed to determine type of 'init' statement");
		return false;
	}
	if(cond && !cond->assignType(types)) {
		err::set(cond->line, cond->col,
			 "failed to determine type of 'condition' expression");
		return false;
	}
	if(incr && !incr->assignType(types)) {
		err::set(incr->line, incr->col,
			 "failed to determine type of 'increment' expression");
		return false;
	}
	if(!blk->assignType(types)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtWhile::assignType(TypeMgr &types)
{
	if(cond && !cond->assignType(types)) {
		err::set(cond->line, cond->col,
			 "failed to determine type of 'condition' expression");
		return false;
	}
	if(!blk->assignType(types)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtRet::assignType(TypeMgr &types)
{
	if(val && !val->assignType(types)) {
		err::set(val->line, val->col, "failed to determine type of the return argument");
		return false;
	}
	Type *valtype = val ? val->type->copy() : types.getCopy("void", parent);
	if(!types.hasFunc()) {
		err::set(line, col, "return statements can be in functions only");
		return false;
	}
	if(!types.getFunc()->rettype->compatible(valtype, val ? val->line : line,
						 val ? val->col : col)) {
		err::set(val ? val->line : line, val ? val->col : col,
			 "function return type and deduced return type are"
			 " incompatible (function return type: %s, deduced: %s)",
			 types.getFunc()->rettype->str().c_str(), valtype->str().c_str());
		delete valtype;
		return false;
	}
	type = valtype;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtContinue /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtContinue::assignType(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBreak::assignType(TypeMgr &types)
{
	return true;
}
} // namespace parser
} // namespace sc