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

#ifndef PARSER_HPP
#define PARSER_HPP

#include <cstddef>

#include "Lex.hpp"
#include "parser/Parse.hpp"

namespace sc
{
namespace parser
{
// on successful parse, returns true, and tree is allocated
bool parse(const std::string &file, std::vector<lex::Lexeme> &toks, stmt_block_t *&tree);
} // namespace parser
} // namespace sc

#endif // PARSER_HPP