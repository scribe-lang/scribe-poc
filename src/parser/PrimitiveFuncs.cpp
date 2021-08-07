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

#include "parser/PrimitiveFuncs.hpp"

#include "parser/Intrinsics.hpp"

namespace sc
{
namespace parser
{
static inline TypeFunc *func(TypeMgr &types, const std::vector<Type *> &args, Type *rettype)
{
	return new TypeFunc(nullptr, 0, 0, 0, 0, false, args, rettype);
}
void add_primitive_integer_funcs(TypeMgr &types)
{
	std::vector<std::string> alltypes = {"i1",  "i8",  "i16", "i32", "i64", "u8",
					     "u16", "u32", "u64", "f32", "f64"};

	TypeSimple *t0 = nullptr;
	TypeSimple *t1 = nullptr;
	TypeSimple *t2 = nullptr;
	TypeFunc *fn   = nullptr;

#include "./PrimitiveFuncs/Arithmetic.def"
#include "./PrimitiveFuncs/ArithmeticAssn.def"
#include "./PrimitiveFuncs/Logical.def"
#include "./PrimitiveFuncs/UnaryPostAssn.def"
#include "./PrimitiveFuncs/UnaryPre.def"
#include "./PrimitiveFuncs/UnaryPreAssn.def"
}
} // namespace parser
} // namespace sc

// TODO: correct the intrin_gen.fer script - such that it generates the include and src files
// simultaneously