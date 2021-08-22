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

#ifndef CODEGEN_C_DRIVER_HPP
#define CODEGEN_C_DRIVER_HPP

#include "codegen/Base.hpp"
#include "codegen/c/Writer.hpp"

namespace sc
{
namespace codegen
{
class CDriver : public Driver
{
	std::vector<std::string> headerflags;
	std::vector<std::string> libflags;
	std::vector<std::string> headers;
	std::vector<std::string> macros;
	std::vector<std::string> decls;
	Writer mod;

public:
	CDriver(parser::RAIIParser &parser);
	~CDriver();

	// generate C code
	bool genIR();
	// dump C code to output or optionally file
	bool dumpIR(const bool &force);
	// dump C code to file and compile
	bool genObjFile(const std::string &dest);

	bool visit(parser::Stmt *stmt, Writer &writer, const bool &semicolon);

	bool visit(parser::StmtBlock *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtType *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtSimple *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtFnCallInfo *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtExpr *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtVar *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtFnSig *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtFnDef *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtHeader *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtLib *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtExtern *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtEnum *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtStruct *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtVarDecl *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtCond *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtForIn *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtFor *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtWhile *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtRet *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtContinue *stmt, Writer &writer, const bool &semicolon);
	bool visit(parser::StmtBreak *stmt, Writer &writer, const bool &semicolon);
};
} // namespace codegen
} // namespace sc

#endif // CODEGEN_C_DRIVER_HPP