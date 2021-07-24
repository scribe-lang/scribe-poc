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

namespace sc
{
namespace parser
{
static inline TypeFunc *func(const std::vector<Type *> &args, Type *rettype)
{
	return new TypeFunc(nullptr, 0, 0, 0, 0, false, args, rettype);
}
void add_primitive_integer_funcs(const std::string &typname, TypeMgr &types)
{
	std::vector<std::string> alltypes = {"i1",  "i8",  "i16", "i32", "i64", "u8",
					     "u16", "u32", "u64", "f32", "f64"};

	TypeSimple *type   = static_cast<TypeSimple *>(types.get(typname, nullptr));
	TypeSimple *i1type = static_cast<TypeSimple *>(types.get("i1", nullptr));
	for(auto &t : alltypes) {
		TypeSimple *type2 = static_cast<TypeSimple *>(types.get(t, nullptr));

		types.add_func("=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("+", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("-", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("*", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("/", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("%", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("+=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("-=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("*=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("/=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("%=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("&&", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func("||", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func("==", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func("<", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func(">", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func("<=", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func(">=", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func("!=", func({type->copy(), type2->copy()}, i1type->copy()), true);
		types.add_func("&", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("|", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("^", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("&=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("|=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("~=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("^=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("<<", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func(">>", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func("<<=", func({type->copy(), type2->copy()}, type->copy()), true);
		types.add_func(">>=", func({type->copy(), type2->copy()}, type->copy()), true);
	}
	types.add_func("x++", func({type->copy()}, type->copy()), true);
	types.add_func("++x", func({type->copy()}, type->copy()), true);
	types.add_func("x--", func({type->copy()}, type->copy()), true);
	types.add_func("--x", func({type->copy()}, type->copy()), true);
	types.add_func("u+", func({type->copy()}, type->copy()), true);
	types.add_func("u-", func({type->copy()}, type->copy()), true);
	types.add_func("!", func({type->copy()}, i1type->copy()), true);
	types.add_func("~", func({type->copy()}, type->copy()), true);
}
} // namespace parser
} // namespace sc