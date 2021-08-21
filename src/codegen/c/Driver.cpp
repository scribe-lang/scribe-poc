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
#include "Utils.hpp"

namespace sc
{
namespace codegen
{
// maps <type>.<id> to typename
static std::unordered_map<std::string, std::string> typenames;

static bool AcceptsSemicolon(parser::Stmt *stmt);
bool TrySetMainFunction(parser::StmtVar *var, const std::string &varname, Writer &writer);

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
		if(!visit(ptree, mod, false)) {
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

bool CDriver::visit(parser::Stmt *stmt, Writer &writer, const bool &semicolon)
{
	using namespace parser;

	// C does not permit modification of variables outside a function
	// therefore, make everything except VAR be unplaceable outside a function
	if(stmt->stmt_type != parser::VAR && stmt->stmt_type != parser::BLOCK &&
	   !stmt->getParentWithType(parser::FNDEF))
	{
		err::set(stmt->line, stmt->col,
			 "failed to generate C code - C does not allow anything except "
			 "declarations/definitions outside a function; found: %s",
			 stmt->stmtTypeString().c_str());
		return false;
	}

	bool res = false;
	Writer tmp;
	switch(stmt->stmt_type) {
	case BLOCK: res = visit(as<StmtBlock>(stmt), tmp, semicolon); break;
	case TYPE: res = visit(as<StmtType>(stmt), tmp, semicolon); break;
	case SIMPLE: res = visit(as<StmtSimple>(stmt), tmp, semicolon); break;
	case EXPR: res = visit(as<StmtExpr>(stmt), tmp, semicolon); break;
	case FNCALLINFO: res = visit(as<StmtFnCallInfo>(stmt), tmp, semicolon); break;
	case VAR: res = visit(as<StmtVar>(stmt), tmp, semicolon); break;
	case FNSIG: res = visit(as<StmtFnSig>(stmt), tmp, semicolon); break;
	case FNDEF: res = visit(as<StmtFnDef>(stmt), tmp, semicolon); break;
	case HEADER: res = visit(as<StmtHeader>(stmt), tmp, semicolon); break;
	case LIB: res = visit(as<StmtLib>(stmt), tmp, semicolon); break;
	case EXTERN: res = visit(as<StmtExtern>(stmt), tmp, semicolon); break;
	case ENUMDEF: res = visit(as<StmtEnum>(stmt), tmp, semicolon); break;
	case STRUCTDEF: res = visit(as<StmtStruct>(stmt), tmp, semicolon); break;
	case VARDECL: res = visit(as<StmtVarDecl>(stmt), tmp, semicolon); break;
	case COND: res = visit(as<StmtCond>(stmt), tmp, semicolon); break;
	case FORIN: res = visit(as<StmtForIn>(stmt), tmp, semicolon); break;
	case FOR: res = visit(as<StmtFor>(stmt), tmp, semicolon); break;
	case WHILE: res = visit(as<StmtWhile>(stmt), tmp, semicolon); break;
	case RET: res = visit(as<StmtRet>(stmt), tmp, semicolon); break;
	case CONTINUE: res = visit(as<StmtContinue>(stmt), tmp, semicolon); break;
	case BREAK: res = visit(as<StmtBreak>(stmt), tmp, semicolon); break;
	default: err::set(stmt->line, stmt->col, "invalid statement for C codegen"); return false;
	}
	if(stmt->isCast()) {
		writer.write("(");
		writer.write(GetCType(stmt, stmt->type));
		writer.write(")(");
		writer.append(tmp);
		writer.write(")");
	} else {
		writer.append(tmp);
	}
	return res;
}

bool CDriver::visit(parser::StmtBlock *stmt, Writer &writer, const bool &semicolon)
{
	if(stmt->parent) {
		writer.write("{");
		writer.addIndent();
		writer.newLine();
	}
	for(size_t i = 0; i < stmt->stmts.size(); ++i) {
		auto &s = stmt->stmts[i];
		Writer tmp;
		if(!visit(s, tmp, AcceptsSemicolon(s))) {
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
	if(semicolon) writer.write(";");
	return true;
}
bool CDriver::visit(parser::StmtType *stmt, Writer &writer, const bool &semicolon)
{
	writer.clear();
	// nothing to do here
	return false;
}
bool CDriver::visit(parser::StmtSimple *stmt, Writer &writer, const bool &semicolon)
{
	writer.clear();
	if(stmt->value) {
		writer.write(GetCValue(stmt, stmt->value, stmt->type));
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
	if(stmt->type->info & parser::REF) writer.write("*"); // for references
	writer.write(GetMangledName(stmt->val.data.s, stmt->type));
	if(semicolon) writer.write(";");
	return true;
}
bool CDriver::visit(parser::StmtFnCallInfo *stmt, Writer &writer, const bool &semicolon)
{
	writer.clear();
	return false;
}
bool CDriver::visit(parser::StmtExpr *stmt, Writer &writer, const bool &semicolon)
{
	writer.clear();
	if(stmt->value) {
		writer.write(GetCValue(stmt, stmt->value, stmt->type));
		if(semicolon) writer.write(";");
		return true;
	}

	const lex::TokType &oper = stmt->oper.tok.val;
	Writer l;
	if(!visit(stmt->lhs, l, false)) {
		err::set(stmt->lhs->line, stmt->lhs->col, "failed to generate C code for LHS");
		return false;
	}
	Writer r;
	if(stmt->rhs && oper != lex::DOT && oper != lex::FNCALL && !visit(stmt->rhs, r, false)) {
		err::set(stmt->rhs->line, stmt->rhs->col, "failed to generate C code for RHS");
		return false;
	}

	switch(oper) {
	case lex::ARROW: // fallthrough
	case lex::DOT: {
		const std::string &field = parser::as<parser::StmtSimple>(stmt->rhs)->val.data.s;
		writer.append(l);
		writer.write((oper == lex::DOT ? "." : "->") + field);
		break;
	}
	case lex::FNCALL: {
		bool is_struct = stmt->lhs->type->type == parser::TSTRUCT;
		if(!is_struct) writer.append(l);
		writer.write(is_struct ? "{" : "(");
		auto &args = parser::as<parser::StmtFnCallInfo>(stmt->rhs)->args;
		for(size_t i = 0; i < args.size(); ++i) {
			auto &a = args[i];
			Writer tmp;
			if(!visit(a, tmp, false)) {
				err::set(a->line, a->col,
					 "failed to generate C code for fncall arg");
				return false;
			}
			writer.append(tmp);
			if(i < args.size() - 1) writer.write(", ");
		}
		writer.write(is_struct ? "}" : ")");
		break;
	}
	case lex::UAND: {
		writer.write("&");
		writer.append(l);
		break;
	}
	case lex::UMUL: {
		writer.write("*");
		writer.append(l);
		break;
	}
	case lex::SUBS: {
		if(stmt->lhs->type->ptr > 0) {
			writer.append(l);
			writer.write("[");
			writer.append(r);
			writer.write("]");
			break;
		}
	}
	default: {
		bool all_primitives = true;
		all_primitives &= stmt->lhs->type->primitiveCompatible();
		if(stmt->rhs) all_primitives &= stmt->rhs->type->primitiveCompatible();
		if(all_primitives) {
			if(stmt->rhs) {
				writer.append(l);
				writer.write(" %s ", stmt->oper.tok.cstr());
				writer.append(r);
			} else if(stmt->oper.tok.isUnaryPre()) {
				writer.write("%s", stmt->oper.tok.getUnaryNoCharCStr());
				writer.append(l);
			} else { // isUnaryPost()
				writer.append(l);
				writer.write("%s", stmt->oper.tok.getUnaryNoCharCStr());
			}
			break;
		}
		std::string fnname = stmt->oper.tok.getOperCStr();
		writer.write(fnname);
		writer.write("(");
		writer.append(l);
		if(stmt->rhs) {
			writer.write(", ");
			writer.append(r);
		}
		break;
	}
	}
	if(semicolon) writer.write(";");
	return true;
}
bool CDriver::visit(parser::StmtVar *stmt, Writer &writer, const bool &semicolon)
{
	writer.clear();
	std::string varname = GetMangledName(stmt->name.data.s, stmt->type);

	if(stmt->value) {
		std::string type;
		if(stmt->type->type == parser::TSTRUCT) {
			type = typenames["struct." + std::to_string(stmt->type->id)];
		} else {
			type = GetCType(stmt, stmt->type);
		}
		writer.write("%s %s = %s", type.c_str(), varname.c_str(),
			     GetCValue(stmt, stmt->value, stmt->type).c_str());
		if(semicolon) writer.write(";");
		return true;
	}
	if(stmt->val && stmt->val->stmt_type == parser::FNDEF) {
		Writer tmp(writer);
		if(!visit(stmt->val, tmp, false)) {
			err::set(stmt->name, "failed to generate IR for function def");
			return false;
		}
		parser::StmtFnDef *fn = parser::as<parser::StmtFnDef>(stmt->val);
		std::string ret	      = GetCType(fn->sig->rettype, fn->sig->rettype->type);

		// set as entry point (main function) if signature matches
		static bool maindone = false;
		if(!maindone && TrySetMainFunction(stmt, varname, writer)) {
			maindone = true;
			varname	 = "main";
		}

		tmp.insertAfter(ret.size(), " " + varname);
		writer.append(tmp);
		// no semicolon after fndef
		return true;
	}
	if(stmt->val && stmt->val->stmt_type == parser::STRUCTDEF) {
		writer.write("typedef struct ", varname.c_str());
		if(!visit(stmt->val, writer, false)) {
			err::set(stmt->name, "failed to generate IR for struct def");
			return false;
		}
		writer.write(" %s", varname.c_str());
		typenames["struct." + std::to_string(stmt->val->type->id)] = varname;
		if(semicolon) writer.write(";");
		return true;
	}

	Writer tmp;
	if(stmt->val && !visit(stmt->val, tmp, false)) {
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
	if(semicolon) writer.write(";");
	return true;
}
bool CDriver::visit(parser::StmtFnSig *stmt, Writer &writer, const bool &semicolon)
{
	writer.write(GetCType(stmt->rettype, stmt->rettype->type));
	writer.write("(");
	for(size_t i = 0; i < stmt->args.size(); ++i) {
		auto &a = stmt->args[i];
		Writer tmp;
		if(!visit(a, tmp, false)) {
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
bool CDriver::visit(parser::StmtFnDef *stmt, Writer &writer, const bool &semicolon)
{
	if(!visit(stmt->sig, writer, false)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for function");
		return false;
	}
	if(!stmt->blk) return true;
	writer.write(" ");
	if(!visit(stmt->blk, writer, false)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for function block");
		return false;
	}
	return true;
}
bool CDriver::visit(parser::StmtHeader *stmt, Writer &writer, const bool &semicolon)
{
	return false;
}
bool CDriver::visit(parser::StmtLib *stmt, Writer &writer, const bool &semicolon)
{
	return false;
}
bool CDriver::visit(parser::StmtExtern *stmt, Writer &writer, const bool &semicolon)
{
	return false;
}
bool CDriver::visit(parser::StmtEnum *stmt, Writer &writer, const bool &semicolon)
{
	return false;
}
bool CDriver::visit(parser::StmtStruct *stmt, Writer &writer, const bool &semicolon)
{
	writer.write("{");
	writer.addIndent();
	writer.newLine();
	for(size_t i = 0; i < stmt->fields.size(); ++i) {
		auto &f = stmt->fields[i];
		Writer tmp;
		if(!visit(f, tmp, true)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for struct field");
			return false;
		}
		writer.append(tmp);
		if(i < stmt->fields.size() - 1) writer.newLine();
	}
	writer.remIndent();
	writer.newLine();
	writer.write("}");
	return true;
}
bool CDriver::visit(parser::StmtVarDecl *stmt, Writer &writer, const bool &semicolon)
{
	for(auto &d : stmt->decls) {
		Writer tmp;
		if(!visit(d, tmp, semicolon)) {
			err::set(stmt->line, stmt->col, "failed to generate C code for var decl");
			return false;
		}
	}
	return true;
}
bool CDriver::visit(parser::StmtCond *stmt, Writer &writer, const bool &semicolon)
{
	if(stmt->isInline()) {
		if(stmt->conds.empty()) return true;
		if(!visit(stmt->conds.back().blk, writer, false)) {
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
			if(!visit(c.cond, tmp, false)) {
				err::set(c.cond->line, c.cond->col,
					 "failed to generate C code for conditional");
				return false;
			}
			writer.append(tmp);
			writer.write(") ");
		}
		if(!visit(c.blk, writer, false)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for conditional block");
			return false;
		}
	}
	return true;
}
bool CDriver::visit(parser::StmtForIn *stmt, Writer &writer, const bool &semicolon)
{
	return false;
}
bool CDriver::visit(parser::StmtFor *stmt, Writer &writer, const bool &semicolon)
{
	if(stmt->isInline()) {
		if(stmt->blk->stmts.empty()) return true;
		Writer tmp;
		if(!visit(stmt->blk, tmp, false)) {
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
		if(!visit(stmt->init, tmp, false)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for for-loop init");
			return false;
		}
		writer.append(tmp);
	}
	writer.write(";");
	if(stmt->cond) {
		Writer tmp;
		if(!visit(stmt->cond, tmp, false)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for for-loop condition");
			return false;
		}
		writer.append(tmp);
	}
	writer.write(";");
	if(stmt->incr) {
		Writer tmp;
		if(!visit(stmt->incr, tmp, false)) {
			err::set(stmt->line, stmt->col,
				 "failed to generate C code for for-loop incr");
			return false;
		}
		writer.append(tmp);
	}
	writer.write(") ");
	Writer tmp;
	if(!visit(stmt->blk, tmp, false)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for for-loop block");
		return false;
	}
	writer.append(tmp);
	return true;
}
bool CDriver::visit(parser::StmtWhile *stmt, Writer &writer, const bool &semicolon)
{
	writer.clear();
	writer.write("while(");
	Writer tmp;
	if(!visit(stmt->cond, tmp, false)) {
		err::set(stmt->line, stmt->col,
			 "failed to generate C code for while-loop condition");
		return false;
	}
	writer.append(tmp);
	writer.write(") ");
	tmp.clear();
	if(!visit(stmt->blk, tmp, false)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for while block");
		return false;
	}
	writer.append(tmp);
	return true;
}
bool CDriver::visit(parser::StmtRet *stmt, Writer &writer, const bool &semicolon)
{
	if(!stmt->val) {
		writer.write("return");
		return true;
	}
	Writer tmp;
	if(!visit(stmt->val, tmp, false)) {
		err::set(stmt->line, stmt->col, "failed to generate C code for return value");
		return false;
	}
	writer.write("return ");
	writer.append(tmp);
	if(semicolon) writer.write(";");
	return true;
}
bool CDriver::visit(parser::StmtContinue *stmt, Writer &writer, const bool &semicolon)
{
	writer.write("continue");
	if(semicolon) writer.write(";");
	return true;
}
bool CDriver::visit(parser::StmtBreak *stmt, Writer &writer, const bool &semicolon)
{
	writer.write("break");
	if(semicolon) writer.write(";");
	return true;
}

static bool AcceptsSemicolon(parser::Stmt *stmt)
{
	switch(stmt->stmt_type) {
	case parser::BLOCK: return false;
	case parser::TYPE: return false;
	case parser::SIMPLE: return true;
	case parser::EXPR: return true;
	case parser::FNCALLINFO: return false;
	case parser::VAR: return true;
	case parser::FNSIG: return false;
	case parser::FNDEF: return false;
	case parser::HEADER: return false;
	case parser::LIB: return false;
	case parser::EXTERN: return false;
	case parser::ENUMDEF: return false;
	case parser::STRUCTDEF: return false;
	case parser::VARDECL: return false;
	case parser::COND: return false;
	case parser::FORIN: return false;
	case parser::FOR: return false;
	case parser::WHILE: return false;
	case parser::RET: return true;
	case parser::CONTINUE: return true;
	case parser::BREAK: return true;
	}
	return false;
}

bool TrySetMainFunction(parser::StmtVar *var, const std::string &varname, Writer &writer)
{
	parser::StmtFnDef *fn = parser::as<parser::StmtFnDef>(var->val);
	if(!startswith(var->name.data.s, "main_0")) return false;
	parser::Type *retbase = fn->sig->rettype->type;
	if(!retbase || retbase->type != parser::TSIMPLE) return false;
	parser::TypeSimple *ret = parser::as<parser::TypeSimple>(retbase);
	if(ret->name != "i32" || ret->ptr > 0) return false;
	// false => 0 args
	// true => 2 args
	bool zero_or_two = false;
	if(fn->sig->args.empty()) { // int main()
		return true;
	} else if(fn->sig->args.size() == 2) { // int main(int argc, char **argv)
		parser::Type *a1base = fn->sig->args[0]->type;
		parser::Type *a2base = fn->sig->args[1]->type;
		if(a1base->type != parser::TSIMPLE || a2base->type != parser::TSIMPLE) return false;
		parser::TypeSimple *a1 = parser::as<parser::TypeSimple>(a1base);
		parser::TypeSimple *a2 = parser::as<parser::TypeSimple>(a2base);
		if(a1->name != "i32" || a1->ptr != 0) return false;
		if(a2->name != "i8" || a2->ptr != 2) return false;
		return true;
	}
	return false;
}
} // namespace codegen
} // namespace sc