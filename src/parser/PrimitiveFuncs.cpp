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
static inline type_func_t *func(const std::vector<type_base_t *> &args, type_base_t *rettype)
{
	return new type_func_t(nullptr, 0, 0, 0, 0, false, args, rettype);
}
void add_primitive_integer_funcs(const std::string &typname, VarMgr &vars)
{
	std::vector<std::string> alltypes = {"i1",  "i8",  "i16", "i32", "i64", "u8",
					     "u16", "u32", "u64", "f32", "f64"};

	type_simple_t *type   = static_cast<type_simple_t *>(vars.get(typname, nullptr));
	type_simple_t *i1type = static_cast<type_simple_t *>(vars.get("i1", nullptr));
	for(auto &t : alltypes) {
		type_simple_t *type2 = static_cast<type_simple_t *>(vars.get(t, nullptr));

		vars.add_func("=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("+", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("-", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("*", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("/", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("%", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("+=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("-=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("*=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("/=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("%=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("&&", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func("||", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func("==", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func("<", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func(">", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func("<=", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func(">=", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func("!=", func({type->copy(), type2->copy()}, i1type->copy()), true);
		vars.add_func("&", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("|", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("^", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("&=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("|=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("~=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("^=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("<<", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func(">>", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func("<<=", func({type->copy(), type2->copy()}, type->copy()), true);
		vars.add_func(">>=", func({type->copy(), type2->copy()}, type->copy()), true);
	}
	vars.add_func("x++", func({type->copy()}, type->copy()), true);
	vars.add_func("++x", func({type->copy()}, type->copy()), true);
	vars.add_func("x--", func({type->copy()}, type->copy()), true);
	vars.add_func("--x", func({type->copy()}, type->copy()), true);
	vars.add_func("u+", func({type->copy()}, type->copy()), true);
	vars.add_func("u-", func({type->copy()}, type->copy()), true);
	vars.add_func("!", func({type->copy()}, i1type->copy()), true);
	vars.add_func("~", func({type->copy()}, type->copy()), true);
}
} // namespace parser
} // namespace sc