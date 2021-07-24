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
#include "parser/Stmts.hpp"
#include "parser/Type.hpp"
#include "parser/VarMgr.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_block_t::executecomptime(VarMgr &vars)
{
	vars.pushlayer();
	std::vector<stmt_base_t *> newstmts;
	for(auto &s : stmts) {
		stmt_base_t *r = s->executecomptime(vars);
		if(!r) {
			err::set(line, col, "failed to execute comptime block");
			return nullptr;
		}
	}
	vars.poplayer();
	return new stmt_block_t(src_id, line, col, newstmts);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_type_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_simple_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// stmt_fncallinfo_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fncallinfo_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_expr_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_var_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_var_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fnsig_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fndef_t::executecomptime(VarMgr &vars)
{
	// this->disp(false);
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_header_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_lib_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_extern_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_enumdef_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_struct_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_vardecl_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_cond_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_forin_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_for_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_while_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_ret_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_cont_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_break_t::executecomptime(VarMgr &vars)
{
	return copy(true);
}
} // namespace parser
} // namespace sc