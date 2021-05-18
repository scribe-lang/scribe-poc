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

#ifndef PARSER_PARSE_HPP
#define PARSER_PARSE_HPP

#include "ParseHelper.hpp"
#include "Stmts.hpp"

namespace sc
{
namespace parser
{
enum class Occurs
{
	YES,
	NO,
	MAYBE
};
// on successful parse, returns true, and tree is allocated
// if with_brace is true, it will attempt to find the beginning and ending brace for each block
bool parse_block(ParseHelper &p, stmt_block_t *&tree, const bool &with_brace = true);

bool parse_type(ParseHelper &p, stmt_type_t *&type);
bool parse_simple(ParseHelper &p, stmt_base_t *&data);

bool parse_expr(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_17(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_16(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_15(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_14(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_13(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_12(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_11(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_10(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_09(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_08(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_07(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_06(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_05(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_04(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_03(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_02(ParseHelper &p, stmt_base_t *&expr);
bool parse_expr_01(ParseHelper &p, stmt_base_t *&expr);

bool parse_var(ParseHelper &p, stmt_var_t *&var, const Occurs &otype, const Occurs &oin,
	       const Occurs &oval);

bool parse_fncall(ParseHelper &p, stmt_base_t *&fn, const bool &is_mem);
bool parse_fndecl_params(ParseHelper &p, stmt_fndecl_params_t *&fparams);
bool parse_fnsig(ParseHelper &p, stmt_base_t *&fsig);
bool parse_fndef(ParseHelper &p, stmt_base_t *&fndef);

bool parse_header(ParseHelper &p, stmt_header_t *&header);
bool parse_lib(ParseHelper &p, stmt_lib_t *&lib);
bool parse_extern(ParseHelper &p, stmt_base_t *&ext);

bool parse_struct(ParseHelper &p, stmt_base_t *&sd);

bool parse_vardecl(ParseHelper &p, stmt_base_t *&vd); // combines VAR_DECL_BASE and VAR_DECL

bool parse_conds(ParseHelper &p, stmt_base_t *&conds);
bool parse_forin(ParseHelper &p, stmt_base_t *&fin);
bool parse_for(ParseHelper &p, stmt_base_t *&f);
bool parse_while(ParseHelper &p, stmt_base_t *&w);
bool parse_ret(ParseHelper &p, stmt_base_t *&ret);
bool parse_continue(ParseHelper &p, stmt_base_t *&cont);
bool parse_break(ParseHelper &p, stmt_base_t *&brk);
} // namespace parser
} // namespace sc

#endif // PARSER_PARSE_HPP