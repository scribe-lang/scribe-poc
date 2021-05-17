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

#ifndef PARSER_STMTS_HPP
#define PARSER_STMTS_HPP

#include "Lex.hpp"

namespace sc
{
namespace parse
{
enum StmtType
{
	BLOCK,
	TYPE,
	EXPR,
	FNDEF,
	ENUMDEF,
	STRUCTDEF,
	COMPTIME,
	EXTERN,
	VARDECL,
	COND,
	FOR,
	WHILE,
	RET,
	CONTINUE,
	BREAK,
	EXPR_COLS,
};

struct stmt_base_t
{
	StmtType type;
	size_t line;
	size_t col_beg, col_end;
	stmt_base_t(const StmtType &type, const size_t &line, const size_t &col_beg,
		    const size_t &col_end);
	virtual void disp(FILE *f) = 0;
};

struct stmt_block_t
{
	std::vector<stmt_base_t *> stmts;
	stmt_block_t(const size_t &line, const size_t &col_beg, const size_t &col_end);
};
} // namespace parse
} // namespace sc

#endif // PARSER_STMTS_HPP