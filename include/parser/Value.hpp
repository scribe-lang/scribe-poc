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

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace sc
{
namespace parser
{
enum Values
{
	VUNKNOWN,
	VVOID,
	VINT, // also char (u8)
	VFLT,
	VSTR,
	VVEC,
	VSTRUCT,
};

struct Value
{
	uint64_t id;
	Values type;
	int64_t i;
	double f;
	std::string s;
	std::vector<Value *> v;			     // list of values (mainly for variadics)
	std::unordered_map<std::string, Value *> st; // each element contains a field of struct
	std::vector<std::string> storder;

	Value(const uint64_t &id, const Values &type);
	Value(const uint64_t &id, const int64_t &idata);
	Value(const uint64_t &id, const double &fdata);
	Value(const uint64_t &id, const std::string &sdata);
	Value(const uint64_t &id, const std::vector<Value *> &vdata);
	Value(const uint64_t &id, const std::unordered_map<std::string, Value *> &stdata,
	      const std::vector<std::string> &storder);

	bool operator==(const Value &other);
	bool operator!=(const Value &other);

	std::string stringify();

	bool has_data();
};

// no need to copy unnecessarily - values are immutable
class ValueAllocator
{
	std::vector<Value *> allvalues;
	Value *unknown;
	Value *vvoid;

	std::string stringify(const std::unordered_map<std::string, Value *> &v);

public:
	ValueAllocator();
	~ValueAllocator();

	// for unknown type
	Value *get(const Values &type);
	Value *get(const int64_t &idata);
	Value *get(const double &fdata);
	Value *get(const std::string &sdata);
	Value *get(const std::vector<Value *> &vdata);
	Value *get(const std::unordered_map<std::string, Value *> &stdata,
		   const std::vector<std::string> &storder);
	Value *get(Value *from);

	void updateValue(Value *src, Value *newval);
};
} // namespace parser
} // namespace sc

#endif // PARSER_VALUE_HPP