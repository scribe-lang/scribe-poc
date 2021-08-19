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

#include "parser/Type.hpp"

namespace sc
{
namespace parser
{
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
	for(size_t i = 0; i < stmt->stmts.size(); ++i) {
		cleanup(stmt->stmts[i], &stmt->stmts[i]);
		if(!stmt->stmts[i]) {
			stmt->stmts.erase(stmt->stmts.begin() + i);
			--i;
		}
	}
}
void cleanup(parser::StmtType *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtSimple *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtFnCallInfo *stmt, parser::Stmt **source) {}
void cleanup(parser::StmtExpr *stmt, parser::Stmt **source)
{
	if(stmt->lhs) cleanup(stmt->lhs, &stmt->lhs);
	if(stmt->rhs) cleanup(stmt->lhs, &stmt->rhs);

	if(stmt->oper.tok.val == lex::EMPTY) {
		stmt->lhs->parent = stmt->parent;
		*source		  = stmt->lhs;
		stmt->lhs	  = nullptr;
		delete stmt;
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
	for(size_t i = 0; i < stmt->args.size(); ++i) {
		cleanup(stmt->args[i], (Stmt **)&stmt->args[i]);
	}
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
} // namespace parser
} // namespace sc