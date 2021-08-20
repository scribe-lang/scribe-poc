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
INTRINSIC(assn_i8_i8)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_i16_i16)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_i32_i32)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_i64_i64)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_u8_u8)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_u16_u16)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_u32_u32)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_u64_u64)
{
	args[0]->updateValue(values, values.get((int64_t)args[1]->value->i));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_f32_f32)
{
	args[0]->updateValue(values, values.get((double)args[1]->value->f));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(assn_f64_f64)
{
	args[0]->updateValue(values, values.get((double)args[1]->value->f));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res += args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_f32_f32)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res += args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(addassn_f64_f64)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res += args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res -= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_f32_f32)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res -= args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(subassn_f64_f64)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res -= args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res *= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_f32_f32)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res *= args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(mulassn_f64_f64)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res *= args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res /= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_f32_f32)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res /= args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(divassn_f64_f64)
{
	double res = args[0]->value->f;
	args[0]->updateValue(values, values.get((double)(res /= args[1]->value->f)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(modassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res %= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bandassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res &= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(borassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res |= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(bxorassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res ^= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(lshiftassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res <<= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_i8_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_i16_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_i32_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_i64_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_u8_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_u16_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_u32_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(rshiftassn_u64_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res >>= args[1]->value->i)));
	base->updateValue(values, args[0]->value);
	return true;
}
} // namespace parser
} // namespace sc
