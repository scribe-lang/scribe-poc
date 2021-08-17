/*
	MIT License

	Copyright (c) 2021 Scribe Language Repositories

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copyodifyerge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#include "codegen/llvm/Driver.hpp"

#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include "codegen/llvm/Types.hpp"
#include "codegen/llvm/Values.hpp"
#include "Error.hpp"

namespace sc
{
namespace codegen
{
static std::unordered_map<std::string, llvm::Type *> structdefs;

static inline std::string GetMangledName(const std::string &name, parser::Type *type)
{
	return name + "." + std::to_string(type->id);
}

LLVMDriver::LLVMDriver(parser::RAIIParser &parser) : Driver(parser)
{
	mod = new llvm::Module(parser.getModuleStack().back(), c);
}
LLVMDriver::~LLVMDriver()
{
	delete mod;
}
bool LLVMDriver::setTargetTriple(const std::string &triple)
{
	mod->setTargetTriple(triple);
	std::string e;
	const llvm::Target *target = llvm::TargetRegistry::lookupTarget(triple, e);
	if(!target) {
		fprintf(stderr, "failed to get target triple with error: %s\n", e.c_str());
		return false;
	}
	llvm::TargetOptions opt;
	llvm::Optional<llvm::Reloc::Model> rm = llvm::Optional<llvm::Reloc::Model>();
	llvm::TargetMachine *tm = target->createTargetMachine(triple, "generic", "", opt, rm);
	mod->setDataLayout(tm->createDataLayout());
	return true;
}
bool LLVMDriver::genIR()
{
	const std::vector<std::string> &modulestack = parser.getModuleStack();
	for(auto it = modulestack.rbegin(); it != modulestack.rend(); ++it) {
		parser::Module *pmod = parser.getModule(*it);
		err::pushModule(pmod);
		parser::Stmt *&ptree = pmod->getParseTree();
		llvm::IRBuilder<> b(c);
		if(!visit(ptree, b)) {
			err::set(ptree->line, ptree->col, "failed to gen IR");
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
	mod->print(llvm::errs(), nullptr);
}
bool LLVMDriver::genObjFile(const std::string &dest)
{
	return true;
}

llvm::Value *LLVMDriver::visit(parser::Stmt *stmt, llvm::IRBuilder<> &b)
{
	switch(stmt->stmt_type) {
	case parser::BLOCK: return visit(parser::as<parser::StmtBlock>(stmt), b);
	case parser::TYPE: return visit(parser::as<parser::StmtType>(stmt), b);
	case parser::SIMPLE: return visit(parser::as<parser::StmtSimple>(stmt), b);
	case parser::EXPR: return visit(parser::as<parser::StmtExpr>(stmt), b);
	case parser::FNCALLINFO: return visit(parser::as<parser::StmtFnCallInfo>(stmt), b);
	case parser::VAR: return visit(parser::as<parser::StmtVar>(stmt), b);
	case parser::FNSIG: return visit(parser::as<parser::StmtFnSig>(stmt), b);
	case parser::FNDEF: return visit(parser::as<parser::StmtFnDef>(stmt), b);
	case parser::HEADER: return visit(parser::as<parser::StmtHeader>(stmt), b);
	case parser::LIB: return visit(parser::as<parser::StmtLib>(stmt), b);
	case parser::EXTERN: return visit(parser::as<parser::StmtExtern>(stmt), b);
	case parser::ENUMDEF: return visit(parser::as<parser::StmtEnum>(stmt), b);
	case parser::STRUCTDEF: return visit(parser::as<parser::StmtStruct>(stmt), b);
	case parser::VARDECL: return visit(parser::as<parser::StmtVarDecl>(stmt), b);
	case parser::COND: return visit(parser::as<parser::StmtCond>(stmt), b);
	case parser::FORIN: return visit(parser::as<parser::StmtForIn>(stmt), b);
	case parser::FOR: return visit(parser::as<parser::StmtFor>(stmt), b);
	case parser::WHILE: return visit(parser::as<parser::StmtWhile>(stmt), b);
	case parser::RET: return visit(parser::as<parser::StmtRet>(stmt), b);
	case parser::CONTINUE: return visit(parser::as<parser::StmtContinue>(stmt), b);
	case parser::BREAK: return visit(parser::as<parser::StmtBreak>(stmt), b);
	}
	return nullptr;
}

llvm::Value *LLVMDriver::visit(parser::StmtBlock *stmt, llvm::IRBuilder<> &b)
{
	for(auto &s : stmt->stmts) {
		if(!visit(s, b)) {
			err::set(s->line, s->col, "failed to generate IR for statement");
			return nullptr;
		}
	}
	return b.getTrue();
}
llvm::Value *LLVMDriver::visit(parser::StmtType *stmt, llvm::IRBuilder<> &b)
{
	// nothing to do here
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtSimple *stmt, llvm::IRBuilder<> &b)
{
	if(stmt->value) return GetLLValue(c, stmt, stmt->value);
	llvm::Type *t = GetLLType(c, stmt, stmt->type);
	switch(stmt->val.tok.val) {
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL:	 // fallthrough
	case lex::INT: return llvm::ConstantInt::get(t, stmt->val.data.i);
	case lex::FLT: return llvm::ConstantFP::get(t, stmt->val.data.f);
	case lex::CHAR: return llvm::ConstantInt::get(t, stmt->val.data.i);
	case lex::STR: return llvm::ConstantDataArray::getString(c, stmt->val.data.s);
	default: break;
	}
	// the following part is only valid for existing variables.
	// the part for variable declaration exists in Var visit
	std::string varname = GetMangledName(stmt->val.data.s, stmt->type);
	if(stmt->type->type == parser::TFUNC) {
		llvm::Function *f = mod->getFunction(varname);
		if(!f) {
			err::set(stmt->val, "function does not exist in IR");
			return nullptr;
		}
		return f;
	}
	llvm::Value *v = GetVar(b, stmt, varname);
	if(!v) {
		err::set(stmt->val, "variable does not exist in IR");
		return nullptr;
	}
	return v;
}
llvm::Value *LLVMDriver::visit(parser::StmtFnCallInfo *stmt, llvm::IRBuilder<> &b)
{
	// std::vector<llvm::Value *> vals;
	// for(auto &a : stmt->args) {
	// 	vals.push_back(visit(a, b));
	// 	if(!vals.back()) {
	// 		err::set(a->line, a->col,
	// 			 "failed to generate IR for function call argument");
	// 		return nullptr;
	// 	}
	// }
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtExpr *stmt, llvm::IRBuilder<> &b)
{
	if(stmt->value) return GetLLValue(c, stmt, stmt->value);

	const lex::TokType &oper = stmt->oper.tok.val;
	llvm::Value *l		 = visit(stmt->lhs, b);
	if(!l) {
		err::set(stmt->lhs->line, stmt->lhs->col, "failed to get IR for LHS");
		return nullptr;
	}
	llvm::Value *r = nullptr;
	if(stmt->rhs && oper != lex::DOT && oper != lex::FNCALL) r = visit(stmt->rhs, b);

	switch(oper) {
	case lex::DOT: {
		if(!l->getType()->isStructTy()) {
			err::set(stmt->line, stmt->col, "expected LHS load to give a struct type");
			return nullptr;
		}
		const std::string &field = parser::as<parser::StmtSimple>(stmt->rhs)->val.data.s;
		llvm::StructType *st	 = llvm::cast<llvm::StructType>(l->getType());
		int32_t idx    = parser::as<parser::TypeStruct>(stmt->type)->getFieldIndex(field);
		llvm::Value *i = llvm::ConstantInt::get(b.getInt32Ty(), idx);
		return b.CreateGEP(st, l, i, field);
	}
	case lex::FNCALL: {
		if(!llvm::isa<llvm::Function>(l) && stmt->lhs->type->type != parser::TSTRUCT) {
			err::set(stmt->line, stmt->col,
				 "expected a function or struct for fncall operation");
			return nullptr;
		}
		if(llvm::isa<llvm::Function>(l)) {
			llvm::Function *f = llvm::cast<llvm::Function>(l);
			std::vector<llvm::Value *> args;
			for(auto &a : parser::as<parser::StmtFnCallInfo>(stmt->rhs)->args) {
				llvm::Value *v = visit(a, b);
				if(!v) {
					err::set(a->line, a->col,
						 "failed to generate IR for fncall arg");
					return nullptr;
				}
				args.push_back(v);
			}
			return b.CreateCall(f, args);
		} else if(stmt->lhs->type->type == parser::TSTRUCT) {
			std::vector<llvm::Value *> args;
			for(auto &a : parser::as<parser::StmtFnCallInfo>(stmt->rhs)->args) {
				llvm::Value *v = visit(a, b);
				if(!v) {
					err::set(a->line, a->col,
						 "failed to generate IR for fncall arg");
					return nullptr;
				}
				args.push_back(v);
			}
			for(size_t i = 0; i < args.size(); ++i) {
				llvm::Value *idx0 = llvm::ConstantInt::get(b.getInt32Ty(), 0);
				llvm::Value *idx  = llvm::ConstantInt::get(b.getInt32Ty(), i);
				// llvm::Value *field = b.CreateGEP(l->getType(), l, {idx0, idx});
				// b.CreateStore(args[i], field);
			}
			return l;
		}
	}
	case lex::SUBS: {
	}
	}
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtVar *stmt, llvm::IRBuilder<> &b)
{
	std::string varname = GetMangledName(stmt->name.data.s, stmt->type);

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
		llvm::Value *fn = visit(stmt->val, b);
		if(!fn) {
			err::set(stmt->name, "failed to generate IR for function");
			return nullptr;
		}
		llvm::Function *f = llvm::cast<llvm::Function>(fn);
		f->setName(varname);
		return f;
	}
	if(stmt->val && stmt->val->stmt_type == parser::STRUCTDEF) {
		llvm::Type *ty	     = GetLLType(c, stmt->val, stmt->val->type);
		llvm::StructType *st = llvm::cast<llvm::StructType>(ty);
		st->setName(varname);
		structdefs[varname] = st;
		return b.getTrue();
	}

	if(stmt->val) {
		// any value with instrinsic should be in stmt->value (for above condition)
		value = visit(stmt->val, b);
		if(!value) {
			err::set(stmt->line, stmt->col,
				 "failed to get LLVM value from scribe declaration value");
			return nullptr;
		}
	}
createvar:
	llvm::Type *type = value ? value->getType() : GetLLType(c, stmt, stmt->type);
	return AddVar(b, stmt, varname, type, value);
}
llvm::Value *LLVMDriver::visit(parser::StmtFnSig *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtFnDef *stmt, llvm::IRBuilder<> &b)
{
	llvm::FunctionType *ftype = llvm::cast<llvm::FunctionType>(GetLLType(c, stmt, stmt->type));
	llvm::Function *f = llvm::Function::Create(ftype, llvm::Function::InternalLinkage, "", mod);
	for(size_t i = 0; i < stmt->sig->args.size(); ++i) {
		auto &arg = stmt->sig->args[i];
		f->getArg(i)->setName(GetMangledName(arg->name.data.s, arg->type));
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
	if(!visit(stmt->blk, newb)) {
		err::set(stmt->line, stmt->col, "failed to generate IR for function block");
		return nullptr;
	}
	f->setCallingConv(llvm::CallingConv::C);
	return f;
}
llvm::Value *LLVMDriver::visit(parser::StmtHeader *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtLib *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtExtern *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtEnum *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtStruct *stmt, llvm::IRBuilder<> &b)
{
	// should never be encountered - cleanup pass removes this
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtVarDecl *stmt, llvm::IRBuilder<> &b)
{
	for(auto &d : stmt->decls) {
		llvm::Value *v = visit(d, b);
		if(!v) {
			err::set(d->line, d->col, "failed to generate IR for variable declaration");
			return nullptr;
		}
	}
	return b.getTrue();
}
llvm::Value *LLVMDriver::visit(parser::StmtCond *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtForIn *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtFor *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtWhile *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtRet *stmt, llvm::IRBuilder<> &b)
{
	if(!stmt->val) return b.CreateRetVoid();
	llvm::Value *v = visit(stmt->val, b);
	if(!v) {
		err::set(stmt->line, stmt->col, "failed to generate IR for return value");
		return nullptr;
	}
	return b.CreateRet(v);
}
llvm::Value *LLVMDriver::visit(parser::StmtContinue *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}
llvm::Value *LLVMDriver::visit(parser::StmtBreak *stmt, llvm::IRBuilder<> &b)
{
	return nullptr;
}

llvm::Value *LLVMDriver::AddVar(llvm::IRBuilder<> &b, parser::Stmt *stmt,
				const std::string &varname, llvm::Type *type, llvm::Value *value)
{
	if(!b.GetInsertBlock()) {
		llvm::Value *gc		= mod->getOrInsertGlobal(varname, type);
		llvm::GlobalVariable *g = llvm::cast<llvm::GlobalVariable>(gc);
		g->setLinkage(llvm::GlobalValue::PrivateLinkage);
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

llvm::Value *LLVMDriver::GetVar(llvm::IRBuilder<> &b, parser::StmtSimple *stmt,
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

	llvm::Value *g = mod->getGlobalVariable(varname, true);
	if(g) return b.CreateLoad(g->getType(), g);

	auto ty = structdefs.find(varname);
	if(ty == structdefs.end()) {
		err::set(stmt->val, "failed to get entity named '%s'", varname.c_str());
		return nullptr;
	}
	return AddVar(b, stmt, varname, ty->second, nullptr);
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