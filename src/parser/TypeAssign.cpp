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
#include "parser/VarMgr.hpp"

namespace sc
{
namespace parser
{
static bool init_templ_func(stmt_base_t *lhs, const std::vector<type_base_t *> &calltemplates)
{
	if(calltemplates.empty()) return true;
	stmt_base_t *templfnparent = lhs->vtyp->parent;
	while(templfnparent && templfnparent->type != BLOCK) {
		templfnparent = templfnparent->parent;
	}
	if(!templfnparent) {
		err::set(lhs->line, lhs->col,
			 "function definition for specialization is not in a block!");
		return false;
	}
	stmt_base_t *tmp = lhs->vtyp->parent;
	while(tmp && tmp->type != VAR) {
		tmp = tmp->parent;
	}
	if(!tmp) {
		err::set(lhs->line, lhs->col,
			 "could not find function definition's variable declaration!");
		return false;
	}
	tmp = tmp->copy();
	if(!tmp->specialize(calltemplates)) {
		err::set(lhs->line, lhs->col,
			 "failed to specialize template function definition: %s",
			 lhs->vtyp->str().c_str());
		return false;
	}
	lhs->vtyp->parent = tmp;
	printf("here's the all new template deduced function\n");
	stmt_block_t *tfnparent = static_cast<stmt_block_t *>(templfnparent);
	tfnparent->stmts.push_back(tmp);
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_block_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	for(size_t i = 0; i < stmts.size(); ++i) {
		auto &s = stmts[i];
		if(s->is_specialized) continue;
		if(!s->assign_type(vars)) {
			err::set(s->line, s->col,
				 "failed to perform type analysis on this statement");
			return false;
		}
	}
	if(parent) vars.poplayer(); // do not remove the top layer if this block is top level
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_type_t::assign_type(VarMgr &vars)
{
	for(size_t i = 0; i < templates.size(); ++i) {
		std::string tname = "@" + std::to_string(i);
		if(vars.exists(templates[i].data.s, false, false)) continue;
		vars.add(templates[i].data.s, new type_simple_t(0, 0, true, tname));
	}
	if(func) {
		if(!fn->assign_type(vars)) {
			err::set(line, col, "failed to determine type from the function type");
			return false;
		}
		vtyp = fn->vtyp->copy();
		return true;
	}
	type_base_t *res = vars.get(name.front().data.s, this);
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
		res = ((type_struct_t *)res)->get_field(name[i].data.s);
		if(!res) {
			err::set(name[i], "variable '%s' does not exist", name[i].data.s.c_str());
			return false;
		}
	}
	vtyp = res->copy();
	for(auto &c : counts) {
		if(!c->assign_type(vars)) {
			err::set(c->line, c->col, "failed to determine type of this statement");
			return false;
		}
		vtyp->counts.push_back(c->vtyp->copy());
	}
	vtyp->info = info;
	vtyp->ptr += ptr;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_simple_t::assign_type(VarMgr &vars)
{
	switch(val.tok.val) {
	case lex::VOID: vtyp = vars.get_copy("void", this); break;
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL: vtyp = vars.get_copy("i1", this); break;
	case lex::INT: vtyp = vars.get_copy("i32", this); break;
	case lex::FLT: vtyp = vars.get_copy("f32", this); break;
	case lex::CHAR: vtyp = vars.get_copy("u8", this); break;
	case lex::STR: vtyp = vars.get_copy("*const u8", this); break;
	case lex::IDEN:
		vtyp = vars.get_copy(val.data.s, this);
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

bool stmt_fncallinfo_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	for(auto &t : templates) {
		if(!t->assign_type(vars)) {
			err::set(t->line, t->col, "failed to determine type of template");
			return false;
		}
	}
	for(auto &a : args) {
		if(!a->assign_type(vars)) {
			err::set(a->line, a->col, "failed to determine type of argument");
			return false;
		}
	}
	vars.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_expr_t::assign_type(VarMgr &vars)
{
	if(lhs && !lhs->assign_type(vars)) {
		err::set(lhs->line, lhs->col, "failed to determine type of LHS");
		return false;
	}
	if(oper.tok.val != lex::DOT && rhs && !rhs->assign_type(vars)) {
		err::set(rhs->line, rhs->col, "failed to determine type of RHS");
		return false;
	}
	// TODO: or-var & or-blk
	switch(oper.tok.val) {
	case lex::DOT: {
		assert(rhs->type == SIMPLE && "RHS for dot MUST be a simple type");
		if(lhs->vtyp->type != TSTRUCT) {
			err::set(line, col,
				 "LHS must be a structure to use the dot operator, found: %s",
				 lhs->vtyp->str().c_str());
			return false;
		}
		type_struct_t *lst = static_cast<type_struct_t *>(lhs->vtyp);
		if(lst->is_def) {
			err::set(line, col,
				 "cannot use dot operator on a struct"
				 " definition; instantiate it first");
			return false;
		}
		stmt_simple_t *rsim = static_cast<stmt_simple_t *>(rhs);
		type_base_t *res    = lst->get_field(rsim->val.data.s);
		if(!res && !(res = vars.get_funcmap_copy(rsim->val.data.s, this))) {
			err::set(line, col, "no function or struct (%s) field named '%s' exists",
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
		std::vector<type_base_t *> calltemplates;
		if(lhs->vtyp->type != TFUNC && lhs->vtyp->type != TSTRUCT &&
		   lhs->vtyp->type != TFUNCMAP) {
			err::set(lhs->line, lhs->col,
				 "function call can be performed "
				 "only on a function or struct type, attempted on: %s",
				 lhs->vtyp->str().c_str());
			return false;
		}
		if(lhs->vtyp->type == TFUNCMAP) {
			type_funcmap_t *fmap = static_cast<type_funcmap_t *>(lhs->vtyp);
			if(!(vtyp = fmap->decide_func(finfo, calltemplates))) {
				err::set(line, col,
					 "failed to decide the function "
					 "to execute, need more info");
				return false;
			}
			delete lhs->vtyp;
			lhs->vtyp = vtyp;
			vtyp	  = static_cast<type_func_t *>(lhs->vtyp)->rettype->copy();
		} else if(lhs->vtyp->type == TFUNC) {
			type_func_t *oldfn = static_cast<type_func_t *>(lhs->vtyp);
			type_func_t *fn	   = nullptr;
			if(!(fn = oldfn->specialize_compatible_call(finfo, calltemplates))) {
				err::set(line, col,
					 "function '%s' incompatible with call arguments",
					 oldfn->str().c_str());
				return false;
			}
			delete oldfn;
			lhs->vtyp = fn;
			if(!fn->intrin_fn) vtyp = fn->rettype->copy();
			if(fn->intrin_fn && !fn->call_intrinsic(vars, this)) {
				err::set(line, col,
					 "failed to call intrinsic "
					 "function during type assignment");
				return false;
			}
			if(!vtyp) vtyp = fn->rettype->copy();
		} else if(lhs->vtyp->type == TSTRUCT) {
			type_struct_t *st = static_cast<type_struct_t *>(lhs->vtyp);
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
			break; // no need to clone the struct
		}
		// apply stmt template specialization
		if(!init_templ_func(lhs, calltemplates)) return false;
		break;
	}
	case lex::SUBS: err::set(line, col, "unimplemented subscript"); return false;
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
		stmt_base_t *tmp = lhs;
		lhs		 = rhs;
		rhs		 = tmp;
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
		type_funcmap_t *fn = vars.get_funcmap(oper.tok.str(), this);
		if(!fn) {
			err::set(line, col, "function '%s' does not exist", oper.tok.str().c_str());
			return false;
		}
		stmt_fncallinfo_t *fci = new stmt_fncallinfo_t(line, col, {}, {lhs});
		if(rhs) fci->args.push_back(rhs);
		std::vector<type_base_t *> calltemplates;
		type_func_t *tmp = fn->decide_func(fci, calltemplates);
		if(!tmp) {
			err::set(line, col, "function '%s' does not exist for type: %s",
				 oper.tok.str().c_str(), lhs->vtyp->str().c_str());
			delete fci;
			return false;
		}
		if(!init_templ_func(lhs, calltemplates)) return false;
		fci->args.clear();
		vtyp = static_cast<type_func_t *>(tmp)->rettype->copy();
		delete fci;
		delete tmp;
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

bool stmt_var_t::assign_type(VarMgr &vars)
{
	if(vars.exists(name.data.s, true, false)) {
		err::set(name, "variable '%s' already exists in scope", name.data.s.c_str());
		return false;
	}
	vars.pushlayer();
	if(val && !val->assign_type(vars)) {
		err::set(name, "unable to determine type of value of this variable");
		return false;
	}
	if(vtype && !vtype->assign_type(vars)) {
		err::set(name, "unable to determine type from the given type of this variable");
		return false;
	}
	// TODO: if(val && vtype && !val->vtyp->supports_init(vtype->vtyp)) return false;
	if(vtype) {
		vtyp = vtype->vtyp->copy();
	} else if(val) {
		vtyp = val->vtyp->copy();
	}
	vars.poplayer();
	if(val && val->type == FNDEF) return vars.add_func_copy(name.data.s, vtyp);
	return vars.add_copy(name.data.s, vtyp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fnsig_t::assign_type(VarMgr &vars)
{
	std::vector<std::string> templs;
	for(size_t i = 0; i < templates.size(); ++i) {
		std::string tname = "@" + std::to_string(i);
		vars.add(templates[i].data.s, new type_simple_t(parent, 0, 0, tname));
		templs.push_back(tname);
	}
	for(auto &p : params) {
		if(!p->assign_type(vars)) {
			err::set(p->line, p->col, "failed to assign type of this function param");
			return false;
		}
	}
	if(!rettype->assign_type(vars)) {
		err::set(rettype->line, rettype->col, "failed to assign function return type");
		return false;
	}
	std::vector<type_base_t *> args;
	for(auto &p : params) {
		args.push_back(p->vtyp->copy());
	}
	vtyp = new type_func_t(this, 0, 0, templs, args, rettype->vtyp->copy());
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fndef_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	if(!sig->assign_type(vars)) {
		err::set(sig->line, sig->col, "failed to assign type to function signature");
		return false;
	}
	if(sig->templates.empty() && blk) {
		vars.pushfret(sig->rettype->vtyp);
		if(!blk->assign_type(vars)) {
			err::set(blk->line, blk->col, "failed to assign type in function block");
			return false;
		}
		vars.popfret();
	}
	vtyp	     = sig->vtyp->copy();
	vtyp->parent = this;
	vars.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_header_t::assign_type(VarMgr &vars)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_lib_t::assign_type(VarMgr &vars)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_extern_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	if(!sig->assign_type(vars)) {
		err::set(sig->line, sig->col, "failed to assign type to function signature");
		return false;
	}
	if(headers && !headers->assign_type(vars)) {
		err::set(headers->line, headers->col, "failed to assign header type");
		return false;
	}
	if(libs && !libs->assign_type(vars)) {
		err::set(libs->line, libs->col, "failed to assign lib type");
		return false;
	}
	vars.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_enumdef_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	for(auto &i : items) {
		if(!i->assign_type(vars)) {
			err::set(i->line, i->col, "failed to assign type to enum");
			return false;
		}
	}
	vars.poplayer();
	// TODO: create vtyp
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_struct_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	std::vector<std::string> templs;
	for(size_t i = 0; i < templates.size(); ++i) {
		std::string tname = "@" + std::to_string(i);
		vars.add(templates[i].data.s, new type_simple_t(0, 0, true, tname));
		templs.push_back(tname);
	}
	std::vector<std::string> field_type_orders;
	for(auto &f : fields) {
		if(!f->assign_type(vars)) {
			err::set(f->name, "unable to assign type of struct field");
			return false;
		}
		field_type_orders.push_back(f->name.data.s);
	}
	std::unordered_map<std::string, type_base_t *> field_types;
	for(size_t i = 0; i < field_type_orders.size(); ++i) {
		field_types[field_type_orders[i]] = fields[i]->vtyp->copy();
	}
	vtyp = new type_struct_t(this, 0, 0, false, templs, field_type_orders, field_types);
	vars.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_vardecl_t::assign_type(VarMgr &vars)
{
	for(auto &d : decls) {
		if(!d->assign_type(vars)) {
			err::set(d->name, "failed to determine type of this variable declaration");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cond_t::assign_type(VarMgr &vars)
{
	for(auto &c : conds) {
		if(!c.cond->assign_type(vars)) {
			err::set(c.cond->line, c.cond->col,
				 "failed to determine type of condition");
			return false;
		}
		if(!c.blk->assign_type(vars)) {
			err::set(c.blk->line, c.blk->col, "failed to determine type of block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_forin_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	if(!in->assign_type(vars)) {
		err::set(in->line, in->col, "failed to determine type of 'in' expression");
		return false;
	}
	if(!vars.add_copy(iter.data.s, in->vtyp)) {
		err::set(iter, "variable '%s' already exists in this scope", iter.data.s.c_str());
		return false;
	}
	if(!blk->assign_type(vars)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	vars.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_for_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	if(init && !init->assign_type(vars)) {
		err::set(init->line, init->col, "failed to determine type of 'init' statement");
		return false;
	}
	if(cond && !cond->assign_type(vars)) {
		err::set(cond->line, cond->col,
			 "failed to determine type of 'condition' expression");
		return false;
	}
	if(incr && !incr->assign_type(vars)) {
		err::set(incr->line, incr->col,
			 "failed to determine type of 'increment' expression");
		return false;
	}
	if(!blk->assign_type(vars)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	vars.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_while_t::assign_type(VarMgr &vars)
{
	if(cond && !cond->assign_type(vars)) {
		err::set(cond->line, cond->col,
			 "failed to determine type of 'condition' expression");
		return false;
	}
	if(!blk->assign_type(vars)) {
		err::set(blk->line, blk->col, "failed to determine type of block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_ret_t::assign_type(VarMgr &vars)
{
	if(val && !val->assign_type(vars)) {
		err::set(val->line, val->col, "failed to determine type of the return argument");
		return false;
	}
	type_base_t *valtype = val ? val->vtyp->copy() : vars.get_copy("void", parent);
	if(!vars.hasfret()) {
		err::set(line, col, "return statements can be in functions only");
		return false;
	}
	if(!vars.getfret()->compatible(valtype, val ? val->line : line, val ? val->col : col)) {
		err::set(val ? val->line : line, val ? val->col : col,
			 "function return type and deduced return type are"
			 " incompatible (function return type: %s, deduced: %s)",
			 vars.getfret()->str().c_str(), valtype->str().c_str());
		delete valtype;
		return false;
	}
	vtyp = valtype;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cont_t::assign_type(VarMgr &vars)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_break_t::assign_type(VarMgr &vars)
{
	return true;
}
} // namespace parser
} // namespace sc