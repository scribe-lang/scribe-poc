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
#include "TreeIO.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_base_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t::stmt_base_t(const StmtType &type, const size_t &src_id, const size_t &line,
			 const size_t &col)
	: type(type), parent(nullptr), src_id(src_id), line(line), col(col), vtyp(nullptr),
	  is_specialized(false), is_intrin(false)
{}
stmt_base_t::~stmt_base_t()
{
	if(vtyp) delete vtyp;
}

stmt_base_t *stmt_base_t::copy(const bool &copy_vtyp)
{
	stmt_base_t *cp = hidden_copy(copy_vtyp, this);
	if(!cp) return nullptr;
	cp->set_parent(cp->parent); // no change for top level parent
	return cp;
}

stmt_base_t *stmt_base_t::get_parent_with_type(const StmtType &typ)
{
	stmt_base_t *res = this->parent;
	while(res && res->type != typ) {
		res = res->parent;
	}
	return res;
}

std::string stmt_base_t::typestr()
{
	switch(type) {
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
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_block_t::stmt_block_t(const size_t &src_id, const size_t &line, const size_t &col,
			   const std::vector<stmt_base_t *> &stmts)
	: stmt_base_t(BLOCK, src_id, line, col), stmts(stmts)
{}
stmt_block_t::~stmt_block_t()
{
	for(auto &stmt : stmts) delete stmt;
}

void stmt_block_t::stmt_block_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Block:\n");
	for(size_t i = 0; i < stmts.size(); ++i) {
		stmts[i]->disp(i != stmts.size() - 1);
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_type_t::stmt_type_t(const size_t &src_id, const size_t &line, const size_t &col,
			 const size_t &ptr, const size_t &info,
			 const std::vector<lex::Lexeme> &name,
			 const std::vector<lex::Lexeme> &templates)
	: stmt_base_t(TYPE, src_id, line, col), func(false), ptr(ptr), info(info), name(name),
	  templates(templates), fn(nullptr)
{}
stmt_type_t::stmt_type_t(const size_t &src_id, const size_t &line, const size_t &col,
			 stmt_base_t *fn)
	: stmt_base_t(TYPE, src_id, line, col), func(true), ptr(0), info(0), name({}), fn(fn)
{}
stmt_type_t::~stmt_type_t()
{
	if(fn) delete fn;
}

void stmt_type_t::disp(const bool &has_next)
{
	if(func) {
		tio::taba(has_next);
		tio::print(has_next, "Type: <Function>%s\n",
			   vtyp ? (" -> " + vtyp->str()).c_str() : "");
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
	tio::print(false, "Type: %s%s\n", tname.c_str(),
		   vtyp ? (" -> " + vtyp->str()).c_str() : "");
	tio::tabr();
}

std::string stmt_type_t::getname()
{
	if(func) return fn->typestr();

	std::string tname(ptr, '*');
	if(info & REF) tname += "&";
	if(info & STATIC) tname += "static ";
	if(info & CONST) tname += "const ";
	if(info & VOLATILE) tname += "volatile ";
	if(info & VARIADIC) tname = "..." + tname;
	for(auto &n : name) tname += n.data.s.empty() ? n.tok.cstr() : n.data.s;
	return tname;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_simple_t::stmt_simple_t(const size_t &src_id, const size_t &line, const size_t &col,
			     const lex::Lexeme &val)
	: stmt_base_t(SIMPLE, src_id, line, col), val(val)
{}

void stmt_simple_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Simple: %s%s\n", val.str(0).c_str(),
		   vtyp ? (" -> " + vtyp->str()).c_str() : "");
	tio::tabr();
}

stmt_simple_t::~stmt_simple_t() {}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// stmt_fncallinfo_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_fncallinfo_t::stmt_fncallinfo_t(const size_t &src_id, const size_t &line, const size_t &col,
				     const std::vector<stmt_type_t *> &templates,
				     const std::vector<stmt_base_t *> &args)
	: stmt_base_t(FNCALLINFO, src_id, line, col), templates(templates), args(args)
{}
stmt_fncallinfo_t::~stmt_fncallinfo_t()
{
	for(auto &templ : templates) delete templ;
	for(auto &a : args) delete a;
}

void stmt_fncallinfo_t::disp(const bool &has_next)
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
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_expr_t::stmt_expr_t(const size_t &src_id, const size_t &line, const size_t &col,
			 stmt_base_t *lhs, const lex::Lexeme &oper, stmt_base_t *rhs)
	: stmt_base_t(EXPR, src_id, line, col), commas(0), lhs(lhs), oper(oper), rhs(rhs),
	  or_blk(nullptr), or_blk_var()
{}
stmt_expr_t::~stmt_expr_t()
{
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	if(or_blk) delete or_blk;
}

void stmt_expr_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Expression [intrinsic = %s]:%s\n", is_intrin ? "yes" : "no",
		   vtyp ? (" -> " + vtyp->str()).c_str() : "");
	if(lhs) {
		tio::taba(oper.tok.is_valid() || rhs || or_blk);
		tio::print(oper.tok.is_valid() || rhs || or_blk, "LHS:\n");
		lhs->disp(false);
		tio::tabr();
	}
	if(oper.tok.is_valid()) {
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
			   or_blk_var.tok.is_data() ? or_blk_var.data.s.c_str() : "<none>");
		or_blk->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_var_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_var_t::stmt_var_t(const size_t &src_id, const size_t &line, const size_t &col,
		       const lex::Lexeme &name, stmt_type_t *vtype, stmt_base_t *val)
	: stmt_base_t(VAR, src_id, line, col), name(name), vtype(vtype), val(val)
{}
stmt_var_t::~stmt_var_t()
{
	if(vtype) delete vtype;
	if(val) delete val;
}

void stmt_var_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Variable: %s%s\n", name.data.s.c_str(),
		   vtyp ? (" -> " + vtyp->str()).c_str() : "");
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
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_fnsig_t::stmt_fnsig_t(const size_t &src_id, const size_t &line, const size_t &col,
			   const std::vector<lex::Lexeme> &templates,
			   std::vector<stmt_var_t *> &params, stmt_type_t *rettype,
			   const bool &comptime)
	: stmt_base_t(FNSIG, src_id, line, col), templates(templates), params(params),
	  rettype(rettype), comptime(comptime)
{}
stmt_fnsig_t::~stmt_fnsig_t()
{
	for(auto &p : params) delete p;
	if(rettype) delete rettype;
}

