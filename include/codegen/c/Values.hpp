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

#ifndef CODEGEN_C_VALUES_HPP
#define CODEGEN_C_VALUES_HPP

#include "parser/Stmts.hpp"
#include "parser/Value.hpp"

namespace sc
{
namespace codegen
{
std::string GetCValue(parser::Stmt *stmt, parser::Value *value, parser::Type *type);
} // namespace codegen
} // namespace sc

#endif // CODEGEN_C_VALUES_HPP