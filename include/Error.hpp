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

#ifndef ERROR_HPP
#define ERROR_HPP

#include <cassert>
#include <cstdarg>
#include <string>

#include "Lex.hpp"
#include "Parser.hpp"

namespace sc
{
namespace err
{
void pushModule(parser::Module *mod);
void popModule();
void set(parser::Stmt *stmt, const char *e, ...);
void set(const lex::Lexeme &tok, const char *e, ...);
void set(const size_t &line, const size_t &col_beg, const size_t &col_end, const char *e, ...);
void set(parser::Module *mod, const size_t &line, const size_t &col_beg, const size_t &col_end,
	 const char *e, va_list args);

// equivalent to set(), but for warnings
void setw(parser::Stmt *stmt, const char *e, ...);
void setw(const lex::Lexeme &tok, const char *e, ...);
void setw(const size_t &line, const size_t &col_beg, const size_t &col_end, const char *e, ...);
void setw(parser::Module *mod, const size_t &line, const size_t &col_beg, const size_t &col_end,
	  const char *e, va_list args);
bool present();
void show(FILE *f);
void reset();
} // namespace err
} // namespace sc

#endif // ERROR_HPP