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
Value::Value(const uint64_t &id, const Values &type) : id(id), type(type), i(0), f(0) {}
Value::Value(const uint64_t &id, const int64_t &idata) : id(id), type(VINT), i(idata), f(idata) {}
Value::Value(const uint64_t &id, const double &fdata) : id(id), type(VFLT), i(fdata), f(fdata) {}
Value::Value(const uint64_t &id, const std::vector<Value *> &vdata)
	: id(id), type(VVEC), i(0), f(0), v(vdata)
{}
Value::Value(const uint64_t &id, const std::unordered_map<std::string, Value *> &stdata,
	     const std::vector<std::string> &storder)
	: type(VSTRUCT), i(0), f(0), st(stdata), storder(storder)
{}
bool Value::operator==(const Value &other)
{
	if(type != other.type) return false;
	switch(type) {
	case VUNKNOWN: return other.type == VUNKNOWN;
	case VVOID: return other.type == VVOID;
	case VINT: return i == other.i;
	case VFLT: return f == other.f;
	case VVEC:
		if(v.size() != other.v.size()) return false;
		for(size_t i = 0; i < v.size(); ++i) {
			if(*v[i] != *other.v[i]) return false;
		}
		return true;
	case VSTRUCT:
		if(st.size() != other.st.size()) return false;
		for(auto &s : storder) {
			auto res = other.st.find(s);
			if(res == other.st.end()) return false;
			if((*st[s]) != (*res->second)) return false;
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
	case VVEC: {
		std::string res;
		res = "[";
		for(auto &e : v) {
			res += e->stringify() + ", ";
		}
		if(v.size() > 0) {
			res.pop_back();
			res.pop_back();
		}
		res += "]";
		return res;
	}
	case VSTRUCT: {
		std::string res;
		res = "{";
		for(auto &f : storder) {
			res += f + " = " + st[f]->stringify() + ", ";
		}
		if(st.size() > 0) {
			res.pop_back();
			res.pop_back();
		}
		res += "}";
		return res;
	}
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
	case VVEC:
	case VSTRUCT: return true;
	}
	return false;
}

ValueAllocator::ValueAllocator() : unknown(new Value(0, VUNKNOWN)), vvoid(new Value(1, VVOID))
{
	allvalues.push_back(unknown);
	allvalues.push_back(vvoid);
}
ValueAllocator::~ValueAllocator()
{
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
	Value *v = new Value(allvalues.size(), idata);
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(const double &fdata)
{
	Value *v = new Value(allvalues.size(), fdata);
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(const std::string &sdata)
{
	std::vector<Value *> chars;
	for(auto &s : sdata) {
		chars.push_back(get((int64_t)s));
	}
	Value *v = new Value(allvalues.size(), chars);
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(const std::vector<Value *> &vdata)
{
	Value *v = new Value(allvalues.size(), vdata);
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(const std::unordered_map<std::string, Value *> &stdata,
			   const std::vector<std::string> &storder)
{
	Value *v = new Value(allvalues.size(), stdata, storder);
	allvalues.push_back(v);
	return v;
}
Value *ValueAllocator::get(Value *from)
{
	Value *v = new Value(allvalues.size(), (int64_t)0);
	allvalues.push_back(v);
	updateValue(v, from);
	return v;
}

void ValueAllocator::updateValue(Value *src, Value *newval)
{
	src->type    = newval->type;
	src->i	     = newval->i;
	src->f	     = newval->f;
	src->v	     = newval->v;
	src->st	     = newval->st;
	src->storder = newval->storder;
}

std::string getStringFromVec(Value *vec)
{
	if(vec->type != VVEC) return "";
	std::string res;
	for(auto &e : vec->v) {
		res.push_back((char)e->i);
	}
	return res;
}
} // namespace parser
} // namespace sc