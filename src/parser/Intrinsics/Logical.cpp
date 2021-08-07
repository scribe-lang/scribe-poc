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

#include "Error.hpp"
#include "FS.hpp"
#include "Parser.hpp"
#include "parser/TypeMgr.hpp"

#define HAS_VALID_VAL(type) (type->val && type->val->has_data())
#define VERIFY_VALS_BINOP()                                                     		\
	if(!HAS_VALID_VAL(args->args[0]->type) || !HAS_VALID_VAL(args->args[1]->type)) {	\
		base->type->val = types.get(VUNKNOWN);						\
		return true;									\
	}

namespace sc
{
namespace parser
{
INTRINSIC(logand_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logand_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logand_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f && args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->i));
	return true;
}
INTRINSIC(logor_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(logor_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f || args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->i));
	return true;
}
INTRINSIC(eq_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(eq_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f == args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->i));
	return true;
}
INTRINSIC(lt_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(lt_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f < args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->i));
	return true;
}
INTRINSIC(gt_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(gt_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f > args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(le_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(le_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f <= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ge_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ge_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f >= args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i1_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i1_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i1_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_i64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_i64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u8_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u8_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u8_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u16_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u16_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u16_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_u64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_u64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->i != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_f32_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f32_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_f32_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_f64_i1)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_i8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_i16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_i32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_i64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_u8)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_u16)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_u32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_u64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->i));
	return true;
}
INTRINSIC(ne_f64_f32)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->f));
	return true;
}
INTRINSIC(ne_f64_f64)
{
	VERIFY_VALS_BINOP();
	base->type->val = types.get((int64_t)(args->args[0]->type->val->f != args->args[1]->type->val->f));
	return true;
}
} // namespace parser
} // namespace sc
