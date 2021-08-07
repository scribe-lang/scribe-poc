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
Value::Value(const Values &type) : type(type), i(0), f(0) {}
Value::Value(const int64_t &idata) : type(VINT), i(idata), f(0) {}
Value::Value(const double &fdata) : type(VFLT), i(0), f(fdata) {}
Value::Value(const std::string &sdata) : type(VSTR), i(0), f(0), s(sdata) {}
Value::Value(const std::unordered_map<std::string, Value *> &stdata)
	: type(VSTRUCT), i(0), f(0), st(stdata)
{}
bool Value::operator==(const Value &other)
{
	if(type != other.type) return false;
	switch(type) {
	case VUNKNOWN: return other.type == VUNKNOWN;
	case VVOID: return other.type == VVOID;
	case VINT: return i == other.i;
	case VFLT: return f == other.f;
	case VSTR: return s == other.s;
	case VSTRUCT:
		if(st.size() != other.st.size()) return false;
		for(auto &s : st) {
			auto res = other.st.find(s.first);
			if(res == other.st.end()) return false;
			if((*s.second) != (*res->second)) return false;
		}
		return true;
	}
	return false;
}
bool Value::operator!=(const Value &other)
{
	return !(*this == other);
}
std::string Value::stringify()
{
	switch(type) {
	case VUNKNOWN: return "<unknown>";
	case VVOID: return "<void>";
	case VINT: return std::to_string(i);
	case VFLT: return std::to_string(f);
	case VSTR: return s;
	case VSTRUCT:
		std::string res;
		res = "{";
		for(auto &f : st) {
			res += f.first + "." + f.second->stringify() + "_";
		}
		if(st.size() > 0) res.pop_back();
		res += "}";
		return res;
	}
	return "";
}
bool Value::has_data()
{
	switch(type) {
	case VUNKNOWN: return false;
	case VVOID: // fallthrough
	case VINT:  // fallthrough
	case VFLT:  // fallthrough
	case VSTR:  // fallthrough
	case VSTRUCT: return true;
	}
	return false;
}

ValueAllocator::ValueAllocator() : unknown(new Value(VUNKNOWN)), vvoid(new Value(VVOID)) {}
ValueAllocator::~ValueAllocator()
{
	delete vvoid;
	delete unknown;
	for(auto &v : allvalues) delete v;
}
std::string ValueAllocator::stringify(const std::unordered_map<std::string, Value *> &v)
{
	if(v.empty()) return "";
	std::string res;
	for(auto &e : v) res += e.first + "." + e.second->stringify() + "_";
	res.pop_back();
	return res;
}
Value *ValueAllocator::get(const Values &type)
{
	switch(type) {
	case VUNKNOWN: return unknown;
	case VVOID: return vvoid;
	default: break;
	}
	return nullptr;
}
Value *ValueAllocator::get(const int64_t &idata)
{
	static std::unordered_map<int64_t, Value *> imap;
	auto res = imap.find(idata);
	if(res != imap.end()) return res->second;
	Value *v    = new Value(idata);
	imap[idata] = v;
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(const double &fdata)
{
	static std::unordered_map<double, Value *> fmap;
	auto res = fmap.find(fdata);
	if(res != fmap.end()) return res->second;
	Value *v    = new Value(fdata);
	fmap[fdata] = v;
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(const std::string &sdata)
{
	static std::unordered_map<std::string, Value *> smap;
	auto res = smap.find(sdata);
	if(res != smap.end()) return res->second;
	Value *v    = new Value(sdata);
	smap[sdata] = v;
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(const std::unordered_map<std::string, Value *> &stdata)
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