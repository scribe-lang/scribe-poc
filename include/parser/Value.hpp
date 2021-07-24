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

#ifndef PARSER_VALUE_HPP
#define PARSER_VALUE_HPP

#include <string>
#include <vector>

namespace sc
{
namespace parser
{
enum Values
{
	VINT, // also char (u8)
	VFLT,
	VSTR,
	VSTRUCT,
};

// typedef bool (*intrinsic_fn_t)(TypeMgr &types, stmt_base_t *stmt);
// #define INTRINSIC(name) bool intrinsic_##name(TypeMgr &types, stmt_base_t *stmt)

struct Value
{
	Values type;
	int64_t i;
	double f;
	std::string s;
	std::vector<Value *> st; // each element contains a field of struct

	Value(const int64_t &idata);
	Value(const double &fdata);
	Value(const std::string &sdata);
	Value(const std::vector<Value *> &stdata);

	bool operator==(const Value &other);
	bool operator!=(const Value &other);
};

// no need to copy unnecessarily - values are immutable
class ValueMgr
{
	std::vector<Value *> allvalues;

	std::string stringify(const std::vector<Value *> &v);
	std::string stringify(const Value *v);

public:
	~ValueMgr();

	Value *get(const int64_t &idata);
	Value *get(const double &fdata);
	Value *get(const std::string &sdata);
	Value *get(const std::vector<Value *> &stdata);
};
} // namespace parser
} // namespace sc

#endif // PARSER_VALUE_HPP