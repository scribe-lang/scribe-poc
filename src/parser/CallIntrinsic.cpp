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

#include "Error.hpp"
#include "parser/Type.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_block_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &s : stmts) {
		if(!s->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for statement in block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_type_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(fn && !fn->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for function type");
		return false;
	}
	for(auto &c : counts) {
		if(!c->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for array subscript");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_simple_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// stmt_fncallinfo_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fncallinfo_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &t : templates) {
		if(!t->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for template");
			return false;
		}
	}
	for(auto &a : args) {
		if(!a->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for argument");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_expr_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(lhs && !lhs->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for LHS");
		return false;
	}
	if(rhs && !rhs->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for LHS");
		return false;
	}
	// TODO: or-var & or-blk
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_var_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_var_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(in && !in->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for 'in'");
		return false;
	}
	if(val && !val->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for 'val'");
		return false;
	}
	if(vtype && !vtype->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for 'type'");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// stmt_fndecl_params_t ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fndecl_params_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &p : params) {
		if(!p->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for parameter");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fnsig_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(params && !params->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for parameters");
		return false;
	}
	if(rettype && !rettype->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for return type");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_fndef_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(!sig->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for function signature");
		return false;
	}
	if(blk && !blk->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_header_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_lib_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_extern_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(!sig->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for function signature");
		return false;
	}
	if(headers && !headers->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for headers");
		return false;
	}
	if(libs && !libs->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for libs");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_enumdef_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &i : items) {
		if(!i->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for enum item");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_struct_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &f : fields) {
		if(!f->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for struct field");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_vardecl_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &d : decls) {
		if(!d->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for var decl");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cond_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &c : conds) {
		if(c.cond && !c.cond->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for condition");
			return false;
		}
		if(!c.blk->call_intrinsic(vars)) {
			err::set(line, col, "failed to call intrinsic for block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_forin_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(!in->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for 'in' in foreach");
		return false;
	}
	if(!blk->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_for_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(init && !init->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for for loop init");
		return false;
	}
	if(cond && !cond->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for for loop cond");
		return false;
	}
	if(incr && !incr->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for for loop incr");
		return false;
	}
	if(!blk->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_while_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(cond && !cond->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for for loop cond");
		return false;
	}
	if(!blk->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_ret_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(val && !val->call_intrinsic(vars)) {
		err::set(line, col, "failed to call intrinsic for return value");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_cont_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool stmt_break_t::call_intrinsic(VarMgr &vars)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(vars, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}
} // namespace parser
} // namespace sc