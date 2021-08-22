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

#include <cinttypes>

#include "Error.hpp"
#include "Parser.hpp"
#include "parser/Stmts.hpp"
#include "parser/TypeMgr.hpp"
#include "Utils.hpp"

#define CHECK_VALUE(x) (x && x->type && x->type->val && x->type->val->type != VUNKNOWN)

namespace sc
{
namespace parser
{
static inline std::string GetMangledName(const std::string &mod_id, const lex::Lexeme &name)
{
	return name.data.s + "_" + mod_id;
}
static inline std::string GetMangledName(Stmt *stmt, const lex::Lexeme &name)
{
	return GetMangledName(stmt->mod->getID(), name);
}

static bool InitTemplateFn(TypeMgr &types, Stmt *caller, Type *&calledfn,
			   std::unordered_map<std::string, Type *> &calltemplates,
			   const bool &has_va);
static void ApplyTypeCoercion(StmtExpr *expr);
static bool ChooseSuperiorPrimitiveType(TypeSimple *l, TypeSimple *r);
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBlock::assignType(TypeMgr &types)
{
	types.pushLayer();
	for(size_t i = 0; i < stmts.size(); ++i) {
		Stmt *s = stmts[i];
		if(!s) break;
		if(s->isSpecialized()) continue;
		if(!s->assignType(types)) {
			err::set(s, "failed to perform type analysis on this statement");
			return false;
		}
	}
	if(parent) types.popLayer(); // do not remove the top layer if this block is top level
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtType::assignType(TypeMgr &types)
{
	std::unordered_map<std::string, Type *> resolvabletemplates;
	for(size_t i = 0; i < templates.size(); ++i) {
		if(types.exists(templates[i].data.s, false, true)) {
			Type *v = types.get(templates[i].data.s);
			resolvabletemplates["@" + std::to_string(i)] = v;
			continue;
		}
		std::string tname = "@" + std::to_string(i);
		types.add(templates[i].data.s, new TypeSimple(nullptr, 0, 0, tname));
	}
	if(func) {
		if(!fn->assignType(types)) {
			err::set(this, "failed to determine type from the function type");
			return false;
		}
		type = fn->type->copy();
		return true;
	}
	Type *res = nullptr;
	if(info & VARIADIC && (res = types.get(this->getname()))) {
		type	   = res->copy();
		type->info = info;
		type->ptr += ptr;
		type->info &= ~VARIADIC;
		return res;
	}
	res = types.get(GetMangledName(this, name.front()));
	if(res == nullptr && !(res = types.get(name.front().data.s))) {
		err::set(name.front(), "variable '%s' does not exist", name.front().data.s.c_str());
		return false;
	}
	for(size_t i = 1; i < name.size(); ++i) {
		if(res->type != TSTRUCT) {
			err::set(name[i - 1], "expected this to be a struct, found: '%s'",
				 res->str().c_str());
			return false;
		}
		res = ((TypeStruct *)res)->get_field(GetMangledName(this, name[i]));
		if(!res && !(res = types.get(name[i].data.s))) {
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
/////////////////////////////////////////// StmtSimple ////////////////////////////////////////////
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
	case lex::CHAR: type = types.getCopy("i8", this); break;
	case lex::STR:
		type = types.getCopy("i8", this);
		type->info |= CONST;
		type->ptr = 1;
		break;
	case lex::IDEN:
		if(!isAppliedModuleID()) {
			type = types.getCopy(GetMangledName(this, val), nullptr);
		}
		if(!type) {
			type = types.getCopy(val.data.s, nullptr);
			break;
		}
		val.data.s = GetMangledName(this, val);
		setAppliedModuleID(true);
		break;
	default: return false;
	}
	if(!type) {
		err::set(val, "failed to determine type of this statement");
		return false;
	}
	if(val.tok.val != lex::IDEN) {
		setComptime(true);
	} else if(type->parent && type->parent->isComptime()) {
		setComptime(true);
	}
	return type;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnCallInfo::assignType(TypeMgr &types)
{
	types.pushLayer();
	for(auto &t : templates) {
		if(!t->assignType(types)) {
			err::set(t, "failed to determine type of template");
			return false;
		}
	}
	for(auto &a : args) {
		if(!a->assignType(types)) {
			err::set(a, "failed to determine type of argument");
			return false;
		}
	}
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExpr::assignType(TypeMgr &types)
{
	if(lhs && !lhs->assignType(types)) {
		err::set(lhs, "failed to determine type of LHS");
		return false;
	}
	if(oper.tok.val == lex::EMPTY) {
		type = lhs->type->copy();
		return true;
	}
	if(oper.tok.val != lex::DOT && oper.tok.val != lex::ARROW && rhs && !rhs->assignType(types))
	{
		err::set(rhs, "failed to determine type of RHS");
		return false;
	}
	static std::vector<std::string> importids;
	if(oper.tok.val != lex::DOT) importids.clear();
	// TODO: or-var & or-blk
	switch(oper.tok.val) {
	case lex::ARROW:
		if(lhs->type->ptr == 0) {
			err::set(this, "arrow operator only works for pointer types");
			return false;
		}
	case lex::DOT: {
		assert(rhs->stmt_type == SIMPLE && "RHS for dot/arrow MUST be a simple type");
		if(lhs->type->type != TSTRUCT && lhs->type->type != TIMPORT) {
			err::set(this, "LHS must be a structure to use the dot operator, found: %s",
				 lhs->type->str().c_str());
			return false;
		}
		StmtSimple *rsim = as<StmtSimple>(rhs);
		if(lhs->type->type == TIMPORT) {
			importids.push_back(as<TypeImport>(lhs->type)->getModID());
			rsim->val.data.s = GetMangledName(importids.back(), rsim->val);
			rsim->setAppliedModuleID(true);
			if(!rhs->assignType(types)) {
				err::set(rhs, "failed to determine type of RHS in import");
				return false;
			}
			type	     = rhs->type->copy();
			type->parent = this;
			if(rhs->isComptime()) setComptime(true);
			delete lhs;
			lhs	     = rhs;
			rhs	     = nullptr;
			oper.tok.val = lex::EMPTY;
			break;
		}
		TypeStruct *lst = as<TypeStruct>(lhs->type);
		if(lst->is_def) {
			err::set(this, "cannot use dot operator on a struct"
				       " definition; instantiate it first");
			return false;
		}
		// std::string mod_id = importids.empty() ? mod->getID() : importids.back();
		// rsim->val.data.s   = GetMangledName(mod_id, rsim->val);
		size_t ptr = lst->ptr;
		if(oper.tok.val == lex::ARROW) --ptr;
		Type *res = ptr == 0 ? lst->get_field(rsim->val.data.s) : nullptr;
		if(!res) {
			if(!(res = types.getFuncMapCopy(rsim->val.data.s, this))) {
				err::set(this,
					 "no function or struct field"
					 " (in '%s') named '%s' exists",
					 lst->str().c_str(), rsim->val.data.s.c_str());
				return false;
			}
		} else if(res->type != TFUNCMAP) {
			res = res->copy();
		}

		if(res->type == TFUNCMAP) {
			Type *self = lst->copy();
			self->info |= REF;
			as<TypeFuncMap>(res)->setSelf(self);
		}
		rhs->type	  = res;
		rhs->type->parent = rhs;
		type		  = res->copy();
		type->parent	  = this;
		if(lhs->isComptime() && res->type != TFUNCMAP) {
			setComptime(true);
		}
		break;
	}
	case lex::FNCALL: {
		assert(rhs && rhs->stmt_type == FNCALLINFO &&
		       "RHS for function call must be a call info (compiler failure)");
		StmtFnCallInfo *finfo = as<StmtFnCallInfo>(rhs);
		std::unordered_map<std::string, Type *> calltemplates;
		bool has_va = false;
		if(lhs->type->type != TFUNC && lhs->type->type != TSTRUCT &&
		   lhs->type->type != TFUNCMAP) {
			err::set(lhs,
				 "function call can be performed "
				 "only on a function or struct type, attempted on: %s",
				 lhs->type->str().c_str());
			return false;
		}
		if(lhs->type->type == TFUNCMAP) {
			TypeFuncMap *fmap = as<TypeFuncMap>(lhs->type);
			TypeFunc *fn	  = nullptr;
			if(!(fn = fmap->decide_func(finfo, calltemplates))) {
				err::set(this, "failed to decide the function "
					       "to execute, need more info");
				return false;
			}
			if(fmap->getSelf() && fmap->getSelf()->parent->isComptime()) {
				setComptime(true);
			}
			if(fmap->getSelf()) {
				StmtExpr *tmpl	  = as<StmtExpr>(lhs);
				tmpl->lhs->parent = rhs;
				finfo->args.push_back(tmpl->lhs);
				tmpl->lhs	  = nullptr;
				tmpl->rhs->parent = this;
				lhs		  = tmpl->rhs;
				tmpl->rhs	  = nullptr;
				delete tmpl;
			}
			delete lhs->type;
			lhs->type = fn;
			has_va	  = fn->has_va;
			type	  = fn->rettype->copy();
		} else if(lhs->type->type == TFUNC) {
			TypeFunc *oldfn = as<TypeFunc>(lhs->type);
			TypeFunc *fn	= nullptr;
			if(!(fn = oldfn->specialize_compatible_call(finfo, calltemplates))) {
				err::set(this, "function '%s' incompatible with call arguments",
					 oldfn->str().c_str());
				return false;
			}
			delete oldfn;
			lhs->type = fn;
			if(type) delete type;
			type = fn->rettype->copy();
			if(fn->getIntrinsicFunc() && !isIntrinsic()) {
				err::set(this, "this is an intrinsic function - "
					       "requires '@' before function name to call");
				return false;
			}
			ValueMgr &vals = types.getParser()->getValueMgr();
			if(fn->getIntrinsicFuncType() == IPARSE &&
			   !fn->callIntrinsicFunc(types, vals, this, finfo)) {
				err::set(this, "failed to call parse intrinsic "
					       "function during type assignment");
				return false;
			} else if(fn->getIntrinsicFuncType() == IVALUE) {
				this->setIntrinsicFunc(fn->getIntrinsicFunc());
			}
			has_va = fn->has_va;
		} else if(lhs->type->type == TSTRUCT) {
			TypeStruct *st = as<TypeStruct>(lhs->type);
			if(!st->is_def) {
				err::set(this,
					 "only structure definitions can be called (instantiated)");
				return false;
			}
			// call the <struct>() function
			// maybe <struct>.init() in future if required
			if(!(type = st->specialize_compatible_call(finfo, calltemplates))) {
				err::set(this, "failed to instantiate struct with given arguments");
				return false;
			}
			delete lhs->type;
			lhs->type = type;
			type	  = lhs->type->copy();
			break; // no need to clone the struct
		}
		// apply stmt template specialization
		if(!InitTemplateFn(types, this, lhs->type, calltemplates, has_va)) return false;
		for(auto &t : calltemplates) delete t.second;
		break;
	}
	case lex::SUBS: {
		if(lhs->type->type == TVARIADIC) {
			if(!rhs->type->integerCompatible()) {
				err::set(this,
					 "variadics can only take one of the "
					 "primitive numeric types (as index), found: %s",
					 rhs->type->str().c_str());
				return false;
			}
			if(!rhs->assignValue(types, types.getParser()->getValueMgr())) {
				err::set(this, "index for a variadic must be comptime");
				return false;
			}
			TypeVariadic *va = as<TypeVariadic>(lhs->type);
			if(va->args.size() <= rhs->value->i) {
				err::set(this,
					 "variadic index out of bounds"
					 " (va: %zu, index: %" PRId64 ")",
					 va->args.size(), rhs->value->i);
				return false;
			}
			setVariadicIndex(rhs->value->i);
			type = va->args[rhs->value->i]->copy();
			break;
		} else if(lhs->type->ptr > 0) {
			if(!rhs->type->integerCompatible()) {
				err::set(this,
					 "pointer subscript can only take one of the "
					 "primitive numeric types (as index), found: %s",
					 rhs->type->str().c_str());
				return false;
			}
			type = lhs->type->copy();
			--type->ptr;
		} else {
			err::set(this, "unimplemented subscript for type: %s",
				 lhs->type->str().c_str());
			return false;
		}
		goto applyoperfn;
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
			err::set(this, "cannot dereference non pointer type: %s",
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
		goto applyoperfn;
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
	applyoperfn:
		ApplyTypeCoercion(this); // basically, type promotion for primitives
		if(lhs->type->type != TSIMPLE && lhs->type->type != TSTRUCT) {
			err::set(this, "operators are only usable on primitive types or structs");
			return false;
		}
		TypeFuncMap *fn = types.getFuncMap(oper.tok.str(), this);
		if(!fn) {
			err::set(this, "function '%s' does not exist", oper.tok.str().c_str());
			return false;
		}
		StmtFnCallInfo *fci = new StmtFnCallInfo(mod, line, col, {}, {lhs});
		if(rhs) fci->args.push_back(rhs);
		std::unordered_map<std::string, Type *> calltemplates;
		TypeFunc *decidedfn = fn->decide_func(fci, calltemplates);
		err::reset();
		if(!decidedfn) {
			err::set(this, "function '%s' does not exist for type: %s",
				 oper.tok.str().c_str(), lhs->type->str().c_str());
			fci->args.clear();
			delete fci;
			return false;
		}
		if(type) delete type;
		type	       = decidedfn->rettype->copy();
		ValueMgr &vals = types.getParser()->getValueMgr();
		bool erred     = false;
		if(decidedfn->getIntrinsicFuncType() == IPARSE &&
		   !decidedfn->callIntrinsicFunc(types, vals, this, fci))
		{
			erred = true;
			err::set(this, "failed to call parse intrinsic "
				       "function during type assignment");
			goto fail;
		} else if(decidedfn->getIntrinsicFuncType() == IVALUE) {
			this->setIntrinsicFunc(decidedfn->getIntrinsicFunc());
		}
		if(!InitTemplateFn(types, this, (Type *&)decidedfn, calltemplates, false)) {
			erred = true;
			err::set(this, "failed to intialize template function");
			goto fail;
		}
		for(auto &t : calltemplates) delete t.second;
		setDecidedFuncID(decidedfn->id);
		fci->args.clear();
		delete fci;
		delete decidedfn;
	fail:
		if(erred) return false;
		break;
	}
	default: err::set(oper, "nonexistent operator"); return false;
	}
	if(commas > 0) {
		if(type) delete type;
		type = nullptr;
	}
	if(type->type == TFUNCMAP) return true;
	if(!isComptime() && lhs->isComptime() && (!rhs || rhs->isComptime())) setComptime(true);
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtVar ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVar::assignType(TypeMgr &types)
{
	if(val && val->stmt_type == FNDEF && as<StmtFnDef>(val)->sig->isMember()) {
		goto post_mangling;
	}
	name.data.s = GetMangledName(this, name);
post_mangling:
	if(isComptime() && !val && parent->stmt_type != FNSIG) {
		err::set(name, "'comptime' variables must have a value");
		return false;
	}
	if((!val || val->stmt_type != FNDEF) && types.exists(name.data.s, true, false)) {
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
			err::set(this,
				 "expression returns void, which cannot be assigned to a var");
			return false;
		}
	}
	if(vtype && val && !vtype->type->compatible(val->type, val)) {
		err::set(this, "incompatible given type and value of the variable decl");
		return false;
	}
	if(val) {
		type = val->type->copy();
		if(vtype) type->info |= vtype->type->info;
	} else if(vtype) {
		type = vtype->type->copy();
	}
	type->parent = this;
	if(isComptime() && parent->stmt_type != FNSIG &&
	   !assignValue(types, types.getParser()->getValueMgr()))
	{
		err::set(name, "unable to assign value to comptime variable");
		return false;
	}
	if((!val || val->stmt_type != STRUCTDEF) && type->type == TSTRUCT) {
		as<TypeStruct>(type)->is_def = false;
	}
	if(val && (val->stmt_type == FNDEF || val->stmt_type == EXTERN)) {
		return types.addFuncCopy(name.data.s, type);
	}
	return types.addCopy(name.data.s, type);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtFnSig /////////////////////////////////////////////
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
			err::set(p, "failed to assign type of this function param");
			return false;
		}
	}
	if(!rettype->assignType(types)) {
		err::set(rettype, "failed to assign function return type");
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
/////////////////////////////////////////// StmtFnDef /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnDef::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(!sig->assignType(types)) {
		err::set(sig, "failed to assign type to function signature");
		return false;
	}
	if(sig->templates.empty() && !sig->has_variadic && blk) {
		types.pushFunc(as<TypeFunc>(sig->type));
		if(!blk->assignType(types)) {
			err::set(blk, "failed to assign type in function block");
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
////////////////////////////////////////// StmtHeader /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtHeader::assignType(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtLib ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtLib::assignType(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtExtern /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExtern::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(!sig->assignType(types)) {
		err::set(sig, "failed to assign type to function signature");
		return false;
	}
	if(headers && !headers->assignType(types)) {
		err::set(headers, "failed to assign header type");
		return false;
	}
	if(libs && !libs->assignType(types)) {
		err::set(libs, "failed to assign lib type");
		return false;
	}
	type	     = sig->type->copy();
	type->parent = this;
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtEnum /////////////////////////////////////////////
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
/////////////////////////////////////////// StmtStruct ////////////////////////////////////////////
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
		std::string membername = f->name.data.s;
		if(!f->assignType(types)) {
			err::set(f->name, "unable to assign type of struct field");
			return false;
		}
		f->name.data.s = membername;
		field_type_orders.push_back(f->name.data.s);
	}
	std::unordered_map<std::string, Type *> field_types;
	for(size_t i = 0; i < field_type_orders.size(); ++i) {
		field_types[field_type_orders[i]] = fields[i]->type->copy();
	}
	type = new TypeStruct(this, 0, 0, templates.size(), field_type_orders, field_types);
	as<TypeStruct>(type)->is_def = true;
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtVarDecl ////////////////////////////////////////////
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
/////////////////////////////////////////// StmtCond //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtCond::assignType(TypeMgr &types)
{
	if(is_inline) {
		bool found = false;
		for(auto it = conds.begin(); it != conds.end();) {
			if(found) {
				delete it->cond;
				delete it->blk;
				it = conds.erase(it);
				continue;
			}
			if(!it->cond) {
				if(!it->blk->assignType(types)) {
					err::set(this, "failed to assign inline-else block type");
					return false;
				}
				it->blk->setValueUnique(types.getParser()->getValueMgr());
				break;
			}
			if(!it->cond->assignType(types)) {
				err::set(it->cond, "failed to assign inline condition type");
				return false;
			}
			if(!it->cond->isComptime()) {
				err::set(it->cond,
					 "inline conditional's condition must be comptime");
				return false;
			}
			if(!it->cond->assignValue(types, types.getParser()->getValueMgr())) {
				err::set(it->cond,
					 "failed to determine value of inline conditional");
				return false;
			}
			if(it->cond->value->i == 0) {
				delete it->cond;
				delete it->blk;
				it = conds.erase(it);
				continue;
			}
			if(!it->blk->assignType(types)) {
				err::set(this, "failed to assign inline-if block type");
				return false;
			}
			it->blk->setValueUnique(types.getParser()->getValueMgr());
			found = true;
			++it;
		}
		setParent(parent);
		return true;
	}
	for(auto &c : conds) {
		if(c.cond && !c.cond->assignType(types)) {
			err::set(c.cond, "failed to determine type of condition");
			return false;
		}
		if(c.cond && !c.cond->type->booleanCompatible()) {
			err::set(c.cond, "conditional does not return a numeric primitive/boolean");
			return false;
		}
		if(!c.blk->assignType(types)) {
			err::set(c.blk, "failed to determine type of block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtForIn /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtForIn::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(!in->assignType(types)) {
		err::set(in, "failed to determine type of 'in' expression");
		return false;
	}
	if(!types.addCopy(iter.data.s, in->type)) {
		err::set(iter, "variable '%s' already exists in this scope", iter.data.s.c_str());
		return false;
	}
	if(!blk->assignType(types)) {
		err::set(blk, "failed to determine type of block");
		return false;
	}
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFor::assignType(TypeMgr &types)
{
	types.pushLayer();
	if(init && !init->assignType(types)) {
		err::set(init, "failed to determine type of 'init' statement");
		return false;
	}
	if(cond && !cond->assignType(types)) {
		err::set(cond, "failed to determine type of 'condition' expression");
		return false;
	}
	if(incr && !incr->assignType(types)) {
		err::set(incr, "failed to determine type of 'increment' expression");
		return false;
	}
	if(is_inline) {
		if(init && !init->assignValue(types, types.getParser()->getValueMgr())) {
			err::set(this, "failed to assign init value");
			return false;
		}
		// init2 exists because init will be possibly changed after inline unfolding which
		// would render it useless
		Stmt *init2 = init ? init->copy(true) : nullptr;
		Pointer<Stmt> init2ptr(init2);
		init2->setValueUnique(types.getParser()->getValueMgr());
		if(init2) {
			init2->setParent(blk);
		}
		if(!blk || blk->stmts.empty()) {
			err::set(this, "no/empty block for inline-for");
			return false;
		}
		if(!cond) {
			err::set(this, "inline-for must have a comptime condition");
			return false;
		}
		if((!cond->isComptime())) {
			err::set(this, "inline-for must have a condition "
				       "that can be computed at comptime");
			return false;
		}
		if(incr && !incr->isComptime()) {
			err::set(this, "inline-for must have an increment statement "
				       "that can be computed at comptime");
			return false;
		}
		std::vector<Stmt *> newstmts;
		while(cond->assignValue(types, types.getParser()->getValueMgr()) &&
		      cond->value->i != 0) {
			StmtBlock *newblk = as<StmtBlock>(blk->copy());
			if(!newblk->assignType(types)) {
				err::set(this, "failed to determine block type");
				delete newblk;
				for(auto &n : newstmts) delete n;
				return false;
			}
			newblk->setValueUnique(types.getParser()->getValueMgr());
			newstmts.insert(newstmts.end(), newblk->stmts.begin(), newblk->stmts.end());
			newblk->stmts.clear();
			delete newblk;
			if(!incr) continue;
			Stmt *newincr	= incr->copy();
			newincr->parent = blk;
			if(!newincr->assignType(types)) {
				err::set(this, "failed to assign type"
					       " of for-increment statement");
				for(auto &n : newstmts) delete n;
				return false;
			}
			newstmts.push_back(newincr);
			if(!newincr->assignValue(types, types.getParser()->getValueMgr())) {
				err::set(this, "failed to determine value"
					       " of for-increment statement");
				for(auto &n : newstmts) delete n;
				return false;
			}
		}
		for(auto &s : blk->stmts) delete s;
		if(init) {
			init->mergeValues(init2);
			newstmts.insert(newstmts.begin(), init);
			init = nullptr;
		}
		blk->stmts = newstmts;
		types.popLayer();
		clearValue();
		setParent(parent);
		return true;
	}
	if(!blk->assignType(types)) {
		err::set(blk, "failed to determine type of block");
		return false;
	}
	types.popLayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtWhile /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtWhile::assignType(TypeMgr &types)
{
	if(cond && !cond->assignType(types)) {
		err::set(cond, "failed to determine type of 'condition' expression");
		return false;
	}
	if(!blk->assignType(types)) {
		err::set(blk, "failed to determine type of block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtRet::assignType(TypeMgr &types)
{
	if(val && !val->assignType(types)) {
		err::set(val, "failed to determine type of the return argument");
		return false;
	}
	Type *valtype = val ? val->type->copy() : types.getCopy("void", val);
	if(!types.hasFunc()) {
		err::set(this, "return statements can be in functions only");
		return false;
	}
	if(!types.getFunc()->rettype->compatible(valtype, val ? val : this)) {
		err::set(val ? val : this,
			 "function return type and deduced return type are"
			 " incompatible (function return type: %s, deduced: %s)",
			 types.getFunc()->rettype->str().c_str(), valtype->str().c_str());
		delete valtype;
		return false;
	}
	if(val && val->isComptime()) {
		setComptime(true);
	} else if(!val) {
		value = types.getParser()->getValueMgr().get(VVOID);
		setComptime(true);
	}
	type = valtype;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtContinue //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtContinue::assignType(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBreak::assignType(TypeMgr &types)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Extra Funcs ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

static bool InitTemplateFn(TypeMgr &types, Stmt *caller, Type *&calledfn,
			   std::unordered_map<std::string, Type *> &calltemplates,
			   const bool &has_va)
{
	if(calltemplates.empty() && !has_va) return true;
	assert(calledfn && "LHS has no type assigned!");
	// if this function has no definition (template intrinsic, extern, for example)
	// do nothing
	if(!calledfn->parent) return true;
	Stmt *templfnparent = calledfn->parent->getParentWithType(BLOCK);
	TypeFunc *origsig   = as<TypeFunc>(calledfn);
	if(!templfnparent) {
		err::set(caller, "function definition for specialization is not in a block!");
		return false;
	}
	Stmt *fndefvar = calledfn->parent->getParentWithType(VAR);
	if(!fndefvar) {
		err::set(caller, "could not find function definition's variable declaration!");
		return false;
	}

	// this id is used to put the correct specializations at template locations (in cleanup)
	static size_t specialized_id = 1;
	if(!fndefvar->getSpecializedID()) {
		fndefvar->setSpecializedID(specialized_id++);
	}

	fndefvar     = fndefvar->copy();
	StmtVar *var = as<StmtVar>(fndefvar);
	var->setParent(templfnparent);
	assert(var->val && var->val->stmt_type == FNDEF && var->val &&
	       "expected function definition as variable value for template initialization");
	StmtFnDef *fn = as<StmtFnDef>(var->val);
	if(!fn->blk) {
		delete fndefvar;
		return false;
	}
	if(caller->mod->getPath() == fn->mod->getPath()) {
		types.lockScopesBefore(origsig->scope);
	} else {
		err::pushModule(fn->mod);
	}
	types.pushLayer();
	types.pushFunc(origsig);
	// for each types add signature variables
	for(size_t i = 0; i < fn->sig->templates.size(); ++i) {
		const std::string &t = fn->sig->templates[i].data.s;
		if(calltemplates.find("@" + std::to_string(i)) == calltemplates.end()) {
			err::set(caller, "template type '%s' not found", t.c_str());
			delete fndefvar;
			return false;
		}
		types.add(t, calltemplates.at("@" + std::to_string(i)));
	}
	calltemplates.clear();
	fn->sig->templates.clear();
	fn->sig->has_variadic = false;
	if(origsig->args.size() > 0 && origsig->args.back()->type == TVARIADIC) {
		std::string tname	     = fn->sig->args.back()->vtype->getname();
		origsig->args.back()->parent = fn->sig->args.back();
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
		err::set(caller, "failed to specialize template function definition: %s",
			 calledfn->str().c_str());
		delete fndefvar;
		return false;
	}
	fn->sig->has_variadic = has_va;
	fn->type	      = fn->sig->type->copy();
	types.popFunc();
	types.popLayer();
	if(caller->mod->getPath() == fn->mod->getPath()) {
		types.unlockScope();
	} else {
		err::popModule();
	}
	var->type = fn->type->copy();
	var->setSpecialized(true);

	// lhs must point to correct type
	delete calledfn;
	calledfn	 = fn->type->copy();
	calledfn->parent = var;

	StmtBlock *tfnparent = as<StmtBlock>(templfnparent);
	tfnparent->stmts.push_back(var);
	return true;
}
static void ApplyTypeCoercion(StmtExpr *expr)
{
	if(!expr->lhs || !expr->rhs) return;
	if(expr->lhs->type->ptr > 0 || expr->rhs->type->ptr > 0) return;
	// the following check is also an assurance of lhs and rhs being TypeSimple
	if(!expr->lhs->type->primitiveCompatible() || !expr->rhs->type->primitiveCompatible())
		return;

	if(expr->oper.tok.val == lex::SUBS) return;

	StmtSimple *ls = as<StmtSimple>(expr->lhs);
	StmtSimple *rs = as<StmtSimple>(expr->rhs);

	TypeSimple *l = as<TypeSimple>(ls->type);
	TypeSimple *r = as<TypeSimple>(rs->type);

	if(l->id == r->id) return;

	if(expr->oper.tok.isAssign()) {
		rs->cast(l);
		return;
	}
	// 0 => lhs
	// 1 => rhs
	bool superior = ChooseSuperiorPrimitiveType(l, r);
	if(superior) {
		rs->cast(l);
	} else {
		ls->cast(r);
	}
	return;
}

static bool ChooseSuperiorPrimitiveType(TypeSimple *l, TypeSimple *r)
{
	static std::unordered_map<std::string, size_t> typeprec = {
	{"i1", 1},  {"i8", 2},	{"u8", 3},  {"i16", 4},	 {"u16", 5}, {"i32", 6},
	{"u32", 7}, {"i64", 8}, {"u64", 9}, {"f32", 10}, {"f64", 11}};

	return typeprec[l->name] > typeprec[r->name];
}
} // namespace parser
} // namespace sc