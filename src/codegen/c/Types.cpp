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

#include "codegen/c/Types.hpp"

#include "Error.hpp"
#include "parser/Type.hpp"

namespace sc
{
namespace codegen
{
std::string ApplyTypeInfo(parser::Stmt *stmt, parser::Type *type, const std::string &t)
{
	if(!type || t.empty()) return "";
	size_t ptrcount = type->ptr;
	std::string pre;
	std::string typestr;
	if(type->info & parser::STATIC) pre += "static ";
	if(type->info & parser::CONST) pre = "const ";
	if(type->info & parser::VOLATILE) pre += "volatile ";
	typestr = pre + t;
	if(type->info & parser::REF) ++ptrcount;
	for(size_t i = 0; i < ptrcount; ++i) {
		typestr += '*';
	}
	return typestr;
}

std::string GetCType(parser::Stmt *stmt, parser::Type *type)
{
	switch(type->type) {
	case parser::TSIMPLE: {
		parser::TypeSimple *ts = parser::as<parser::TypeSimple>(type);
		return ApplyTypeInfo(stmt, ts, ts->name);
	}
	case parser::TSTRUCT: {
		parser::TypeStruct *tst = parser::as<parser::TypeStruct>(type);
		std::string res		= "{";
		for(auto &f : tst->field_order) {
			res += GetCType(stmt, tst->fields[f]) + " " + f + ";";
		}
		res += "}";
		return ApplyTypeInfo(stmt, type, res);
	}
	case parser::TENUM: {
		err::set(stmt, "enum LLVM type is not implemented yet");
		return nullptr;
	}
	case parser::TFUNC: {
		// parser::TypeFunc *tf = parser::as<parser::TypeFunc>(type);
		// std::vector<llvm::Type *> args;
		// for(auto &a : tf->args) {
		// 	llvm::Type *t = GetLLType(c, stmt, a);
		// 	if(!t) {
		// 		err::set(stmt,
		// 			 "failed to get LLVM type for scribe"
		// 			 " func arg of type '%s'",
		// 			 a->str().c_str());
		// 		return nullptr;
		// 	}
		// 	args.push_back(t);
		// }
		// llvm::Type *rettype = GetLLType(c, stmt, tf->rettype);
		// if(!rettype) {
		// 	err::set(stmt,
		// 		 "failed to get LLVM type for scribe func return-type of type '%s'",
		// 		 tf->rettype->str().c_str());
		// 	return nullptr;
		// }
		// llvm::FunctionType *t = llvm::FunctionType::get(rettype, args, false);
		// return ApplyTypeInfo(c, stmt, type, t);
	}
	default: break;
	}
	err::set(stmt, "invalid scribe type encountered '%s'", type->str().c_str());
	return "";
}

std::string GetCTypeName(parser::Stmt *stmt, parser::Type *type)
{
	std::string res;
	if(type->type == parser::TSTRUCT) {
		res = "struct_" + std::to_string(type->id);
		res = ApplyTypeInfo(stmt, type, res);
	} else if(type->type == parser::TFUNC) {
		res = "func_" + std::to_string(type->id);
		res = ApplyTypeInfo(stmt, type, res);
	} else if(type->type == parser::TENUM) {
		res = "enum_" + std::to_string(type->id);
		res = ApplyTypeInfo(stmt, type, res);
	} else {
		res = GetCType(stmt, type);
	}
	return res;
}
} // namespace codegen
} // namespace sc