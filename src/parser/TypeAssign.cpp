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
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_block_t::assign_type(VarMgr &vars)
{
	vars.pushlayer();
	for(auto &s : stmts) {
		if(!s->assign_type(vars)) {
			err::set(s->line, s->col,
				 "failed to perform type analysis on this statement");
			return false;
		}
	}
	vars.poplayer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_type_t::assign_type(VarMgr &vars)
{
	for(size_t i = 0; i < templates.size(); ++i) {
		std::string tname = "@" + std::to_string(i);
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
	type_base_t *res = vars.get(name.front().data.s);
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
	case lex::VOID: vtyp = vars.get_copy("void"); break;
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL: vtyp = vars.get_copy("i1"); break;
	case lex::INT: vtyp = vars.get_copy("i32"); break;
	case lex::FLT: vtyp = vars.get_copy("f32"); break;
	case lex::CHAR: vtyp = vars.get_copy("u8"); break;
	case lex::STR: vtyp = vars.get_copy("*const u8"); break;
	case lex::IDEN:
		vtyp = vars.get_copy(val.data.s);
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
	if(rhs && !rhs->assign_type(vars)) {
		err::set(rhs->line, rhs->col, "failed to determine type of RHS");
		return false;
	}
	// TODO: or-var & or-blk
	switch(oper.tok.val) {
	case lex::FNCALL:
		assert(rhs && rhs->type == FNCALLINFO &&
		       "RHS for function call must be a call info (compiler failure)");
		if(lhs->vtyp->type != TFUNC && lhs->vtyp->type != TSTRUCT) {
			err::set(lhs->line, lhs->col,
				 "function call can be done only on a function or struct type");
			return false;
		}
		if(lhs->vtyp->type == TFUNC) {
			stmt_fndef_t *specialized_fn = nullptr;
			if(!update_fncall_types(lhs, static_cast<stmt_fncallinfo_t *>(rhs),
						specialized_fn)) {
				err::set(line, col, "failed to perform type check on function");
				return false;
			}
		}
		// TODO: check type
		vtyp = lhs->vtyp->copy();
		break;
	default: err::set(oper, "unimplemented operator"); return false;
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
	vars.pushlayer();
	if(in && !in->assign_type(vars)) {
		err::set(name, "unable to determine type of 'in'");
		return false;
	}
	if(in && in->vtyp->type != TSTRUCT && in->vtyp->type != TENUM) {
		err::set(name, "'in' only works for structures and enums");
		return false;
	}
	if(!in && vars.exists(name.data.s, true, false)) {
		err::set(name, "variable '%s' already exists in scope", name.data.s.c_str());
		return false;
	}
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

	std::string fullname = name.data.s; // includes mangling, if a function is present
	// if(vtyp->type == TFUNC) {
	// 	fullname += vtyp->mangled_name();
	// 	printf("storing as: %s\n", fullname.c_str());
	// }
	if(!in) return vars.add_copy(fullname, vtyp);

	if(in->vtyp->type == TSTRUCT) {
		type_struct_t *t = static_cast<type_struct_t *>(in->vtyp);
		if(t->has_field(fullname)) {
			err::set(name, "a field of this name already exists in struct");
			return false;
		}
		return t->add_field_copy(fullname, vtyp);
	} else if(in->vtyp->type == TENUM) {
		err::set(name, "unimplemented for enum");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// stmt_fndecl_params_t ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fndecl_params_t::assign_type(VarMgr &vars)
{
	for(auto &p : params) {
		if(!p->assign_type(vars)) {
			err::set(p->line, p->col, "failed to assign type of this function param");
			return false;
		}
	}
	return true;
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
	if(params && !params->assign_type(vars)) {
		err::set(params->line, params->col, "failed to assign type of the function params");
		return false;
	}
	if(!rettype->assign_type(vars)) {
		err::set(rettype->line, rettype->col, "failed to assign function return type");
		return false;
	}
	std::vector<type_base_t *> args;
	if(params) {
		for(auto &p : params->params) {
			args.push_back(p->vtyp->copy());
		}
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
	if(blk && !blk->assign_type(vars)) {
		err::set(blk->line, blk->col, "failed to assign type in function block");
		return false;
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
	vtyp = new type_struct_t(parent, 0, 0, templs, field_type_orders, field_types);
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
	vtyp = val ? val->vtyp->copy() : vars.get_copy("void");
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