/*
	MIT License

	Copyright (c) 2021 Scribe Language Repositories

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"), to
	deal in the Software without restriction, including without limitation the
	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#include "parser/Stmts.hpp"

#include "parser/Type.hpp"
#include "parser/ValueMgr.hpp"
#include "TreeIO.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// Stmt //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt::Stmt(const Stmts &stmt_type, Module *mod, const size_t &line, const size_t &col)
	: stmt_type(stmt_type), parent(nullptr), mod(mod), line(line), col(col),
	  is_specialized(false), is_comptime(false), type(nullptr), value(nullptr)
{}
Stmt::~Stmt()
{
	if(type) delete type;
}

Stmt *Stmt::copy(const bool &copy_type, const bool &copy_val)
{
	Stmt *cp = hiddenCopy(copy_type, copy_val, this);
	if(!cp) return nullptr;
	return cp;
}
Stmt *Stmt::getParentWithType(const Stmts &typ)
{
	Stmt *res = this;
	while(res && res->stmt_type != typ) {
		res = res->parent;
	}
	return res;
}
void Stmt::setSpecialized(const bool &specialized)
{
	is_specialized = specialized;
}
bool Stmt::isSpecialized()
{
	return is_specialized;
}
void Stmt::setComptime(const bool &comptime)
{
	is_comptime = comptime;
}
bool Stmt::isComptime()
{
	return is_comptime;
}
void Stmt::updateValue(ValueMgr &values, Value *newvalue)
{
	if(!value) {
		value = newvalue;
		return;
	}
	values.updateValue(value, newvalue);
}
std::string Stmt::typeString()
{
	std::string res;
	if(type) res += " :: " + type->str();
	if(value) res += " -> " + value->stringify();
	return res;
}

std::string Stmt::stmtTypeString()
{
	switch(stmt_type) {
	case BLOCK: return "block";
	case TYPE: return "type";
	case SIMPLE: return "simple";
	case EXPR: return "expression";
	case FNCALLINFO: return "function call info";
	case VAR: return "variable declaration base";
	case FNSIG: return "function signature";
	case FNDEF: return "function definition";
	case HEADER: return "extern header";
	case LIB: return "extern library";
	case EXTERN: return "extern";
	case ENUMDEF: return "enumeration definition";
	case STRUCTDEF: return "structure definition";
	case VARDECL: return "variable declaration";
	case COND: return "conditional";
	case FORIN: return "for-in loop";
	case FOR: return "for loop";
	case WHILE: return "while loop";
	case RET: return "return";
	case CONTINUE: return "continue";
	case BREAK: return "break";
	}
	return "";
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtBlock::StmtBlock(Module *mod, const size_t &line, const size_t &col,
		     const std::vector<Stmt *> &stmts)
	: Stmt(BLOCK, mod, line, col), stmts(stmts)
{}
StmtBlock::~StmtBlock()
{
	for(auto &stmt : stmts) delete stmt;
}

void StmtBlock::StmtBlock::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Block:\n");
	for(size_t i = 0; i < stmts.size(); ++i) {
		stmts[i]->disp(i != stmts.size() - 1);
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtType::StmtType(Module *mod, const size_t &line, const size_t &col, const size_t &ptr,
		   const size_t &info, const std::vector<lex::Lexeme> &name,
		   const std::vector<lex::Lexeme> &templates)
	: Stmt(TYPE, mod, line, col), func(false), ptr(ptr), info(info), name(name),
	  templates(templates), fn(nullptr)
{}
StmtType::StmtType(Module *mod, const size_t &line, const size_t &col, Stmt *fn)
	: Stmt(TYPE, mod, line, col), func(true), ptr(0), info(0), name({}), fn(fn)
{}
StmtType::~StmtType()
{
	if(fn) delete fn;
}

void StmtType::disp(const bool &has_next)
{
	if(func) {
		tio::taba(has_next);
		tio::print(has_next, "Type: <Function>%s\n", typeString().c_str());
		fn->disp(false);
		tio::tabr();
		return;
	}
	std::string tname(ptr, '*');
	if(info & REF) tname += "&";
	if(info & STATIC) tname += "static ";
	if(info & CONST) tname += "const ";
	if(info & VOLATILE) tname += "volatile ";
	if(info & VARIADIC) tname = "..." + tname;
	for(auto &n : name) tname += n.data.s.empty() ? n.tok.cstr() : n.data.s;
	if(!templates.empty()) {
		tname += "<";
		for(auto &t : templates) {
			tname += t.data.s + ", ";
		}
		tname.pop_back();
		tname.pop_back();
		tname += ">";
	}
	tio::taba(has_next);
	tio::print(false, "Type: %s%s\n", tname.c_str(), typeString().c_str());
	tio::tabr();
}

std::string StmtType::getname()
{
	if(func) return fn->stmtTypeString();

	std::string tname(ptr, '*');
	if(info & REF) tname += "&";
	if(info & STATIC) tname += "static ";
	if(info & CONST) tname += "const ";
	if(info & VOLATILE) tname += "volatile ";
	if(info & VARIADIC) tname = "..." + tname;
	for(auto &n : name) tname += n.data.s.empty() ? n.tok.cstr() : n.data.s;
	if(templates.empty()) return tname;
	tname += "<";
	for(auto &t : templates) {
		tname += t.data.s;
	}
	tname += ">";
	return tname;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtSimple ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtSimple::StmtSimple(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &val)
	: Stmt(SIMPLE, mod, line, col), val(val)
{}

void StmtSimple::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Simple: %s%s\n", val.str(0).c_str(), typeString().c_str());
	tio::tabr();
}

StmtSimple::~StmtSimple() {}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtFnCallInfo::StmtFnCallInfo(Module *mod, const size_t &line, const size_t &col,
			       const std::vector<StmtType *> &templates,
			       const std::vector<Stmt *> &args)
	: Stmt(FNCALLINFO, mod, line, col), templates(templates), args(args)
{}
StmtFnCallInfo::~StmtFnCallInfo()
{
	for(auto &templ : templates) delete templ;
	for(auto &a : args) delete a;
}

void StmtFnCallInfo::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Function Call Info: %s\n",
		   templates.empty() && args.empty() ? "(empty)" : "");
	if(!templates.empty()) {
		tio::taba(!args.empty());
		tio::print(!args.empty(), "Template Types:\n");
		for(size_t i = 0; i < templates.size(); ++i) {
			templates[i]->disp(i != templates.size() - 1);
		}
		tio::tabr();
	}
	if(!args.empty()) {
		tio::taba(false);
		tio::print(false, "Args:\n");
		for(size_t i = 0; i < args.size(); ++i) {
			args[i]->disp(i != args.size() - 1);
		}
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtExpr::StmtExpr(Module *mod, const size_t &line, const size_t &col, Stmt *lhs,
		   const lex::Lexeme &oper, Stmt *rhs)
	: Stmt(EXPR, mod, line, col), commas(0), lhs(lhs), oper(oper), rhs(rhs), or_blk(nullptr),
	  or_blk_var(), is_parse_intrinsic(false), intrin_fn(nullptr)
{}
StmtExpr::~StmtExpr()
{
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	if(or_blk) delete or_blk;
}

void StmtExpr::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Expression [parsing intinsic: %s]:%s\n",
		   is_parse_intrinsic ? "yes" : "no", typeString().c_str());
	if(lhs) {
		tio::taba(oper.tok.isValid() || rhs || or_blk);
		tio::print(oper.tok.isValid() || rhs || or_blk, "LHS:\n");
		lhs->disp(false);
		tio::tabr();
	}
	if(oper.tok.isValid()) {
		tio::taba(rhs || or_blk);
		tio::print(rhs || or_blk, "Oper: %s\n", oper.tok.cstr());
		tio::tabr();
	}
	if(rhs) {
		tio::taba(or_blk);
		tio::print(or_blk, "RHS:\n");
		rhs->disp(false);
		tio::tabr();
	}
	if(or_blk) {
		tio::taba(false);
		tio::print(false, "Or: %s\n",
			   or_blk_var.tok.isData() ? or_blk_var.data.s.c_str() : "<none>");
		or_blk->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

void StmtExpr::setIntrinsic(intrinsic_fn_t intrin)
{
	intrin_fn = intrin;
}
bool StmtExpr::hasIntrinsic()
{
	return intrin_fn != nullptr;
}
bool StmtExpr::callIntrinsic(TypeMgr &types, ValueMgr &values, StmtExpr *base,
			     const std::vector<StmtType *> &templates,
			     const std::vector<Stmt *> &args)
{
	if(!intrin_fn) return false;
	return intrin_fn(types, values, base, templates, args);
}

void StmtExpr::setParseIntrinsic(const bool &pi)
{
	is_parse_intrinsic = pi;
}
bool StmtExpr::isParseIntrinsic()
{
	return is_parse_intrinsic;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtVar::StmtVar(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &name,
		 StmtType *vtype, Stmt *val)
	: Stmt(VAR, mod, line, col), name(name), vtype(vtype), val(val)
{}
StmtVar::~StmtVar()
{
	if(vtype) delete vtype;
	if(val) delete val;
}

void StmtVar::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Variable: %s%s\n", name.data.s.c_str(), typeString().c_str());
	if(vtype) {
		tio::taba(val);
		tio::print(val, "Type:\n");
		vtype->disp(false);
		tio::tabr();
	}
	if(val) {
		tio::taba(false);
		tio::print(false, "Value:\n");
		val->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtFnSig::StmtFnSig(Module *mod, const size_t &line, const size_t &col,
		     const std::vector<lex::Lexeme> &templates, std::vector<StmtVar *> &args,
		     StmtType *rettype, const bool &has_variadic)
	: Stmt(FNSIG, mod, line, col), templates(templates), args(args), rettype(rettype),
	  has_variadic(has_variadic), is_member(false)
{}
StmtFnSig::~StmtFnSig()
{
	for(auto &p : args) delete p;
	if(rettype) delete rettype;
}

void StmtFnSig::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Function signature [variadic = %s; member = %s]%s\n",
		   has_variadic ? "yes" : "no", is_member ? "yes" : "no", typeString().c_str());
	if(!templates.empty()) {
		tio::taba(args.size() > 0 || rettype);
		tio::print(args.size() > 0 || rettype, "Templates:\n");
		for(size_t i = 0; i < templates.size(); ++i) {
			tio::taba(i != templates.size() - 1);
			tio::print(i != templates.size() - 1, "%s\n", templates[i].data.s.c_str());
			tio::tabr();
		}
		tio::tabr();
	}
	if(args.size() > 0) {
		tio::taba(rettype);
		tio::print(rettype, "Parameters:\n");
		for(size_t i = 0; i < args.size(); ++i) {
			args[i]->disp(i != args.size() - 1);
		}
		tio::tabr();
	}
	if(rettype) {
		tio::taba(false);
		tio::print(false, "Return Type:\n");
		rettype->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

void StmtFnSig::setMember(const bool &is_mem)
{
	is_member = is_mem;
}
bool StmtFnSig::isMember()
{
	return is_member;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtFnDef::StmtFnDef(Module *mod, const size_t &line, const size_t &col, StmtFnSig *sig,
		     StmtBlock *blk)
	: Stmt(FNDEF, mod, line, col), sig(sig), blk(blk)
{}
StmtFnDef::~StmtFnDef()
{
	if(sig) delete sig;
	if(blk) delete blk;
}

void StmtFnDef::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Function definition%s\n", typeString().c_str());
	tio::taba(true);
	tio::print(true, "Function Signature:\n");
	sig->disp(false);
	tio::tabr();

	tio::taba(false);
	tio::print(false, "Function Block:\n");
	blk->disp(false);
	tio::tabr(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtHeader ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtHeader::StmtHeader(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &names,
		       const lex::Lexeme &flags)
	: Stmt(HEADER, mod, line, col), names(names), flags(flags)
{}

void StmtHeader::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Header\n");
	tio::taba(!flags.data.s.empty());
	tio::print(!flags.data.s.empty(), "Names: %s\n", names.data.s.c_str());
	tio::tabr();

	if(!flags.data.s.empty()) {
		tio::taba(false);
		tio::print(false, "Flags: %s\n", flags.data.s.c_str());
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtLib //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtLib::StmtLib(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &flags)
	: Stmt(LIB, mod, line, col), flags(flags)
{}

void StmtLib::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Libs\n");
	tio::taba(false);
	tio::print(false, "Flags: %s\n", flags.data.s.c_str());
	tio::tabr(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtExtern ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtExtern::StmtExtern(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &fname,
		       StmtHeader *headers, StmtLib *libs, StmtFnSig *sig)
	: Stmt(EXTERN, mod, line, col), fname(fname), headers(headers), libs(libs), sig(sig)
{}
StmtExtern::~StmtExtern()
{
	if(headers) delete headers;
	if(libs) delete libs;
	if(sig) delete sig;
}

void StmtExtern::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Extern for %s%s\n", fname.data.s.c_str(), typeString().c_str());
	if(headers) {
		tio::taba(libs || sig);
		tio::print(libs || sig, "Headers:\n");
		headers->disp(false);
		tio::tabr();
	}
	if(libs) {
		tio::taba(sig);
		tio::print(sig, "Libs:\n");
		libs->disp(false);
		tio::tabr();
	}

	if(sig) {
		tio::taba(false);
		tio::print(false, "Funtion Signature:\n");
		sig->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtEnum ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtEnum::StmtEnum(Module *mod, const size_t &line, const size_t &col,
		   const std::vector<lex::Lexeme> &items)
	: Stmt(ENUMDEF, mod, line, col), items(items)
{}
StmtEnum::~StmtEnum() {}

void StmtEnum::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Enumerations:%s\n", typeString().c_str());
	for(size_t i = 0; i < items.size(); ++i) {
		tio::taba(i != items.size() - 1);
		tio::print(i != items.size() - 1, "%s\n", items[i].str(0).c_str());
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtStruct //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtStruct::StmtStruct(Module *mod, const size_t &line, const size_t &col, const bool &decl,
		       const std::vector<lex::Lexeme> &templates,
		       const std::vector<StmtVar *> &fields)
	: Stmt(STRUCTDEF, mod, line, col), decl(decl), templates(templates), fields(fields)
{}
StmtStruct::~StmtStruct()
{
	for(auto &field : fields) delete field;
}

void StmtStruct::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Struct [declaration = %s]%s\n", decl ? "yes" : "no",
		   typeString().c_str());

	if(!templates.empty()) {
		tio::taba(!fields.empty());
		tio::print(!fields.empty(), "Templates:\n");
		for(size_t i = 0; i < templates.size(); ++i) {
			tio::taba(i != templates.size() - 1);
			tio::print(i != templates.size() - 1, "%s\n", templates[i].str(0).c_str());
			tio::tabr();
		}
		tio::tabr();
	}

	if(!fields.empty()) {
		tio::taba(false);
		tio::print(false, "Fields:\n");
		for(size_t i = 0; i < fields.size(); ++i) {
			fields[i]->disp(i != fields.size() - 1);
		}
		tio::tabr();
	}

	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtVarDecl ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtVarDecl::StmtVarDecl(Module *mod, const size_t &line, const size_t &col,
			 const std::vector<StmtVar *> &decls)
	: Stmt(VARDECL, mod, line, col), decls(decls)
{}
StmtVarDecl::~StmtVarDecl()
{
	for(auto &decl : decls) delete decl;
}

void StmtVarDecl::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Variable declarations\n");
	for(size_t i = 0; i < decls.size(); ++i) {
		decls[i]->disp(i != decls.size() - 1);
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtCond::StmtCond(Module *mod, const size_t &line, const size_t &col,
		   const std::vector<cond_t> &conds)
	: Stmt(COND, mod, line, col), conds(conds)
{}
StmtCond::~StmtCond()
{
	for(auto &c : conds) {
		if(c.cond) delete c.cond;
		if(c.blk) delete c.blk;
	}
}

void StmtCond::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Conditional\n");
	for(size_t i = 0; i < conds.size(); ++i) {
		tio::taba(i != conds.size() - 1);
		tio::print(i != conds.size() - 1, "Branch:\n");
		if(conds[i].cond) {
			tio::taba(true);
			tio::print(true, "Condition:\n");
			conds[i].cond->disp(false);
			tio::tabr();
		}
		tio::taba(false);
		tio::print(false, "Block:\n");
		conds[i].blk->disp(false);
		tio::tabr(2);
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtForIn //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtForIn::StmtForIn(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &iter,
		     Stmt *in, StmtBlock *blk)
	: Stmt(FORIN, mod, line, col), iter(iter), in(in), blk(blk)
{}
StmtForIn::~StmtForIn()
{
	if(in) delete in;
	if(blk) delete blk;
}

void StmtForIn::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "For-in loop with iterator: %s:\n", iter.data.s.c_str());
	tio::taba(true);
	tio::print(true, "In:\n");
	in->disp(false);
	tio::tabr();
	tio::taba(false);
	tio::print(false, "Block:\n");
	blk->disp(false);
	tio::tabr(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtFor::StmtFor(Module *mod, const size_t &line, const size_t &col, Stmt *init, Stmt *cond,
		 Stmt *incr, StmtBlock *blk)
	: Stmt(FOR, mod, line, col), init(init), cond(cond), incr(incr), blk(blk), is_inline(false)
{}
StmtFor::~StmtFor()
{
	if(init) delete init;
	if(cond) delete cond;
	if(incr) delete incr;
	if(blk) delete blk;
}

void StmtFor::setInline(const bool &_inline)
{
	is_inline = _inline;
}
bool StmtFor::isInline()
{
	return is_inline;
}

void StmtFor::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "For\n");
	if(init) {
		tio::taba(cond || incr || blk);
		tio::print(cond || incr || blk, "Init:\n");
		init->disp(false);
		tio::tabr();
	}
	if(cond) {
		tio::taba(incr || blk);
		tio::print(incr || blk, "Condition:\n");
		cond->disp(false);
		tio::tabr();
	}
	if(incr) {
		tio::taba(blk);
		tio::print(blk, "Increment:\n");
		incr->disp(false);
		tio::tabr();
	}
	if(blk) {
		tio::taba(false);
		tio::print(false, "Block:\n");
		blk->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtWhile::StmtWhile(Module *mod, const size_t &line, const size_t &col, Stmt *cond, StmtBlock *blk)
	: Stmt(WHILE, mod, line, col), cond(cond), blk(blk)
{}
StmtWhile::~StmtWhile()
{
	if(cond) delete cond;
	if(blk) delete blk;
}

void StmtWhile::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "While\n");
	tio::taba(true);
	tio::print(true, "Condition:\n");
	cond->disp(true);
	tio::tabr();
	tio::taba(false);
	tio::print(false, "Block:\n");
	blk->disp(false);
	tio::tabr(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtRet::StmtRet(Module *mod, const size_t &line, const size_t &col, Stmt *val)
	: Stmt(RET, mod, line, col), val(val)
{}
StmtRet::~StmtRet()
{
	if(val) delete val;
}

void StmtRet::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Return%s\n", typeString().c_str());
	if(val) {
		tio::taba(false);
		tio::print(false, "Value:\n");
		val->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtContinue
////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtContinue::StmtContinue(Module *mod, const size_t &line, const size_t &col)
	: Stmt(CONTINUE, mod, line, col)
{}

void StmtContinue::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Continue\n");
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

StmtBreak::StmtBreak(Module *mod, const size_t &line, const size_t &col)
	: Stmt(BREAK, mod, line, col)
{}

void StmtBreak::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Break\n");
	tio::tabr();
}
} // namespace parser
} // namespace sc