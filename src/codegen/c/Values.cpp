/*
	MIT License
	Copyright (c) 2021 Scribe Language Repositories
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#include "codegen/c/Values.hpp"

#include "Error.hpp"

namespace sc
{
namespace codegen
{
std::string GetCValue(parser::Stmt *stmt, parser::Value *value)
{
	switch(value->type) {
	case parser::VUNKNOWN: // fallthrough
	case parser::VVOID: return "";
	case parser::VINT: return std::to_string(value->i);
	case parser::VFLT: return std::to_string(value->f);
	case parser::VVEC: {
		std::string res;
		res = "{";
		for(auto &e : value->v) {
			res += GetCValue(stmt, e) + ", ";
		}
		if(value->v.size() > 0) {
			res.pop_back();
			res.pop_back();
		}
		res += "}";
		return res;
	}
	case parser::VSTRUCT: {
		std::string res;
		res = "{";
		for(auto &f : value->storder) {
			res += GetCValue(stmt, value->st[f]) + ", ";
		}
		if(value->st.size() > 0) {
			res.pop_back();
			res.pop_back();
		}
		res += "}";
		return res;
	}
	default: break;
	}
	err::set(stmt->line, stmt->col, "invalid scribe value encountered '%s'",
		 value->stringify().c_str());
	return nullptr;
}
} // namespace codegen
} // namespace sc