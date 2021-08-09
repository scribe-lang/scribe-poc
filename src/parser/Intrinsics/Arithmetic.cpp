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

namespace sc
{
namespace parser
{
INTRINSIC(add_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_i8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_i16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_i32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_i64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_i64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i + args[1]->value->i)));
	return true;
}
INTRINSIC(add_u64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_u64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i + args[1]->value->f)));
	return true;
}
INTRINSIC(add_f32_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->f)));
	return true;
}
INTRINSIC(add_f32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->f)));
	return true;
}
INTRINSIC(add_f64_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->i)));
	return true;
}
INTRINSIC(add_f64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->f)));
	return true;
}
INTRINSIC(add_f64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f + args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_i64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_i64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_u64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_u64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_f32_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_f32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_f64_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->i)));
	return true;
}
INTRINSIC(sub_f64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->f)));
	return true;
}
INTRINSIC(sub_f64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f - args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_i64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_i64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_u64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_u64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_f32_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_f32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_f64_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->i)));
	return true;
}
INTRINSIC(mul_f64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->f)));
	return true;
}
INTRINSIC(mul_f64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f * args[1]->value->f)));
	return true;
}
INTRINSIC(div_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_i8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_i16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_i32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_i64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_i64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u8_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u8_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u16_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u16_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i / args[1]->value->i)));
	return true;
}
INTRINSIC(div_u64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_u64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->i / args[1]->value->f)));
	return true;
}
INTRINSIC(div_f32_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f32_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->f)));
	return true;
}
INTRINSIC(div_f32_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->f)));
	return true;
}
INTRINSIC(div_f64_i8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_i16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_i32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_i64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_u8)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_u16)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_u32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_u64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->i)));
	return true;
}
INTRINSIC(div_f64_f32)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->f)));
	return true;
}
INTRINSIC(div_f64_f64)
{
	base->updateValue(values, values.get((double)(args[0]->value->f / args[1]->value->f)));
	return true;
}
INTRINSIC(mod_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(mod_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i % args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(band_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i & args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bor_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i | args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(bxor_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i ^ args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(lshift_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i << args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_i64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u8_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u16_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u32_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_i8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_i16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_i32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_i64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_u8)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_u16)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_u32)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
INTRINSIC(rshift_u64_u64)
{
	base->updateValue(values, values.get((int64_t)(args[0]->value->i >> args[1]->value->i)));
	return true;
}
} // namespace parser
} // namespace sc
