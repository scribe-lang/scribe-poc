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

#include "parser/TypeMgr.hpp"

namespace sc
{
namespace parser
{
INTRINSIC(xinc_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xinc_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xinc_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xinc_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xinc_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xinc_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xinc_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xinc_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res++)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
INTRINSIC(xdec_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(res--)));
	base->updateValue(values, values.get((int64_t)(res)));
	return true;
}
} // namespace parser
} // namespace sc
