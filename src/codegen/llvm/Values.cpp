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

#include "codegen/llvm/Values.hpp"

#include <llvm/IR/Constants.h>

#include "Error.hpp"

namespace sc
{
namespace codegen
{
llvm::Type *GetLLType(llvm::LLVMContext &c, parser::Value *value)
{
	switch(value->type) {
	case parser::VUNKNOWN: return nullptr;
	case parser::VVOID: return llvm::Type::getVoidTy(c);
	case parser::VINT: return llvm::Type::getInt32Ty(c);
	case parser::VFLT: return llvm::Type::getFloatTy(c);
	case parser::VSTR: return llvm::Type::getInt8PtrTy(c);
	case parser::VVEC: {
		if(value->v.empty()) return nullptr;
		return llvm::ArrayType::get(GetLLType(c, value->v[0]), value->v.size());
	}
	case parser::VSTRUCT: {
		std::vector<llvm::Type *> structtypes;
		for(auto &f : value->storder) {
			llvm::Type *t = GetLLType(c, value->st[f]);
			if(!t) return nullptr;
			structtypes.push_back(t);
		}
		return llvm::StructType::get(c, structtypes);
	}
	}
	return nullptr;
}
llvm::Value *GetLLValue(llvm::LLVMContext &c, parser::Stmt *stmt, parser::Value *&value)
{
	switch(value->type) {
	case parser::VUNKNOWN: // fallthrough
	case parser::VVOID: return nullptr;
	case parser::VINT: return llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), value->i);
	case parser::VFLT: return llvm::ConstantFP::get(llvm::Type::getFloatTy(c), value->f);
	case parser::VSTR: return llvm::ConstantDataArray::getString(c, value->s);
	case parser::VVEC: {
		llvm::ArrayType *vt = static_cast<llvm::ArrayType *>(GetLLType(c, value));
		std::vector<llvm::Constant *> vals;
		for(auto &e : value->v) {
			llvm::Value *v = GetLLValue(c, stmt, e);
			if(!v) return nullptr;
			vals.push_back(static_cast<llvm::Constant *>(v));
		}
		return llvm::ConstantArray::get(vt, vals);
	}
	case parser::VSTRUCT: {
		llvm::StructType *stt = static_cast<llvm::StructType *>(GetLLType(c, value));
		std::vector<llvm::Constant *> vals;
		for(auto &f : value->storder) {
			llvm::Value *v = GetLLValue(c, stmt, value->st[f]);
			if(!v) return nullptr;
			vals.push_back(static_cast<llvm::Constant *>(v));
		}
		return llvm::ConstantStruct::get(stt, vals);
	}
	default: break;
	}
	err::set(stmt->line, stmt->col, "invalid scribe value encountered '%s'",
		 value->stringify().c_str());
	return nullptr;
}
} // namespace codegen
} // namespace sc