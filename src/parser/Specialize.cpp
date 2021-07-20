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
bool specialize_type(type_base_t *&src, const std::vector<type_base_t *> &templs,
		     const size_t &line, const size_t &col)
{
	type_simple_t *tsim = nullptr;
	type_struct_t *tst  = nullptr;
	type_func_t *tfn    = nullptr;
	type_base_t *copy   = nullptr;
	std::string idstr;
	size_t id;
	switch(src->type) {
	case TSIMPLE:
		tsim = static_cast<type_simple_t *>(src);
		if(tsim->name[0] != '@') return true; // check for template
		idstr = tsim->name;
		assert(*idstr.begin() == '@' && "template id must begin with an '@'");
		idstr.erase(idstr.begin());
		id = std::stoul(idstr);
		if(id >= templs.size()) {
			err::set(line, col, "id exceeds template size; id: %zu, template size: %zu",
				 id, templs.size());
			return false;
		}
		copy = templs[id]->copy();
		copy->ptr += src->ptr;
		copy->info |= src->info;
		delete src;
		src = copy;
		break;
	case TSTRUCT:
		copy = src->copy();
		tst  = static_cast<type_struct_t *>(copy);
		for(auto &f : tst->fields) {
			if(!specialize_type(f.second, templs, line, col)) {
				err::set(line, col, "failed to specialize struct field");
				return false;
			}
		}
		copy->ptr += src->ptr;
		copy->info |= src->info;
		delete src;
		src = copy;
		break;
	case TENUM: err::set(line, col, "unimplemented for enum"); return false;
	case TFUNC:
		copy = src->copy();
		tfn  = static_cast<type_func_t *>(copy);
		for(auto &a : tfn->args) {
			if(!specialize_type(a, templs, line, col)) {
				err::set(line, col, "failed to specialize function arg");
				return false;
			}
		}
		if(!specialize_type(tfn->rettype, templs, line, col)) {
			err::set(line, col, "failed to specialize function return type");
			return false;
		}
		// TODO: copy and then specialize
		if(tfn->parent && !tfn->parent->specialize(templs)) {
			err::set(line, col, "failed to specialize function definition");
			return false;
		}
		copy->ptr += src->ptr;
		copy->info |= src->info;
		delete src;
		src = copy;
		break;
	default: err::set(line, col, "unimplemented for unknown type"); return false;
	}
	return true;
}
bool update_type(type_base_t *&vtyp, type_base_t *newt)
{
	if(vtyp) delete vtyp;
	vtyp = newt->copy();
	return true;
}
bool update_type(type_base_t *&vtyp, const std::vector<type_base_t *> &templs, const size_t &line,
		 const size_t &col)
{
	if(!vtyp) return true;
	return specialize_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_block_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	for(auto &s : stmts) {
		if(!s->specialize(templs)) {
			err::set(line, col, "failed to perform type specialization on statement");
			return false;
		}
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_type_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(fn) {
		if(!fn->specialize(templs)) {
			err::set(line, col, "failed to specialize function type");
			return false;
		}
		return update_type(vtyp, fn->vtyp);
	}
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_simple_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// stmt_fncallinfo_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fncallinfo_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	for(auto &t : templates) {
		if(!t->specialize(templs)) {
			err::set(t->line, t->col, "failed to specialize template in function call");
			return false;
		}
	}
	for(auto &a : args) {
		if(!a->specialize(templs)) {
			err::set(a->line, a->col,
				 "failed to specialize templates in function call argument");
			return false;
		}
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_expr_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(lhs && !lhs->specialize(templs)) {
		err::set(lhs->line, lhs->col, "failed to specialize type of LHS");
		return false;
	}
	if(rhs && !rhs->specialize(templs)) {
		err::set(rhs->line, rhs->col, "failed to specialize type of RHS");
		return false;
	}
	// TODO: or-var & or-blk
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_var_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_var_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(in && !in->specialize(templs)) {
		err::set(name, "unable to specialize type of 'in'");
		return false;
	}
	if(val && !val->specialize(templs)) {
		err::set(name, "unable to specialize type of value of this variable");
		return false;
	}
	if(vtype && !vtype->specialize(templs)) {
		err::set(name, "unable to specialize type from the given type of this variable");
		return false;
	}
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// stmt_fndecl_params_t ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fndecl_params_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	for(auto &p : params) {
		if(!p->specialize(templs)) {
			err::set(p->line, p->col,
				 "failed to specialize type of this function param");
			return false;
		}
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fnsig_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(params && !params->specialize(templs)) {
		err::set(params->line, params->col,
			 "failed to specialize type of the function params");
		return false;
	}
	if(!rettype->specialize(templs)) {
		err::set(rettype->line, rettype->col, "failed to specialize function return type");
		return false;
	}
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fndef_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(!sig->specialize(templs)) {
		err::set(sig->line, sig->col, "failed to specialize type of function signature");
		return false;
	}
	if(blk && !blk->specialize(templs)) {
		err::set(blk->line, blk->col, "failed to specialize type in function block");
		return false;
	}
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_header_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_lib_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_extern_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(!sig->specialize(templs)) {
		err::set(sig->line, sig->col, "failed to specialize type of function signature");
		return false;
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_enumdef_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_struct_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	for(auto &f : fields) {
		if(!f->specialize(templs)) {
			err::set(f->name, "unable to specialize type of struct field");
			return false;
		}
	}
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_vardecl_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	for(auto &d : decls) {
		if(!d->specialize(templs)) {
			err::set(d->name, "failed to specialize type of this variable declaration");
			return false;
		}
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cond_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	for(auto &c : conds) {
		if(!c.cond->specialize(templs)) {
			err::set(c.cond->line, c.cond->col,
				 "failed to specialize type of condition");
			return false;
		}
		if(!c.blk->specialize(templs)) {
			err::set(c.blk->line, c.blk->col, "failed to specialize type of block");
			return false;
		}
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_forin_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(!in->specialize(templs)) {
		err::set(in->line, in->col, "failed to specialize type of 'in' expression");
		return false;
	}
	if(!blk->specialize(templs)) {
		err::set(blk->line, blk->col, "failed to specialize type of block");
		return false;
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_for_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(init && !init->specialize(templs)) {
		err::set(init->line, init->col, "failed to specialize type of 'init' statement");
		return false;
	}
	if(cond && !cond->specialize(templs)) {
		err::set(cond->line, cond->col,
			 "failed to specialize type of 'condition' expression");
		return false;
	}
	if(incr && !incr->specialize(templs)) {
		err::set(incr->line, incr->col,
			 "failed to specialize type of 'increment' expression");
		return false;
	}
	if(!blk->specialize(templs)) {
		err::set(blk->line, blk->col, "failed to specialize type of block");
		return false;
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_while_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(cond && !cond->specialize(templs)) {
		err::set(cond->line, cond->col,
			 "failed to specialize type of 'condition' expression");
		return false;
	}
	if(!blk->specialize(templs)) {
		err::set(blk->line, blk->col, "failed to specialize type of block");
		return false;
	}
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_ret_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	if(val && !val->specialize(templs)) {
		err::set(val->line, val->col, "failed to specialize type of the return argument");
		return false;
	}
	is_specialized = true;
	return update_type(vtyp, templs, line, col);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cont_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	is_specialized = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_break_t::specialize(const std::vector<type_base_t *> &templs)
{
	if(is_specialized) return true;
	is_specialized = true;
	return true;
}
} // namespace parser
} // namespace sc