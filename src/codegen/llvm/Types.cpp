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

#include "codegen/llvm/Types.hpp"

#include "Error.hpp"
#include "llvm/IR/DerivedTypes.h"
#include "parser/Type.hpp"

namespace sc
{
namespace codegen
{
static llvm::Type *ApplyTypeInfo(llvm::LLVMContext &c, parser::Stmt *&stmt, parser::Type *type,
				 llvm::Type *t)
{
	if(!type || !t) return nullptr;
	size_t ptrcount = type->ptr;
	if(type->info & parser::REF) ++ptrcount;
	for(size_t i = 0; i < ptrcount; ++i) {
		t = llvm::PointerType::get(t, 0);
	}
	return t;
}
static llvm::Type *GetPrimitiveType(llvm::LLVMContext &c, parser::Stmt *stmt,
				    parser::TypeSimple *type)
{
	size_t ptrcount = type->ptr;

	if(type->info & parser::REF) ++ptrcount;

	llvm::Type *t = nullptr;

	if(type->name == "void") {
		t = llvm::Type::getVoidTy(c);
	} else if(type->name == "i1" || type->name == "u1") {
		t = llvm::Type::getInt1Ty(c);
	} else if(type->name == "i8" || type->name == "u8") {
		t = llvm::Type::getInt8Ty(c);
	} else if(type->name == "i16" || type->name == "u16") {
		t = llvm::Type::getInt16Ty(c);
	} else if(type->name == "i32" || type->name == "u32") {
		t = llvm::Type::getInt32Ty(c);
	} else if(type->name == "i64" || type->name == "u64") {
		t = llvm::Type::getInt64Ty(c);
	} else if(type->name == "f32") {
		t = llvm::Type::getFloatTy(c);
	} else if(type->name == "f64") {
		t = llvm::Type::getDoubleTy(c);
	} else if(type->name == "nil" || type->name == "bool") {
		t = llvm::Type::getInt1Ty(c);
	}
	if(!t) {
		err::set(stmt->line, stmt->col, "failed to get LLVM type for scribe type '%s'",
			 type->str().c_str());
		return nullptr;
	}
	return t;
}

llvm::Type *GetLLType(llvm::LLVMContext &c, parser::Stmt *stmt, parser::Type *type)
{
	switch(type->type) {
	case parser::TSIMPLE: {
		parser::TypeSimple *ts = parser::as<parser::TypeSimple>(type);
		llvm::Type *t	       = GetPrimitiveType(c, stmt, ts);
		if(!t) return nullptr;
		return ApplyTypeInfo(c, stmt, type, t);
	}
	case parser::TSTRUCT: {
		parser::TypeStruct *tst = parser::as<parser::TypeStruct>(type);
		std::vector<llvm::Type *> structtypes;
		for(auto &f : tst->field_order) {
			llvm::Type *t = GetLLType(c, stmt, tst->fields[f]);
			if(!t) {
				err::set(stmt->line, stmt->col,
					 "failed to get LLVM type for scribe"
					 " struct field '%s' of type '%s'",
					 f.c_str(), tst->fields[f]->str().c_str());
				return nullptr;
			}
			structtypes.push_back(t);
		}
		llvm::StructType *t = llvm::StructType::get(c, structtypes);
		return ApplyTypeInfo(c, stmt, type, t);
	}
	case parser::TENUM: {
		err::set(stmt->line, stmt->col, "enum LLVM type is not implemented yet");
		return nullptr;
	}
	case parser::TFUNC: {
		parser::TypeFunc *tf = parser::as<parser::TypeFunc>(type);
		std::vector<llvm::Type *> args;
		for(auto &a : tf->args) {
			llvm::Type *t = GetLLType(c, stmt, a);
			if(!t) {
				err::set(stmt->line, stmt->col,
					 "failed to get LLVM type for scribe"
					 " func arg of type '%s'",
					 a->str().c_str());
				return nullptr;
			}
			args.push_back(t);
		}
		llvm::Type *rettype = GetLLType(c, stmt, tf->rettype);
		if(!rettype) {
			err::set(stmt->line, stmt->col,
				 "failed to get LLVM type for scribe func return-type of type '%s'",
				 tf->rettype->str().c_str());
			return nullptr;
		}
		llvm::FunctionType *t = llvm::FunctionType::get(rettype, args, false);
		return ApplyTypeInfo(c, stmt, type, t);
	}
	default: break;
	}
	err::set(stmt->line, stmt->col, "invalid scribe type encountered '%s'",
		 type->str().c_str());
	return nullptr;
}
} // namespace codegen
} // namespace sc