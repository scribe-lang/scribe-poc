/*
	MIT License
	Copyright (c) 2021 Scribe Language Repositories
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#ifndef CODEGEN_C_TYPES_HPP
#define CODEGEN_C_TYPES_HPP

#include "parser/Stmts.hpp"
#include "parser/Type.hpp"

namespace sc
{
namespace codegen
{
std::string GetCType(parser::Stmt *stmt, parser::Type *type);
} // namespace codegen
} // namespace sc

#endif // CODEGEN_C_TYPES_HPP