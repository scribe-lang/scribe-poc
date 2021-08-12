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

#ifndef CODEGEN_LLVM_DRIVER_HPP
#define CODEGEN_LLVM_DRIVER_HPP

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include "codegen/Base.hpp"

namespace sc
{
namespace codegen
{
class LLVMDriver : public Driver
{
	llvm::LLVMContext c;
	std::unordered_map<std::string, llvm::Module *> mods;

	llvm::Module *getLLModule(const std::string &path);

public:
	LLVMDriver(parser::RAIIParser &parser);
	~LLVMDriver();

	bool genIR();
	void dumpIR(const bool &force);
	bool genObjFile(const std::string &dest);

	llvm::Value *visit(parser::Stmt *stmt, llvm::Module *m, llvm::IRBuilder<> &b);

	llvm::Value *visit(parser::StmtBlock *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtType *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtSimple *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtFnCallInfo *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtExpr *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtVar *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtFnSig *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtFnDef *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtHeader *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtLib *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtExtern *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtEnum *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtStruct *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtVarDecl *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtCond *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtForIn *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtFor *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtWhile *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtRet *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtContinue *stmt, llvm::Module *m, llvm::IRBuilder<> &b);
	llvm::Value *visit(parser::StmtBreak *stmt, llvm::Module *m, llvm::IRBuilder<> &b);

	llvm::Value *AddVar(llvm::Module *m, llvm::IRBuilder<> &b, parser::Stmt *stmt,
			    const std::string &varname, llvm::Type *type, llvm::Value *value);
	llvm::Value *GetVar(llvm::Module *m, llvm::IRBuilder<> &b, parser::StmtSimple *stmt,
			    const std::string &varname);

	llvm::BasicBlock *GetOrCreateBasicBlock(llvm::Function *f, const std::string &name,
						llvm::BasicBlock *before);
	llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *f, const std::string &varname,
						 llvm::Type *type);
	llvm::Value *CreateInitAssignAfterAlloca(llvm::Function *f, llvm::AllocaInst *alloca,
						 llvm::Value *value);
	llvm::AllocaInst *GetEntryBlockAlloca(llvm::Function *f, const std::string &varname);
};
} // namespace codegen
} // namespace sc

#endif // CODEGEN_LLVM_DRIVER_HPP