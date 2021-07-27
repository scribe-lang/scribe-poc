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

#define HAS_VALID_VAL(vtyp) (vtyp->val && vtyp->val->has_data())
#define VERIFY_VALS_BINOP()                                                     		\
	if(!HAS_VALID_VAL(args->args[0]->vtyp) || !HAS_VALID_VAL(args->args[1]->vtyp)) {	\
		base->vtyp->val = types.get(VUNKNOWN);						\
		return true;									\
	}

namespace sc
{
namespace parser
{
INTRINSIC(assn_i8_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i8_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i16_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i32_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_i64_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u8_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u16_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u32_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((int64_t)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_u64_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f32_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_i8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_i16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_i32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_i64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_u8)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_u16)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_u32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_u64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->i);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_f32)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(assn_f64_f64)
{
	VERIFY_VALS_BINOP();
	args->args[0]->vtyp->val = types.get((double)args->args[1]->vtyp->val->f);
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_i64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_u64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(addassn_f64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res += args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_i64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_u64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(subassn_f64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res -= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_i64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_u64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(mulassn_f64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res *= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_i64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u8_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u16_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_u64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f32_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_i8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_i16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_i32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_i64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_u8)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_u16)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_u32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_u64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_f32)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(divassn_f64_f64)
{
	VERIFY_VALS_BINOP();
	double res = args->args[0]->vtyp->val->f;
	args->args[0]->vtyp->val = types.get((double)(res /= args->args[1]->vtyp->val->f));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(modassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res %= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bandassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res &= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(borassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res |= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(bxorassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res ^= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(lshiftassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res <<= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_i64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u8_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u16_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u32_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_i8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_i16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_i32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_i64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_u8)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_u16)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_u32)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
INTRINSIC(rshiftassn_u64_u64)
{
	VERIFY_VALS_BINOP();
	int64_t res = args->args[0]->vtyp->val->i;
	args->args[0]->vtyp->val = types.get((int64_t)(res >>= args->args[1]->vtyp->val->i));
	base->vtyp->val = args->args[0]->vtyp->val;
	return true;
}
} // namespace parser
} // namespace sc