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
	return new type_func_t(nullptr, 0, 0, {}, args, rettype);
}
void add_primitive_integer_funcs(const std::string &typname, VarMgr &vars)
{
	std::vector<std::string> alltypes = {"i1",  "i8",  "i16", "i32", "i64", "u8",
					     "u16", "u32", "u64", "f32", "f64"};

	type_simple_t *type = static_cast<type_simple_t *>(vars.get(typname));
	for(auto &t : alltypes) {
		type_simple_t *type2		= static_cast<type_simple_t *>(vars.get(t));
		const std::vector<int64_t> tids = {type->id, type2->id};

		vars.add_type_func(tids, "=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "+", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "-", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "*", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "/", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "%", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "+=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "-=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "*=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "/=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "%=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "&&", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "||", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "==", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "<", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, ">", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "<=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, ">=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "!=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "&", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "|", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "^", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "&=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "|=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "~=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "^=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "<<", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, ">>", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, "<<=", func({type->copy(), type2->copy()}, type->copy()));
		vars.add_type_func(tids, ">>=", func({type->copy(), type2->copy()}, type->copy()));
	}
	vars.add_type_func({type->id}, "x++", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "++x", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "x--", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "--x", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "u+", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "u-", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "u&", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "u*", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "!", func({type->copy()}, type->copy()));
	vars.add_type_func({type->id}, "~", func({type->copy()}, type->copy()));
}
} // namespace parser
} // namespace sc