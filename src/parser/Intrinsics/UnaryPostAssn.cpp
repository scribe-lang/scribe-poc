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

#define HAS_VALID_VAL(type) (type->val && type->val->has_data())
#define VERIFY_VALS_UNOP()						\
	if(!HAS_VALID_VAL(args->args[0]->type)) {			\
		base->type->val = types.get(VUNKNOWN);			\
		return true;						\
	}

namespace sc
{
namespace parser
{
INTRINSIC(xinc_i8)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xinc_i16)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xinc_i32)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xinc_i64)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xinc_u8)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xinc_u16)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xinc_u32)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xinc_u64)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res++));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_i8)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_i16)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_i32)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_i64)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_u8)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_u16)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_u32)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
INTRINSIC(xdec_u64)
{
	VERIFY_VALS_UNOP();
	int64_t res = args->args[0]->type->val->i;
	args->args[0]->type->val = types.get((int64_t)(res--));
	base->type->val = types.get((int64_t)(res));
	return true;
}
} // namespace parser
} // namespace sc
