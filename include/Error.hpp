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

#include <string>

#include "Lex.hpp"

namespace sc
{
namespace err
{
enum EType
{
	WARN,
	FAIL,
};
void set(const size_t &line, const size_t &col_beg, const size_t &col_end, const std::string &e,
	 const EType &type = FAIL);
inline void set(const lex::Lexeme &tok, const std::string &e, const EType &type = FAIL)
{
	set(tok.line, tok.col_beg, tok.col_end, e, type);
}
bool present();
void show(FILE *f, const std::string &data, const std::string &filename);
} // namespace err
} // namespace sc

#endif // ERROR_HPP