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

#ifndef PARSER_CLEANUP_HPP
#define PARSER_CLEANUP_HPP

#include "parser/Stmts.hpp"

namespace sc
{
namespace parser
{
void cleanup(parser::Stmt *stmt, parser::Stmt **source);

void cleanup(parser::StmtBlock *stmt, parser::Stmt **source);
void cleanup(parser::StmtType *stmt, parser::Stmt **source);
void cleanup(parser::StmtSimple *stmt, parser::Stmt **source);
void cleanup(parser::StmtFnCallInfo *stmt, parser::Stmt **source);
void cleanup(parser::StmtExpr *stmt, parser::Stmt **source);
void cleanup(parser::StmtVar *stmt, parser::Stmt **source);
void cleanup(parser::StmtFnSig *stmt, parser::Stmt **source);
void cleanup(parser::StmtFnDef *stmt, parser::Stmt **source);
void cleanup(parser::StmtHeader *stmt, parser::Stmt **source);
void cleanup(parser::StmtLib *stmt, parser::Stmt **source);
void cleanup(parser::StmtExtern *stmt, parser::Stmt **source);
void cleanup(parser::StmtEnum *stmt, parser::Stmt **source);
void cleanup(parser::StmtStruct *stmt, parser::Stmt **source);
void cleanup(parser::StmtVarDecl *stmt, parser::Stmt **source);
void cleanup(parser::StmtCond *stmt, parser::Stmt **source);
void cleanup(parser::StmtForIn *stmt, parser::Stmt **source);
void cleanup(parser::StmtFor *stmt, parser::Stmt **source);
void cleanup(parser::StmtWhile *stmt, parser::Stmt **source);
void cleanup(parser::StmtRet *stmt, parser::Stmt **source);
void cleanup(parser::StmtContinue *stmt, parser::Stmt **source);
void cleanup(parser::StmtBreak *stmt, parser::Stmt **source);
} // namespace parser
} // namespace sc

#endif // PARSER_CLEANUP_HPP