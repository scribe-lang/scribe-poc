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

#include <cassert>

#include "Error.hpp"

namespace sc
{
namespace codegen
{
static bool TypeIsLiteralStr(parser::Type *ty)
{
	if(ty->type != parser::TSIMPLE) return false;
	if(ty->ptr != 1) return false;
	if(parser::as<parser::TypeSimple>(ty)->name != "i8") return false;
	return true;
}
static bool TypeIsLiteralChar(parser::Type *ty)
{
	if(ty->type != parser::TSIMPLE) return false;
	if(ty->ptr != 0) return false;
	if(parser::as<parser::TypeSimple>(ty)->name != "i8") return false;
	return true;
}
std::string GetCValue(parser::Stmt *stmt, parser::Value *value, parser::Type *type)
{
	switch(value->type) {
	case parser::VUNKNOWN: // fallthrough
	case parser::VVOID: return "";
	case parser::VINT: {
		if(TypeIsLiteralChar(type)) {
			return "'" + std::string(1, value->i) + "'";
		}
		return std::to_string(value->i);
	}
	case parser::VFLT: return std::to_string(value->f);
	case parser::VVEC: {
		if(TypeIsLiteralStr(type)) {
			return "\"" + parser::getStringFromVec(value) + "\"";
		}
		std::string res;
		res		    = "{";
		parser::Type *etype = type->copy();
		--etype->ptr;
		for(auto &e : value->v) {
			res += GetCValue(stmt, e, etype) + ", ";
		}
		delete etype;
		if(value->v.size() > 0) {
			res.pop_back();
			res.pop_back();
		}
		res += "}";
		return res;
	}
	case parser::VSTRUCT: {
		std::string res;
		parser::TypeStruct *st = parser::as<parser::TypeStruct>(type);

		res = "{";
		for(auto &f : value->storder) {
			res += GetCValue(stmt, value->st[f], st->get_field(f)) + ", ";
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
	err::set(stmt, "invalid scribe value encountered '%s'", value->stringify().c_str());
	return nullptr;
}
} // namespace codegen
} // namespace sc