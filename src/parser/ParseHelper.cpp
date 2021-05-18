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

#include "parser/ParseHelper.hpp"

namespace sc
{
namespace parser
{
ParseHelper::ParseHelper(std::vector<lex::Lexeme> &toks, const size_t begin)
	: toks(toks), invalid(0, 0, 0, lex::INVALID), eof(0, 0, 0, lex::FEOF), idx(begin)
{}

lex::Lexeme &ParseHelper::peak(const int offset)
{
	if(offset < 0 && idx < (-offset)) return eof;
	if(idx + offset >= toks.size()) return eof;
	return toks[idx + offset];
}

lex::TokType ParseHelper::peakt(const int offset) const
{
	if(offset < 0 && idx < (-offset)) return eof.tok.val;
	if(idx + offset >= toks.size()) return eof.tok.val;
	return toks[idx + offset].tok.val;
}

lex::Lexeme &ParseHelper::next()
{
	++idx;
	if(idx >= toks.size()) return eof;
	return toks[idx];
}

lex::TokType ParseHelper::nextt()
{
	++idx;
	if(idx >= toks.size()) return eof.tok.val;
	return toks[idx].tok.val;
}

lex::Lexeme &ParseHelper::prev()
{
	if(idx == 0) return invalid;
	--idx;
	return toks[idx];
}

lex::TokType ParseHelper::prevt()
{
	if(idx == 0) return invalid.tok.val;
	--idx;
	return toks[idx].tok.val;
}

const lex::Lexeme *ParseHelper::at(const size_t &idx) const
{
	if(idx >= toks.size()) return &invalid;
	return &toks[idx];
}
} // namespace parser
} // namespace sc