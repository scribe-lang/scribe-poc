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

#include "parser/Value.hpp"

#include <unordered_map>

namespace sc
{
namespace parser
{
Value::Value(const int64_t &idata) : type(VINT), i(idata), f(0) {}
Value::Value(const double &fdata) : type(VFLT), i(0), f(fdata) {}
Value::Value(const std::string &sdata) : type(VSTR), i(0), f(0), s(sdata) {}
Value::Value(const std::vector<Value *> &stdata) : type(VSTRUCT), i(0), f(0), st(stdata) {}
bool Value::operator==(const Value &other)
{
	if(type != other.type) return false;
	switch(type) {
	case VINT: return i == other.i;
	case VFLT: return f == other.f;
	case VSTR: return s == other.s;
	case VSTRUCT:
		if(st.size() != other.st.size()) return false;
		for(size_t i = 0; i < st.size(); ++i) {
			if((*st[i]) != (*other.st[i])) return false;
		}
		return true;
	}
	return false;
}
bool Value::operator!=(const Value &other)
{
	return !(*this == other);
}

ValueMgr::~ValueMgr()
{
	for(auto &v : allvalues) delete v;
}
std::string ValueMgr::stringify(const std::vector<Value *> &v)
{
	if(v.empty()) return "";
	std::string res;
	for(auto &e : v) res += stringify(e) + "_";
	res.pop_back();
	return res;
}
std::string ValueMgr::stringify(const Value *v)
{
	switch(v->type) {
	case VINT: return std::to_string(v->i);
	case VFLT: return std::to_string(v->f);
	case VSTR: return v->s;
	case VSTRUCT:
		std::string res;
		res = "{";
		for(auto &f : v->st) {
			res += stringify(f) + "_";
		}
		if(v->st.size() > 0) res.pop_back();
		return res;
	}
	return "";
}
Value *ValueMgr::get(const int64_t &idata)
{
	static std::unordered_map<int64_t, Value *> imap;
	auto res = imap.find(idata);
	if(res != imap.end()) return res->second;
	Value *v    = new Value(idata);
	imap[idata] = v;
	allvalues.push_back(v);
	return v;
}
Value *ValueMgr::get(const double &fdata)
{
	static std::unordered_map<double, Value *> fmap;
	auto res = fmap.find(fdata);
	if(res != fmap.end()) return res->second;
	Value *v    = new Value(fdata);
	fmap[fdata] = v;
	allvalues.push_back(v);
	return v;
}
Value *ValueMgr::get(const std::string &sdata)
{
	static std::unordered_map<std::string, Value *> smap;
	auto res = smap.find(sdata);
	if(res != smap.end()) return res->second;
	Value *v    = new Value(sdata);
	smap[sdata] = v;
	allvalues.push_back(v);
	return v;
}
Value *ValueMgr::get(const std::vector<Value *> &stdata)
{
	static std::unordered_map<std::string, Value *> stmap;
	std::string name = "{" + stringify(stdata) + "}";
	auto res	 = stmap.find(name);
	if(res != stmap.end()) return res->second;
	Value *v    = new Value(stdata);
	stmap[name] = v;
	allvalues.push_back(v);
	return v;
}
} // namespace parser
} // namespace sc