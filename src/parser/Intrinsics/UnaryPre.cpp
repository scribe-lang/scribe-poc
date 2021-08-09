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
INTRINSIC(uadd_i8)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_i16)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_i32)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_i64)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_u8)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_u16)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_u32)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_u64)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->i)));
	return true;
}
INTRINSIC(uadd_f32)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->f)));
	return true;
}
INTRINSIC(uadd_f64)
{
	base->updateValue(values, values.get((int64_t)(+args[0]->value->f)));
	return true;
}
INTRINSIC(usub_i8)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_i16)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_i32)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_i64)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_u8)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_u16)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_u32)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_u64)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->i)));
	return true;
}
INTRINSIC(usub_f32)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->f)));
	return true;
}
INTRINSIC(usub_f64)
{
	base->updateValue(values, values.get((int64_t)(-args[0]->value->f)));
	return true;
}
INTRINSIC(not_i1)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_i8)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_i16)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_i32)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_i64)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_u8)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_u16)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_u32)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_u64)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->i)));
	return true;
}
INTRINSIC(not_f32)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->f)));
	return true;
}
INTRINSIC(not_f64)
{
	base->updateValue(values, values.get((int64_t)(!args[0]->value->f)));
	return true;
}
INTRINSIC(bnot_i8)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
INTRINSIC(bnot_i16)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
INTRINSIC(bnot_i32)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
INTRINSIC(bnot_i64)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
INTRINSIC(bnot_u8)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
INTRINSIC(bnot_u16)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
INTRINSIC(bnot_u32)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
INTRINSIC(bnot_u64)
{
	base->updateValue(values, values.get((int64_t)(~args[0]->value->i)));
	return true;
}
} // namespace parser
} // namespace sc
