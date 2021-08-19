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

#include "codegen/c/Driver.hpp"

#include "codegen/c/Preface.hpp"
#include "codegen/c/Types.hpp"
#include "codegen/c/Values.hpp"
#include "Error.hpp"

namespace sc
{
namespace codegen
{
// maps <type>.<id> to typename
static std::unordered_map<std::string, std::string> typenames;

static inline std::string GetMangledName(const std::string &name, parser::Type *type)
{
	return name;
}

CDriver::CDriver(parser::RAIIParser &parser) : Driver(parser)
{
	mod.write(preface);
}
CDriver::~CDriver() {}
bool CDriver::genIR()
{
	const std::vector<std::string> &modulestack = parser.getModuleStack();
	for(auto it = modulestack.rbegin(); it != modulestack.rend(); ++it) {
		parser::Module *pmod = parser.getModule(*it);
		err::pushModule(pmod);
		parser::Stmt *&ptree = pmod->getParseTree();
		if(!visit(ptree, mod)) {
			err::set(ptree->line, ptree->col, "failed to transpile to C");
			err::show(stderr);
			return false;
		}
		err::popModule();
	}
	return true;
}
void CDriver::dumpIR(const bool &force)
{
	if(!args.has("ir") && !force) return;
	printf("%s\n", mod.getData().c_str());
}
bool CDriver::genObjFile(const std::string &dest)
{
	return true;
}

bool CDriver::visit(parser::Stmt *stmt, Writer &writer)
{
	switch(stmt->stmt_type) {
	case parser::BLOCK: return visit(parser::as<parser::StmtBlock>(stmt), writer);
	case parser::TYPE: return visit(parser::as<parser::StmtType>(stmt), writer);
	case parser::SIMPLE: return visit(parser::as<parser::StmtSimple>(stmt), writer);
	case parser::EXPR: return visit(parser::as<parser::StmtExpr>(stmt), writer);
	case parser::FNCALLINFO: return visit(parser::as<parser::StmtFnCallInfo>(stmt), writer);
	case parser::VAR: return visit(parser::as<parser::StmtVar>(stmt), writer);
	case parser::FNSIG: return visit(parser::as<parser::StmtFnSig>(stmt), writer);
	case parser::FNDEF: return visit(parser::as<parser::StmtFnDef>(stmt), writer);
	case parser::HEADER: return visit(parser::as<parser::StmtHeader>(stmt), writer);
	case parser::LIB: return visit(parser::as<parser::StmtLib>(stmt), writer);
	case parser::EXTERN: return visit(parser::as<parser::StmtExtern>(stmt), writer);
	case parser::ENUMDEF: return visit(parser::as<parser::StmtEnum>(stmt), writer);
	case parser::STRUCTDEF: return visit(parser::as<parser::StmtStruct>(stmt), writer);
	case parser::VARDECL: return visit(parser::as<parser::StmtVarDecl>(stmt), writer);
	case parser::COND: return visit(parser::as<parser::StmtCond>(stmt), writer);
	case parser::FORIN: return visit(parser::as<parser::StmtForIn>(stmt), writer);
	case parser::FOR: return visit(parser::as<parser::StmtFor>(stmt), writer);
	case parser::WHILE: return visit(parser::as<parser::StmtWhile>(stmt), writer);
	case parser::RET: return visit(parser::as<parser::StmtRet>(stmt), writer);
	case parser::CONTINUE: return visit(parser::as<parser::StmtContinue>(stmt), writer);
	case parser::BREAK: return visit(parser::as<parser::StmtBreak>(stmt), writer);
	}
	return false;
}

bool CDriver::visit(parser::StmtBlock *stmt, Writer &writer)
{
	if(stmt->parent) {
		writer.write("{");
		writer.addIndent();
		writer.newLine();
	}
	for(size_t i = 0; i < stmt->stmts.size(); ++i) {
		auto &s = stmt->stmts[i];
		Writer tmp;
		if(!visit(s, tmp)) {
			err::set(s->line, s->col, "failed to generate IR for statement");
			return false;
		}
		writer.append(tmp);
		if(i < stmt->stmts.size() - 1) writer.newLine();
	}
	if(stmt->parent) {
		writer.remIndent();
		writer.newLine();
		writer.write("}");
	}
	return true;
}
bool CDriver::visit(parser::StmtType *stmt, Writer &writer)
{
	writer.clear();
	// nothing to do here
	return false;
}
bool CDriver::visit(parser::StmtSimple *stmt, Writer &writer)
{
	writer.clear();
	if(stmt->value) {
		writer.write(GetCValue(stmt, stmt->value));
		return true;
	}
	switch(stmt->val.tok.val) {
	case lex::TRUE:	 // fallthrough
	case lex::FALSE: // fallthrough
	case lex::NIL:	 // fallthrough
	case lex::INT: writer.write(stmt->val.data.i); return true;
	case lex::FLT: writer.write((double)stmt->val.data.f); return true;
	case lex::CHAR: writer.writeConstChar(stmt->val.data.i); return true;
	case lex::STR: writer.writeConstString(stmt->val.data.s); return true;
	default: break;
	}
	// the following part is only valid for existing variables.
	// the part for variable declaration exists in Var visit
	writer.write(GetMangledName(stmt->val.data.s, stmt->type));
	return true;
}
bool CDriver::visit(parser::StmtFnCallInfo *stmt, Writer &writer)
{
	writer.clear();
	return false;
}
bool CDriver::visit(parser::StmtExpr *stmt, Writer &writer)
{
	writer.clear();
	if(stmt->value) {
		writer.write(GetCValue(stmt, stmt->value));
		return true;
	}

	const lex::TokType &oper = stmt->oper.tok.val;
	Writer l;
	if(!visit(stmt->lhs, l)) {
		err::set(stmt->lhs->line, stmt->lhs->col, "failed to generate C code for LHS");
		return false;
	}
	Writer r;
	if(stmt->rhs && oper != lex::DOT && oper != lex::FNCALL && !visit(stmt->rhs, r)) {
		err::set(stmt->rhs->line, stmt->rhs->col, "failed to generate C code for RHS");
		return false;
	}

	switch(oper) {
	case lex::DOT: {
		const std::string &field = parser::as<parser::StmtSimple>(stmt->rhs)->val.data.s;
		writer.append(l);
		writer.write("." + field);
		return true;
	}
	case lex::FNCALL: {
		bool is_struct = stmt->lhs->type->type == parser::TSTRUCT;
		if(!is_struct) writer.append(l);
		writer.write(is_struct ? "{" : "(");
		auto &args = parser::as<parser::StmtFnCallInfo>(stmt->rhs)->args;
		for(size_t i = 0; i < args.size(); ++i) {
			auto &a = args[i];
			Writer tmp;
			if(!visit(a, tmp)) {
				err::set(a->line, a->col,
					 "failed to generate C code for fncall arg");
				return false;
			}
			writer.append(tmp);
			if(i < args.size() - 1) writer.write(", ");
		}
		writer.write(is_struct ? "}" : ")");
		return true;
	}
	case lex::SUBS: {
	}
	}
	return false;
}
bool CDriver::visit(parser::StmtVar *stmt, Writer &writer)
{
	writer.clear();
	std::string varname = GetMangledName(stmt->name.data.s, stmt->type);

	if(stmt->value) {
		std::string type = GetCType(stmt, stmt->type);
		writer.write("%s %s = %s", type.c_str(), varname.c_str(),
			     GetCValue(stmt, stmt->value).c_str());
		return true;
	}
	if(stmt->val && stmt->val->stmt_type == parser::FNDEF) {
		Writer tmp(writer);
		tmp.write(varname);
		if(!visit(stmt->val, tmp)) {
			err::set(stmt->name, "failed to generate IR for function def");
			return false;
		}
		writer.append(tmp);
		return true;
	}
	if(stmt->val && stmt->val->stmt_type == parser::STRUCTDEF) {
		writer.write("typedef struct ", varname.c_str());
		if(!visit(stmt->val, writer)) {
			err::set(stmt->name, "failed to generate IR for struct def");
			return false;
		}
		writer.write(" %s", varname.c_str());
		typenames["struct." + std::to_string(stmt->val->type->id)] = varname;
		return true;
	}

	Writer tmp;
	if(stmt->val && !visit(stmt->val, tmp)) {
		err::set(stmt->line, stmt->col,
			 "failed to get C value from scribe declaration value");
		return false;
	}
	std::string type;
	if(stmt->type->type == parser::TSTRUCT) {
		type = typenames["struct." + std::to_string(stmt->type->id)];
	} else {
		type = GetCType(stmt, stmt->type);
	}
	writer.write("%s %s", type.c_str(), varname.c_str());
	if(!tmp.empty()) {
		writer.write(" = ");
		writer.append(tmp);
	}
	return true;
}
bool CDriver::visit(parser::StmtFnSig *stmt, Writer &writer)
{
	writer.writeBefore(GetCType(stmt->rettype, stmt->rettype->type) + " ");
	writer.write("(");
	for(size_t i = 0; i < stmt->args.size(); ++i) {
		auto &a = stmt->args[i];
		Writer tmp;
		if(!visit(a, tmp)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for function arg");
			return false;
		}
		writer.append(tmp);
		if(i < stmt->args.size() - 1) writer.write(", ");
	}
	writer.write(")");
	return true;
}
bool CDriver::visit(parser::StmtFnDef *stmt, Writer &writer)
{
	if(!visit(stmt->sig, writer)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for function");
		return false;
	}
	if(!stmt->blk) return true;
	writer.write(" ");
	if(!visit(stmt->blk, writer)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for function block");
		return false;
	}
	return true;
}
bool CDriver::visit(parser::StmtHeader *stmt, Writer &writer)
{
	return false;
}
bool CDriver::visit(parser::StmtLib *stmt, Writer &writer)
{
	return false;
}
bool CDriver::visit(parser::StmtExtern *stmt, Writer &writer)
{
	return false;
}
bool CDriver::visit(parser::StmtEnum *stmt, Writer &writer)
{
	return false;
}
bool CDriver::visit(parser::StmtStruct *stmt, Writer &writer)
{
	writer.write("{");
	writer.addIndent();
	writer.newLine();
	for(size_t i = 0; i < stmt->fields.size(); ++i) {
		auto &f = stmt->fields[i];
		Writer tmp;
		if(!visit(f, tmp)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for struct field");
			return false;
		}
		writer.append(tmp);
		writer.write(";");
		if(i < stmt->fields.size() - 1) writer.newLine();
	}
	writer.remIndent();
	writer.newLine();
	writer.write("}");
	return true;
}
bool CDriver::visit(parser::StmtVarDecl *stmt, Writer &writer)
{
	for(auto &d : stmt->decls) {
		Writer tmp;
		if(!visit(d, tmp)) {
			err::set(d->line, d->col,
				 "failed to generate C code for variable declaration");
			return false;
		}
		writer.append(tmp);
		writer.write(";");
	}
	return true;
}
bool CDriver::visit(parser::StmtCond *stmt, Writer &writer)
{
	if(stmt->isInline()) {
		if(!visit(stmt->conds.back().blk, writer)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for inline conditional block");
			return false;
		}
		return true;
	}
	for(size_t i = 0; i < stmt->conds.size(); ++i) {
		auto &c = stmt->conds[i];
		if(i > 0) writer.write(" else ");
		if(c.cond) {
			writer.write("if(");
			Writer tmp;
			if(!visit(c.cond, tmp)) {
				err::set(c.cond->line, c.cond->col,
					 "failed to generate C code for conditional");
				return false;
			}
			writer.append(tmp);
			writer.write(") ");
		}
		if(!visit(c.blk, writer)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for conditional block");
			return false;
		}
	}
	return true;
}
bool CDriver::visit(parser::StmtForIn *stmt, Writer &writer)
{
	return false;
}
bool CDriver::visit(parser::StmtFor *stmt, Writer &writer)
{
	if(stmt->isInline()) {
		Writer tmp;
		if(!visit(stmt->init, tmp)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for inline for-loop init");
			return false;
		}
		writer.append(tmp);
		writer.write(";");
		writer.newLine();
		tmp.clear();
		if(!visit(stmt->blk, tmp)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for inline for-loop block");
			return false;
		}
		writer.append(tmp);
		return true;
	}
	writer.write("for(");
	if(stmt->init) {
		Writer tmp;
		if(!visit(stmt->init, tmp)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for for-loop init");
			return false;
		}
		writer.append(tmp);
	}
	writer.write(";");
	if(stmt->cond) {
		Writer tmp;
		if(!visit(stmt->cond, tmp)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for for-loop condition");
			return false;
		}
		writer.append(tmp);
	}
	writer.write(";");
	if(stmt->incr) {
		Writer tmp;
		if(!visit(stmt->incr, tmp)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for for-loop incr");
			return false;
		}
		writer.append(tmp);
	}
	writer.write(") ");
	Writer tmp;
	if(!visit(stmt->blk, tmp)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for while block");
		return false;
	}
	writer.append(tmp);
	return true;
}
bool CDriver::visit(parser::StmtWhile *stmt, Writer &writer)
{
	writer.clear();
	writer.write("while(");
	Writer tmp;
	if(!visit(stmt->cond, tmp)) {
		err::set(stmt->line, stmt->col,
			 "failed to generate C code for while-loop condition");
		return false;
	}
	writer.append(tmp);
	writer.write(") ");
	tmp.clear();
	if(!visit(stmt->blk, tmp)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for while block");
		return false;
	}
	writer.append(tmp);
	return true;
}
bool CDriver::visit(parser::StmtRet *stmt, Writer &writer)
{
	if(!stmt->val) {
		writer.write("return;");
		return true;
	}
	Writer tmp;
	if(!visit(stmt->val, tmp)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for return value");
		return false;
	}
	writer.write("return ");
	writer.append(tmp);
	writer.write(";");
	return true;
}
bool CDriver::visit(parser::StmtContinue *stmt, Writer &writer)
{
	writer.write("continue;");
	return true;
}
bool CDriver::visit(parser::StmtBreak *stmt, Writer &writer)
{
	writer.write("break;");
	return true;
}
} // namespace codegen
} // namespace sc