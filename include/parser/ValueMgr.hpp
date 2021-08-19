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

#ifndef PARSER_VALUEMGR_HPP
#define PARSER_VALUEMGR_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "Value.hpp"

namespace sc
{
namespace parser
{
class RAIIParser;
// typedef bool (*intrinsic_fn_t)(TypeMgr &types, Stmt *stmt);
// #define INTRINSIC(name) bool intrinsic_##name(TypeMgr &types, Stmt *stmt)

// no need to copy unnecessarily - values are immutable

class ValueLayer
{
	std::unordered_map<std::string, Value *> vals;

public:
	inline bool add(const std::string &name, Value *val)
	{
		if(vals.find(name) != vals.end()) return false;
		vals[name] = val;
		return true;
	}
	inline Value *get(const std::string &name)
	{
		return vals[name];
	}

	inline bool has(const std::string &name)
	{
		return vals.find(name) != vals.end();
	}
};

class ValueSrc
{
	std::vector<ValueLayer> stack;

public:
	inline void pushLayer()
	{
		stack.push_back({});
	}
	inline void popLayer()
	{
		stack.pop_back();
	}

	inline bool add(const std::string &name, Value *val)
	{
		return stack.back().add(name, val);
	}
	inline Value *get(const std::string &name)
	{
		return stack.back().get(name);
	}

	inline bool has(const std::string &name)
	{
		return stack.back().has(name);
	}
};

class ValueMgr
{
	RAIIParser *parser;

	std::unordered_map<std::string, Value *> globals;

	std::unordered_map<size_t, ValueSrc> srcs;
	std::vector<ValueSrc *> stack;
	ValueAllocator vallocator;

public:
	ValueMgr(RAIIParser *parser);

	inline RAIIParser *getParser()
	{
		return parser;
	}

	inline void add_src(const size_t &src_id)
	{
		if(srcs.find(src_id) == srcs.end()) srcs[src_id] = {};
	}
	inline void push_src(const size_t &src_id)
	{
		stack.push_back(&srcs[src_id]);
	}
	inline void pop_src()
	{
		stack.pop_back();
	}

	inline void pushLayer()
	{
		stack.back()->pushLayer();
	}
	inline void popLayer()
	{
		stack.back()->popLayer();
	}

	// FIXME: enable global
	inline bool add_val(const std::string &name, Value *val, const bool &global)
	{
		return stack.back()->add(name, val);
	}
	inline Value *get_val(const std::string &name)
	{
		return stack.back()->get(name);
	}

	// FIXME: enable top_only and with_globals
	inline bool has(const std::string &name, const bool &top_only, const bool &with_globals)
	{
		return stack.back()->has(name);
	}

	inline Value *get(const int64_t &idata)
	{
		return vallocator.get(idata);
	}
	inline Value *get(const double &fdata)
	{
		return vallocator.get(fdata);
	}
	inline Value *get(const std::string &sdata)
	{
		return vallocator.get(sdata);
	}
	inline Value *get(const std::vector<Value *> &vdata)
	{
		return vallocator.get(vdata);
	}
	inline Value *get(const std::unordered_map<std::string, Value *> &stdata,
			  const std::vector<std::string> &storder)
	{
		return vallocator.get(stdata, storder);
	}
	// this is for unknown and void values
	inline Value *get(const Values &type)
	{
		return vallocator.get(type);
	}
	inline Value *get(Value *from)
	{
		return vallocator.get(from);
	}

	inline std::string getStringFromVec(Value *vec)
	{
		return parser::getStringFromVec(vec);
	}

	inline void updateValue(Value *src, Value *newval)
	{
		return vallocator.updateValue(src, newval);
	}
};
} // namespace parser
} // namespace sc

#endif // PARSER_VALUEMGR_HPP