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

#ifndef PARSER_PRIMITIVE_FUNCS_HPP
#define PARSER_PRIMITIVE_FUNCS_HPP

#include <string>
#include <unordered_map>

#include "TypeMgr.hpp"

namespace sc
{
namespace parser
{
void add_primitive_integer_funcs(TypeMgr &types);
} // namespace parser
} // namespace sc

#endif // PARSER_PRIMITIVE_FUNCS_HPP