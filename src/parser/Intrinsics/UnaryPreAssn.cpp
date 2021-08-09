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
INTRINSIC(incx_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(incx_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(incx_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(incx_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(incx_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(incx_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(incx_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(incx_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(++res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_i8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_i16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_i32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_i64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_u8)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_u16)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_u32)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
INTRINSIC(decx_u64)
{
	int64_t res = args[0]->value->i;
	args[0]->updateValue(values, values.get((int64_t)(--res)));
	base->updateValue(values, args[0]->value);
	return true;
}
} // namespace parser
} // namespace sc
