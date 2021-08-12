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

#include "codegen/llvm/Driver.hpp"

#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/IRBuilder.h>

#include "codegen/llvm/Types.hpp"
#include "codegen/llvm/Values.hpp"
#include "Error.hpp"

namespace sc
{
namespace codegen
{
LLVMDriver::LLVMDriver(parser::RAIIParser &parser) : Driver(parser) {}
LLVMDriver::~LLVMDriver()
{
	for(auto &m : mods) delete m.second;
}
llvm::Module *LLVMDriver::getLLModule(const std::string &path)
{
	if(mods.find(path) == mods.end()) {
		mods[path] = new llvm::Module(path, c);
	}
	return mods[path];
}

bool LLVMDriver::genIR()
{
	const std::vector<std::string> &modulestack = parser.getModuleStack();
	for(auto it = modulestack.rbegin(); it != modulestack.rend(); ++it) {
		parser::Module *mod = parser.getModule(*it);
		err::pushModule(mod);
		parser::Stmt *&ptree = mod->getParseTree();
		llvm::Module *m	     = getLLModule(mod->getPath());
		llvm::IRBuilder<> b(c);
		if(!visit(ptree, m, b)) {
			err::set(ptree->line, ptree->col, "failed to gen IR for source: %s",
				 mod->getPath().c_str());
			err::show(stderr);
			return false;
		}
		err::popModule();
	}
	return true;
}
void LLVMDriver::dumpIR(const bool &force)
{
	if(!args.has("ir") && !force) return;
	const std::vector<std::string> &modulestack = parser.getModuleStack();
	for(auto it = modulestack.rbegin(); it != modulestack.rend(); ++it) {
		llvm::Module *mod = mods[*it];
		mod->print(llvm::errs(), nullptr);
	}
}
bool LLVMDriver::genObjFile(const std::string &dest)
{
	return true;
}

llvm::Value *LLVMDriver::visit(parser::Stmt *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	switch(stmt->stmt_type) {
	case parser::BLOCK: return visit(parser::as<parser::StmtBlock>(stmt), m, b);
	case parser::TYPE: return visit(parser::as<parser::StmtType>(stmt), m, b);
	case parser::SIMPLE: return visit(parser::as<parser::StmtSimple>(stmt), m, b);
	case parser::EXPR: return visit(parser::as<parser::StmtExpr>(stmt), m, b);
	case parser::FNCALLINFO: return visit(parser::as<parser::StmtFnCallInfo>(stmt), m, b);
	case parser::VAR: return visit(parser::as<parser::StmtVar>(stmt), m, b);
	case parser::FNSIG: return visit(parser::as<parser::StmtFnSig>(stmt), m, b);
	case parser::FNDEF: return visit(parser::as<parser::StmtFnDef>(stmt), m, b);
	case parser::HEADER: return visit(parser::as<parser::StmtHeader>(stmt), m, b);
	case parser::LIB: return visit(parser::as<parser::StmtLib>(stmt), m, b);
	case parser::EXTERN: return visit(parser::as<parser::StmtExtern>(stmt), m, b);
	case parser::ENUMDEF: return visit(parser::as<parser::StmtEnum>(stmt), m, b);
	case parser::STRUCTDEF: return visit(parser::as<parser::StmtStruct>(stmt), m, b);
	case parser::VARDECL: return visit(parser::as<parser::StmtVarDecl>(stmt), m, b);
	case parser::COND: return visit(parser::as<parser::StmtCond>(stmt), m, b);
	case parser::FORIN: return visit(parser::as<parser::StmtForIn>(stmt), m, b);
	case parser::FOR: return visit(parser::as<parser::StmtFor>(stmt), m, b);
	case parser::WHILE: return visit(parser::as<parser::StmtWhile>(stmt), m, b);
	case parser::RET: return visit(parser::as<parser::StmtRet>(stmt), m, b);
	case parser::CONTINUE: return visit(parser::as<parser::StmtContinue>(stmt), m, b);
	case parser::BREAK: return visit(parser::as<parser::StmtBreak>(stmt), m, b);
	}
	return nullptr;
}

llvm::Value *LLVMDriver::visit(parser::StmtBlock *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	for(auto &s : stmt->stmts) {
		if(!visit(s, m, b)) {
			err::set(s->line, s->col, "failed to generate IR for statement");
			return nullptr;
		}
	}
	return b.getTrue();
}
llvm::Value *LLVMDriver::visit(parser::StmtType *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	// nothing to do here
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtSimple *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	if(stmt->value) return GetLLValue(c, stmt, stmt->value);
	llvm::Type *t = GetLLType(c, stmt, stmt->type);
	switch(stmt->val.tok.val) {
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL:	 // fallthrough
	case lex::INT: return llvm::ConstantInt::get(t, stmt->val.data.i);
	case lex::FLT: return llvm::ConstantFP::get(t, stmt->val.data.f);
	case lex::CHAR: return llvm::ConstantDataArray::getString(c, stmt->val.data.s);
	default: break;
	}
	// the following part is only valid for existing variables.
	// the part for variable declaration exists in Var visit
	std::string varname = stmt->val.data.s + '.' + std::to_string(stmt->type->id);
	if(stmt->type->type == parser::TFUNC) {
		llvm::Function *f = m->getFunction(varname);
		if(!f) {
			err::set(stmt->val, "function does not exist in IR");
			return nullptr;
		}
		return f;
	}
	llvm::Value *v = GetVar(m, b, stmt, varname);
	if(!v) {
		err::set(stmt->val, "variable does not exist in IR");
		return nullptr;
	}
	return v;
}
llvm::Value *LLVMDriver::visit(parser::StmtFnCallInfo *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	// std::vector<llvm::Value *> vals;
	// for(auto &a : stmt->args) {
	// 	vals.push_back(visit(a, m, b));
	// 	if(!vals.back()) {
	// 		err::set(a->line, a->col,
	// 			 "failed to generate IR for function call argument");
	// 		return nullptr;
	// 	}
	// }
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtExpr *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	if(stmt->value) return GetLLValue(c, stmt, stmt->value);

	// const lex::TokType &oper = stmt->oper.tok.val;
	// llvm::Value *l		 = visit(stmt->lhs, m, b);
	// if(!l) {
	// 	err::set(stmt->lhs->line, stmt->lhs->col, "failed to get IR for LHS");
	// 	return nullptr;
	// }
	// llvm::Value *r = nullptr;
	// if(stmt->rhs && oper != lex::DOT && oper != lex::FNCALL) r = visit(stmt->rhs, m, b);

	// switch(oper) {
	// case lex::DOT: {
	// 	if(!l->getType()->isStructTy()) {
	// 		err::set(stmt->line, stmt->col, "expected LHS load to give a struct type");
	// 		return nullptr;
	// 	}
	// 	const std::string &field = parser::as<parser::StmtSimple>(stmt->rhs)->val.data.s;
	// 	llvm::StructType *st	 = llvm::cast<llvm::StructType>(l->getType());
	// 	int32_t idx    = parser::as<parser::TypeStruct>(stmt->type)->getFieldIndex(field);
	// 	llvm::Value *i = llvm::ConstantInt::get(b.getInt32Ty(), idx);
	// 	return b.CreateGEP(st, l, i, field);
	// }
	// case lex::FNCALL: {
	// 	stmt->lhs->disp(false);
	// 	if(!llvm::isa<llvm::Function>(l) && stmt->lhs->type->type != parser::TSTRUCT) {
	// 		err::set(stmt->line, stmt->col,
	// 			 "expected a function or struct for fncall operation");
	// 		return nullptr;
	// 	}
	// 	if(llvm::isa<llvm::Function>(l)) {
	// 		llvm::Function *f = llvm::cast<llvm::Function>(l);
	// 		std::vector<llvm::Value *> args;
	// 		for(auto &a : parser::as<parser::StmtFnCallInfo>(stmt->rhs)->args) {
	// 			llvm::Value *v = visit(a, m, b);
	// 			if(!v) {
	// 				err::set(a->line, a->col,
	// 					 "failed to generate IR for fncall arg");
	// 				return nullptr;
	// 			}
	// 			args.push_back(v);
	// 		}
	// 		return b.CreateCall(f, args);
	// 	} else if(stmt->lhs->type->type == parser::TSTRUCT) {
	// 		llvm::Type *type = GetLLType(c, stmt->lhs, stmt->lhs->type);
	// 		if(!type || !type->isStructTy()) {
	// 			err::set(stmt->lhs->line, stmt->lhs->col,
	// 				 "failed to get IR for scribe struct type '%s'",
	// 				 stmt->lhs->type->str().c_str());
	// 			return nullptr;
	// 		}
	// 		std::vector<llvm::Value *> args;
	// 		for(auto &a : parser::as<parser::StmtFnCallInfo>(stmt->rhs)->args) {
	// 			llvm::Value *v = visit(a, m, b);
	// 			if(!v) {
	// 				err::set(a->line, a->col,
	// 					 "failed to generate IR for fncall arg");
	// 				return nullptr;
	// 			}
	// 			args.push_back(v);
	// 		}
	// 		llvm::Value *alloca = AddVar(m, b, stmt, "<unnamed>", type, nullptr);
	// 		for(size_t i = 0; i < args.size(); ++i) {
	// 			llvm::Value *idx   = llvm::ConstantInt::get(b.getInt32Ty(), i);
	// 			llvm::Value *field = b.CreateGEP(type, alloca, idx);
	// 			b.CreateStore(args[i], field);
	// 		}
	// 		return alloca;
	// 	}
	// }
	// case lex::SUBS: {
	// }
	// }
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtVar *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	std::string varname = stmt->name.data.s + "." + std::to_string(stmt->type->id);

	llvm::Type *type   = GetLLType(c, stmt, stmt->type);
	llvm::Value *value = nullptr;
	if(stmt->value) {
		value = GetLLValue(c, stmt, stmt->value);
		if(!value) {
			err::set(stmt->line, stmt->col,
				 "failed to get LLVM value from scribe value: %s\n",
				 stmt->value->stringify().c_str());
			return nullptr;
		}
		goto createvar;
	}
	if(stmt->val && stmt->val->stmt_type == parser::FNDEF) {
		// check that function is not template or variadic
		llvm::Value *fn = visit(stmt->val, m, b);
		if(!fn) {
			err::set(stmt->name, "failed to generate IR for function");
			return nullptr;
		}
		llvm::Function *f = llvm::cast<llvm::Function>(fn);
		f->setName(varname);
		return f;
	}
	if(stmt->val && stmt->val->stmt_type == parser::STRUCTDEF) {
		// a structure definition is unnecessary
		return b.getTrue();
	}
	if(stmt->val && stmt->val->stmt_type == parser::EXPR &&
	   parser::as<parser::StmtExpr>(stmt->val)->isIntrinsic())
	{
		return b.getTrue();
	}

	if(stmt->val) {
		// any value with instrinsic should be in stmt->value (for above condition)
		value = visit(stmt->val, m, b);
		if(!value) {
			err::set(stmt->line, stmt->col,
				 "failed to get LLVM value from scribe declaration value");
			return nullptr;
		}
	}
createvar:
	return AddVar(m, b, stmt, varname, type, value);
}
llvm::Value *LLVMDriver::visit(parser::StmtFnSig *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtFnDef *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	llvm::FunctionType *ftype = llvm::cast<llvm::FunctionType>(GetLLType(c, stmt, stmt->type));
	llvm::Function *f = llvm::Function::Create(ftype, llvm::Function::InternalLinkage, "", m);
	for(size_t i = 0; i < stmt->sig->args.size(); ++i) {
		auto &arg = stmt->sig->args[i];
		f->getArg(i)->setName(arg->name.data.s + "." + std::to_string(arg->type->id));
	}
	if(!stmt->blk) return f;
	llvm::BasicBlock *entry	      = GetOrCreateBasicBlock(f, "entry", nullptr);
	llvm::BasicBlock *init_assign = GetOrCreateBasicBlock(f, "init_assign", nullptr);
	llvm::BasicBlock *content     = GetOrCreateBasicBlock(f, "content", nullptr);
	{
		llvm::IRBuilder<> newb(entry);
		newb.CreateBr(init_assign);
	}
	{
		llvm::IRBuilder<> newb(init_assign);
		newb.CreateBr(content);
	}
	llvm::IRBuilder<> newb(content);
	if(!visit(stmt->blk, m, newb)) {
		err::set(stmt->line, stmt->col, "failed to generate IR for function block");
		return nullptr;
	}
	f->setCallingConv(llvm::CallingConv::C);
	return f;
}
llvm::Value *LLVMDriver::visit(parser::StmtHeader *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtLib *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtExtern *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtEnum *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtStruct *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	llvm::Type *t = GetLLType(c, stmt, stmt->type);
	if(!t) {
		err::set(stmt->line, stmt->col, "failed to get IR type for scribe type '%s'",
			 stmt->type->str().c_str());
		return nullptr;
	}
	return AddVar(m, b, stmt, "struct." + std::to_string(stmt->type->id), t, nullptr);
}
llvm::Value *LLVMDriver::visit(parser::StmtVarDecl *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	for(auto &d : stmt->decls) {
		llvm::Value *v = visit(d, m, b);
		if(!v) {
			err::set(d->line, d->col, "failed to generate IR for variable declaration");
			return nullptr;
		}
	}
	return b.getTrue();
}
llvm::Value *LLVMDriver::visit(parser::StmtCond *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtForIn *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtFor *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtWhile *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtRet *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	if(!stmt->val) return b.CreateRetVoid();
	llvm::Value *v = visit(stmt->val, m, b);
	if(!v) {
		err::set(stmt->line, stmt->col, "failed to generate IR for return value");
		return nullptr;
	}
	return b.CreateRet(v);
}
llvm::Value *LLVMDriver::visit(parser::StmtContinue *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtBreak *stmt, llvm::Module *m, llvm::IRBuilder<> &b)
{
	return nullptr;
}

llvm::Value *LLVMDriver::AddVar(llvm::Module *m, llvm::IRBuilder<> &b, parser::Stmt *stmt,
				const std::string &varname, llvm::Type *type, llvm::Value *value)
{
	if(!b.GetInsertBlock()) {
		llvm::Value *gc		= m->getOrInsertGlobal(varname, type);
		llvm::GlobalVariable *g = llvm::cast<llvm::GlobalVariable>(gc);
		g->setLinkage(llvm::GlobalValue::InternalLinkage);
		g->setConstant(stmt->type->info & parser::CONST);
		if(value && llvm::isa<llvm::Constant>(value)) {
			llvm::Constant *c = llvm::cast<llvm::Constant>(value);
			g->setInitializer(c);
		}
		return g;
	}
	llvm::Function *f	 = b.GetInsertBlock()->getParent();
	llvm::AllocaInst *alloca = CreateEntryBlockAlloca(f, varname, type);
	if(value) CreateInitAssignAfterAlloca(f, alloca, value);
	return alloca;
}
llvm::BasicBlock *LLVMDriver::GetOrCreateBasicBlock(llvm::Function *f, const std::string &name,
						    llvm::BasicBlock *before)
{
	bool found = false;
	for(auto &bb : f->getBasicBlockList()) {
		if(bb.getName() == name) return &bb;
	}
	return llvm::BasicBlock::Create(c, name, f, before);
}
llvm::AllocaInst *LLVMDriver::CreateEntryBlockAlloca(llvm::Function *f, const std::string &varname,
						     llvm::Type *type)
{
	llvm::BasicBlock *bb = GetOrCreateBasicBlock(f, "entry", nullptr);
	llvm::IRBuilder<> b(bb->getTerminator());
	return b.CreateAlloca(type, 0, varname);
}
llvm::Value *LLVMDriver::CreateInitAssignAfterAlloca(llvm::Function *f, llvm::AllocaInst *alloca,
						     llvm::Value *value)
{
	llvm::BasicBlock *bb = GetOrCreateBasicBlock(f, "init_assign", nullptr);
	llvm::IRBuilder<> b(bb->getTerminator());
	llvm::LoadInst *load = b.CreateLoad(alloca->getType(), alloca);
	return b.CreateStore(value, load);
}

llvm::Value *LLVMDriver::GetVar(llvm::Module *m, llvm::IRBuilder<> &b, parser::StmtSimple *stmt,
				const std::string &varname)
{
	if(b.GetInsertBlock()) {
		llvm::Function *f	 = b.GetInsertBlock()->getParent();
		llvm::AllocaInst *alloca = GetEntryBlockAlloca(f, varname);
		if(alloca) return b.CreateLoad(alloca->getAllocatedType(), alloca);
		for(auto &a : f->args()) {
			if(a.getName() == varname) return &a;
		}
	}
	llvm::Value *g = m->getGlobalVariable(varname, true);
	if(!g) {
		err::set(stmt->val, "failed to get variable '%s'", varname.c_str());
		return nullptr;
	}
	return b.CreateLoad(g->getType(), g);
}
llvm::AllocaInst *LLVMDriver::GetEntryBlockAlloca(llvm::Function *f, const std::string &varname)
{
	for(auto &i : f->getEntryBlock()) {
		if(!llvm::isa<llvm::AllocaInst>(i)) continue;
		if(llvm::cast<llvm::AllocaInst>(i).getName() == varname) {
			return &llvm::cast<llvm::AllocaInst>(i);
		}
	}
	return nullptr;
}
} // namespace codegen
} // namespace sc