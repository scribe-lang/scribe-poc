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

#include "parser/Cleanup.hpp"

#include <cassert>

#include "parser/Type.hpp"

namespace sc
{
namespace parser
{
static void eraseTemplates(std::vector<Stmt *> &stmts);
static void removeVarDecls(StmtBlock *block);
static bool isTemplateFunctionVariable(Stmt *var);

void cleanup(parser::Stmt *stmt, parser::Stmt **source)
{
	switch(stmt->stmt_type) {
	case parser::BLOCK: cleanup(parser::as<parser::StmtBlock>(stmt), source); break;
	case parser::TYPE: cleanup(parser::as<parser::StmtType>(stmt), source); break;
	case parser::SIMPLE: cleanup(parser::as<parser::StmtSimple>(stmt), source); break;
	case parser::EXPR: cleanup(parser::as<parser::StmtExpr>(stmt), source); break;
	case parser::FNCALLINFO: cleanup(parser::as<parser::StmtFnCallInfo>(stmt), source); break;
	case parser::VAR: cleanup(parser::as<parser::StmtVar>(stmt), source); break;
	case parser::FNSIG: cleanup(parser::as<parser::StmtFnSig>(stmt), source); break;
	case parser::FNDEF: cleanup(parser::as<parser::StmtFnDef>(stmt), source); break;
	case parser::HEADER: cleanup(parser::as<parser::StmtHeader>(stmt), source); break;
	case parser::LIB: cleanup(parser::as<parser::StmtLib>(stmt), source); break;
	case parser::EXTERN: cleanup(parser::as<parser::StmtExtern>(stmt), source); break;
	case parser::ENUMDEF: cleanup(parser::as<parser::StmtEnum>(stmt), source); break;
	case parser::STRUCTDEF: cleanup(parser::as<parser::StmtStruct>(stmt), source); break;
	case parser::VARDECL: cleanup(parser::as<parser::StmtVarDecl>(stmt), source); break;
	case parser::COND: cleanup(parser::as<parser::StmtCond>(stmt), source); break;
	case parser::FORIN: cleanup(parser::as<parser::StmtForIn>(stmt), source); break;
	case parser::FOR: cleanup(parser::as<parser::StmtFor>(stmt), source); break;
	case parser::WHILE: cleanup(parser::as<parser::StmtWhile>(stmt), source); break;
	case parser::RET: cleanup(parser::as<parser::StmtRet>(stmt), source); break;
	case parser::CONTINUE: cleanup(parser::as<parser::StmtContinue>(stmt), source); break;
	case parser::BREAK: cleanup(parser::as<parser::StmtBreak>(stmt), source); break;
	}
}

void cleanup(parser::StmtBlock *stmt, parser::Stmt **source)
{
	removeVarDecls(stmt);
	for(size_t i = 0; i < stmt->stmts.size(); ++i) {
		if(isTemplateFunctionVariable(stmt->stmts[i])) continue;
		cleanup(stmt->stmts[i], &stmt->stmts[i]);
		if(!stmt->stmts[i]) {
			stmt->stmts.erase(stmt->stmts.begin() + i);
			--i;
		}
	}
	eraseTemplates(stmt->stmts);
}
void cleanup(parser::StmtType *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtSimple *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtFnCallInfo *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtExpr *stmt, parser::Stmt **source)
{
	if(stmt->lhs) cleanup(stmt->lhs, &stmt->lhs);
	if(stmt->rhs) cleanup(stmt->rhs, &stmt->rhs);

	if(stmt->oper.tok.val == lex::EMPTY) {
		stmt->lhs->parent = stmt->parent;
		*source		  = stmt->lhs;
		stmt->lhs	  = nullptr;
		delete stmt;
		return;
	}

	if(stmt->oper.tok.val == lex::SUBS && stmt->lhs->type->type == TVARIADIC && !stmt->value) {
		assert(stmt->lhs->stmt_type == SIMPLE &&
		       "variadic LHS must be a simple for cleanup");
		StmtSimple *ls = as<StmtSimple>(stmt->lhs);
		ls->val.data.s += "__" + std::to_string(stmt->rhs->value->i);
		TypeVariadic *tv = as<TypeVariadic>(ls->type);
		ls->type	 = tv->args[stmt->rhs->value->i]->copy();
		ls->parent	 = stmt->parent;
		*source		 = stmt->lhs;
		stmt->lhs	 = nullptr;
		delete tv;
		delete stmt;
		return;
	}
}
void cleanup(parser::StmtVar *stmt, parser::Stmt **source)
{
	// imports are irrelevant now
	if(stmt->type && stmt->type->type == TIMPORT) {
		delete stmt;
		*source = nullptr;
		return;
	}

	if(stmt->val) cleanup(stmt->val, &stmt->val);
	if(stmt->vtype) cleanup(stmt->vtype, (Stmt **)&stmt->vtype);
}
void cleanup(parser::StmtFnSig *stmt, parser::Stmt **source)
{
	if(stmt->args.empty()) goto retcleanup;

	// cleanup variadic, replace with normal variables
	if(stmt->args.back()->type->type == TVARIADIC) {
		StmtVar *vaarg = stmt->args.back();
		stmt->args.pop_back();
		TypeVariadic *vatype = as<TypeVariadic>(vaarg->type);
		Value *vaval	     = vaarg->value;

		Module *mod = vaarg->mod;
		size_t line = vaarg->line;
		size_t col  = vaarg->col;

		for(size_t i = 0; i < vatype->args.size(); ++i) {
			auto &a		 = vatype->args[i];
			lex::Lexeme name = vaarg->name;
			name.data.s += "__" + std::to_string(i);
			StmtVar *v = new StmtVar(mod, line, col, name, nullptr, nullptr);
			v->parent  = vaarg->parent;
			if(vaval) v->value = vaval->v[i];
			v->type	  = a;
			a->parent = v;
			stmt->args.push_back(v);
		}
		vatype->args.clear();
		delete vaarg;
	}

	for(size_t i = 0; i < stmt->args.size(); ++i) {
		cleanup(stmt->args[i], (Stmt **)&stmt->args[i]);
	}

retcleanup:
	if(stmt->rettype) cleanup(stmt->rettype, (Stmt **)&stmt->rettype);
}
void cleanup(parser::StmtFnDef *stmt, parser::Stmt **source)
{
	cleanup(stmt->sig, (Stmt **)&stmt->sig);
	if(stmt->blk) cleanup(stmt->blk, (Stmt **)&stmt->blk);
}
void cleanup(parser::StmtHeader *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtLib *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtExtern *stmt, parser::Stmt **source)
{
	cleanup(stmt->sig, (Stmt **)&stmt->sig);
	if(stmt->headers) cleanup(stmt->headers, (Stmt **)&stmt->headers);
	if(stmt->libs) cleanup(stmt->libs, (Stmt **)&stmt->libs);
}
void cleanup(parser::StmtEnum *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtStruct *stmt, parser::Stmt **source)
{
	for(size_t i = 0; i < stmt->fields.size(); ++i) {
		cleanup(stmt->fields[i], (Stmt **)&stmt->fields[i]);
	}
}
void cleanup(parser::StmtVarDecl *stmt, parser::Stmt **source)
{
	for(size_t i = 0; i < stmt->decls.size(); ++i) {
		cleanup(stmt->decls[i], (Stmt **)&stmt->decls[i]);
		if(!stmt->decls[i]) {
			stmt->decls.erase(stmt->decls.begin() + i);
			--i;
		}
	}
	if(stmt->decls.empty()) {
		delete stmt;
		*source = nullptr;
		return;
	}
}
void cleanup(parser::StmtCond *stmt, parser::Stmt **source)
{
	for(size_t i = 0; i < stmt->conds.size(); ++i) {
		auto &c = stmt->conds[i];
		if(c.cond) cleanup(c.cond, (Stmt **)&c.cond);
		cleanup(c.blk, (Stmt **)&c.blk);
	}
}
void cleanup(parser::StmtForIn *stmt, parser::Stmt **source)
{
	cleanup(stmt->in, (Stmt **)&stmt->in);
	cleanup(stmt->blk, (Stmt **)&stmt->blk);
}
void cleanup(parser::StmtFor *stmt, parser::Stmt **source)
{
	if(stmt->init) cleanup(stmt->init, (Stmt **)&stmt->init);
	if(stmt->cond) cleanup(stmt->cond, (Stmt **)&stmt->cond);
	if(stmt->incr) cleanup(stmt->incr, (Stmt **)&stmt->incr);
	cleanup(stmt->blk, (Stmt **)&stmt->blk);
}
void cleanup(parser::StmtWhile *stmt, parser::Stmt **source)
{
	if(stmt->cond) cleanup(stmt->cond, (Stmt **)&stmt->cond);
	cleanup(stmt->blk, (Stmt **)&stmt->blk);
}
void cleanup(parser::StmtRet *stmt, parser::Stmt **source)
{
	if(stmt->val) cleanup(stmt->val, (Stmt **)&stmt->val);
}
void cleanup(parser::StmtContinue *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtBreak *stmt, parser::Stmt **source) {}

static void eraseTemplates(std::vector<Stmt *> &stmts)
{
	if(stmts.empty()) return;

	for(size_t i = 0; i < stmts.size(); ++i) {
		if(!isTemplateFunctionVariable(stmts[i])) continue;
		Stmt *base	      = stmts[i];
		const size_t &spec_id = base->getSpecializedID();
		stmts.erase(stmts.begin() + i);
		if(!spec_id) {
			delete base;
			continue;
		}
		for(size_t j = i + 1; j < stmts.size(); ++j) {
			if(stmts[j]->getSpecializedID() != spec_id) continue;
			Stmt *found = stmts[j];
			stmts.erase(stmts.begin() + j);
			--j;
			stmts.insert(stmts.begin() + i, found);
			++i;
		}
		delete base;
		continue;
	}
}

static void removeVarDecls(StmtBlock *block)
{
	std::vector<Stmt *> &stmts = block->stmts;
	for(size_t i = 0; i < stmts.size(); ++i) {
		if(stmts[i]->stmt_type != VARDECL) continue;
		StmtVarDecl *vd = as<StmtVarDecl>(stmts[i]);
		stmts.erase(stmts.begin() + i);
		while(vd->decls.size() > 0) {
			auto *d	  = vd->decls.back();
			d->parent = block;
			stmts.insert(stmts.begin() + i, d);
			vd->decls.pop_back();
		}
		delete vd;
	}
}

static bool isTemplateFunctionVariable(Stmt *var)
{
	if(var->stmt_type != VAR) return false;
	StmtVar *v = as<StmtVar>(var);
	if(!v->val || v->val->stmt_type != FNDEF) return false;
	return !as<StmtFnDef>(v->val)->sig->templates.empty();
}
} // namespace parser
} // namespace sc