void stmt_fnsig_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Function signature [comptime = %s]%s\n", comptime ? "yes" : "no",
		   vtyp ? (" -> " + vtyp->str()).c_str() : "");
	if(!templates.empty()) {
		tio::taba(params.size() > 0 || rettype);
		tio::print(params.size() > 0 || rettype, "Templates:\n");
		for(size_t i = 0; i < templates.size(); ++i) {
			tio::taba(i != templates.size() - 1);
			tio::print(i != templates.size() - 1, "%s\n", templates[i].data.s.c_str());
			tio::tabr();
		}
		tio::tabr();
	}
	if(params.size() > 0) {
		tio::taba(rettype);
		tio::print(rettype, "Parameters:\n");
		for(size_t i = 0; i < params.size(); ++i) {
			params[i]->disp(i != params.size() - 1);
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_fndef_t::stmt_fndef_t(const size_t &src_id, const size_t &line, const size_t &col,
			   stmt_fnsig_t *sig, stmt_block_t *blk)
	: stmt_base_t(FNDEF, src_id, line, col), sig(sig), blk(blk)
{}
stmt_fndef_t::~stmt_fndef_t()
{
	if(sig) delete sig;
	if(blk) delete blk;
}

void stmt_fndef_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Function definition%s\n", vtyp ? (" -> " + vtyp->str()).c_str() : "");
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
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_header_t::stmt_header_t(const size_t &src_id, const size_t &line, const size_t &col,
			     const lex::Lexeme &names, const lex::Lexeme &flags)
	: stmt_base_t(HEADER, src_id, line, col), names(names), flags(flags)
{}

void stmt_header_t::disp(const bool &has_next)
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
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_lib_t::stmt_lib_t(const size_t &src_id, const size_t &line, const size_t &col,
		       const lex::Lexeme &flags)
	: stmt_base_t(LIB, src_id, line, col), flags(flags)
{}

void stmt_lib_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Libs\n");
	tio::taba(false);
	tio::print(false, "Flags: %s\n", flags.data.s.c_str());
	tio::tabr(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_extern_t::stmt_extern_t(const size_t &src_id, const size_t &line, const size_t &col,
			     const lex::Lexeme &fname, stmt_header_t *headers, stmt_lib_t *libs,
			     stmt_fnsig_t *sig)
	: stmt_base_t(EXTERN, src_id, line, col), fname(fname), headers(headers), libs(libs),
	  sig(sig)
{}
stmt_extern_t::~stmt_extern_t()
{
	if(headers) delete headers;
	if(libs) delete libs;
	if(sig) delete sig;
}

void stmt_extern_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Extern for %s%s\n", fname.data.s.c_str(),
		   vtyp ? (" -> " + vtyp->str()).c_str() : "");
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
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_enumdef_t::stmt_enumdef_t(const size_t &src_id, const size_t &line, const size_t &col,
			       const std::vector<stmt_var_t *> &items)
	: stmt_base_t(ENUMDEF, src_id, line, col), items(items)
{}
stmt_enumdef_t::~stmt_enumdef_t()
{
	for(auto &item : items) delete item;
}

void stmt_enumdef_t::disp(const bool &has_next) {}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_struct_t::stmt_struct_t(const size_t &src_id, const size_t &line, const size_t &col,
			     const bool &decl, const std::vector<lex::Lexeme> &templates,
			     const std::vector<stmt_var_t *> &fields)
	: stmt_base_t(STRUCTDEF, src_id, line, col), decl(decl), templates(templates),
	  fields(fields)
{}
stmt_struct_t::~stmt_struct_t()
{
	for(auto &field : fields) delete field;
}

void stmt_struct_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "struct [declaration = %s]%s\n", decl ? "yes" : "no",
		   vtyp ? (" -> " + vtyp->str()).c_str() : "");

	if(!templates.empty()) {
		tio::taba(!fields.empty());
		tio::print(!fields.empty(), "Templates:\n");
		for(size_t i = 0; i < templates.size(); ++i) {
			tio::taba(i != templates.size() - 1);
			tio::print(false, "%s\n", templates[i].str(0).c_str());
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
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_vardecl_t::stmt_vardecl_t(const size_t &src_id, const size_t &line, const size_t &col,
			       const std::vector<stmt_var_t *> &decls)
	: stmt_base_t(VARDECL, src_id, line, col), decls(decls)
{}
stmt_vardecl_t::~stmt_vardecl_t()
{
	for(auto &decl : decls) delete decl;
}

void stmt_vardecl_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Variable declarations\n");
	for(size_t i = 0; i < decls.size(); ++i) {
		decls[i]->disp(i != decls.size() - 1);
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_cond_t::stmt_cond_t(const size_t &src_id, const size_t &line, const size_t &col,
			 const std::vector<cond_t> &conds)
	: stmt_base_t(COND, src_id, line, col), conds(conds)
{}
stmt_cond_t::~stmt_cond_t()
{
	for(auto &c : conds) {
		if(c.cond) delete c.cond;
		if(c.blk) delete c.blk;
	}
}

void stmt_cond_t::disp(const bool &has_next)
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
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_forin_t::stmt_forin_t(const size_t &src_id, const size_t &line, const size_t &col,
			   const lex::Lexeme &iter, stmt_base_t *in, stmt_block_t *blk)
	: stmt_base_t(FORIN, src_id, line, col), iter(iter), in(in), blk(blk)
{}
stmt_forin_t::~stmt_forin_t()
{
	if(in) delete in;
	if(blk) delete blk;
}

void stmt_forin_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "For in with iterator %s", iter.data.s.c_str());
	tio::taba(true);
	tio::print(true, "In:\n");
	in->disp(true);
	tio::tabr();
	tio::taba(false);
	tio::print(false, "Block:\n");
	blk->disp(false);
	tio::tabr(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_for_t::stmt_for_t(const size_t &src_id, const size_t &line, const size_t &col,
		       stmt_base_t *init, stmt_base_t *cond, stmt_base_t *incr, stmt_block_t *blk)
	: stmt_base_t(FOR, src_id, line, col), init(init), cond(cond), incr(incr), blk(blk)
{}
stmt_for_t::~stmt_for_t()
{
	if(init) delete init;
	if(cond) delete cond;
	if(incr) delete incr;
	if(blk) delete blk;
}

void stmt_for_t::disp(const bool &has_next)
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
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_while_t::stmt_while_t(const size_t &src_id, const size_t &line, const size_t &col,
			   stmt_base_t *cond, stmt_block_t *blk)
	: stmt_base_t(WHILE, src_id, line, col), cond(cond), blk(blk)
{}
stmt_while_t::~stmt_while_t()
{
	if(cond) delete cond;
	if(blk) delete blk;
}

void stmt_while_t::disp(const bool &has_next)
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
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_ret_t::stmt_ret_t(const size_t &src_id, const size_t &line, const size_t &col,
		       stmt_base_t *val)
	: stmt_base_t(RET, src_id, line, col), val(val)
{}
stmt_ret_t::~stmt_ret_t()
{
	if(val) delete val;
}

void stmt_ret_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Return%s\n", vtyp ? (" -> " + vtyp->str()).c_str() : "");
	if(val) {
		tio::taba(false);
		tio::print(false, "Value:\n");
		val->disp(false);
		tio::tabr();
	}
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_cont_t::stmt_cont_t(const size_t &src_id, const size_t &line, const size_t &col)
	: stmt_base_t(CONTINUE, src_id, line, col)
{}

void stmt_cont_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Continue\n");
	tio::tabr();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_break_t::stmt_break_t(const size_t &src_id, const size_t &line, const size_t &col)
	: stmt_base_t(BREAK, src_id, line, col)
{}

void stmt_break_t::disp(const bool &has_next)
{
	tio::taba(has_next);
	tio::print(has_next, "Break\n");
	tio::tabr();
}
} // namespace parser
} // namespace sc