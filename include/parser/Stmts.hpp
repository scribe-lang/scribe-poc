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

#ifndef PARSER_STMTS_HPP
#define PARSER_STMTS_HPP

#include "Lex.hpp"

namespace sc
{
namespace parser
{
enum StmtType
{
	BLOCK,
	TYPE,
	SIMPLE,
	EXPR,
	FNCALL,
	VAR, // Var and (Type or Val) (<var> : <type> = <value>)
	FNPARAMS,
	FNSIG, // function signature
	FNDEF,
	HEADER, // header format for extern
	LIB,	// lib format for extern
	EXTERN,
	ENUMDEF,
	STRUCTDEF,
	VARDECL,
	COND,
	FORIN,
	FOR,
	WHILE,
	RET,
	CONTINUE,
	BREAK,
};

struct Type
{
	size_t ptr;  // number of ptrs
	size_t info; // all from parser::TypeInfoMask
	std::string name;
};

struct stmt_base_t
{
	StmtType type;
	size_t line;
	size_t col;
	stmt_base_t(const StmtType &type, const size_t &line, const size_t &col);
	virtual ~stmt_base_t();
	virtual void disp(const bool &has_next) = 0;

	std::string typestr();

	// virtual bool check_type(Type &t, Type *expect = nullptr) = 0;
};

template<typename T> T *as(stmt_base_t *data)
{
	return static_cast<T *>(data);
}

enum TypeInfoMask
{
	REF	 = 1 << 0, // is a reference
	STATIC	 = 1 << 1, // is static
	CONST	 = 1 << 2, // is const
	VOLATILE = 1 << 3, // is volatile
	VARIADIC = 1 << 4, // is variadic
};

struct stmt_type_t : public stmt_base_t
{
	bool func;
	size_t ptr;  // number of ptrs
	size_t info; // all from TypeInfoMask
	std::vector<lex::Lexeme> name;
	std::vector<lex::Lexeme> templates;
	stmt_base_t *fn;
	std::vector<stmt_base_t *> counts; // array counts (expr or int)
	bool is_extern;
	stmt_type_t(const size_t &line, const size_t &col, const size_t &ptr, const size_t &info,
		    const std::vector<lex::Lexeme> &name, const std::vector<lex::Lexeme> &templates,
		    const std::vector<stmt_base_t *> &counts);
	stmt_type_t(const size_t &line, const size_t &col, stmt_base_t *fn);
	~stmt_type_t();

	void disp(const bool &has_next);

	std::string getname();

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_block_t : public stmt_base_t
{
	std::vector<stmt_base_t *> stmts;
	stmt_block_t(const size_t &line, const size_t &col,
		     const std::vector<stmt_base_t *> &stmts);
	~stmt_block_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_simple_t : public stmt_base_t
{
	lex::Lexeme val;
	stmt_simple_t(const size_t &line, const size_t &col, const lex::Lexeme &val);

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_expr_t : public stmt_base_t
{
	size_t commas;
	stmt_base_t *lhs;
	lex::Lexeme oper;
	stmt_base_t *rhs;
	stmt_block_t *or_blk;
	lex::Lexeme or_blk_var;
	// or_blk and or_blk_var can be set separately - nullptr/INVALID by default
	stmt_expr_t(const size_t &line, const size_t &col, stmt_base_t *lhs,
		    const lex::Lexeme &oper, stmt_base_t *rhs);
	~stmt_expr_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_fncall_t : public stmt_base_t
{
	lex::Lexeme name;
	std::vector<stmt_type_t *> templates;
	stmt_base_t *args;
	bool comptime;
	bool mem;
	bool subscr;
	stmt_fncall_t(const size_t &line, const size_t &col, const lex::Lexeme &name,
		      const std::vector<stmt_type_t *> &templates, stmt_base_t *args,
		      const bool &comptime, const bool &mem, const bool &subscr);
	~stmt_fncall_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_var_t : public stmt_base_t
{
	lex::Lexeme name;
	stmt_type_t *vtype;
	stmt_type_t *in;
	stmt_base_t *val; // either of expr, funcdef, enumdef, or structdef
	// at least one of type or val must be present
	stmt_var_t(const size_t &line, const size_t &col, const lex::Lexeme &name,
		   stmt_type_t *vtype, stmt_type_t *in, stmt_base_t *val);
	~stmt_var_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_fndecl_params_t : public stmt_base_t
{
	std::vector<stmt_var_t *> params;
	// stmt_var_t contains only type here, no val
	stmt_fndecl_params_t(const size_t &line, const size_t &col,
			     const std::vector<stmt_var_t *> &params);
	~stmt_fndecl_params_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_fnsig_t : public stmt_base_t
{
	std::vector<lex::Lexeme> templates;
	stmt_fndecl_params_t *params;
	stmt_type_t *rettype;
	bool comptime;
	stmt_fnsig_t(const size_t &line, const size_t &col,
		     const std::vector<lex::Lexeme> &templates, stmt_fndecl_params_t *params,
		     stmt_type_t *rettype, const bool &comptime);
	~stmt_fnsig_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_fndef_t : public stmt_base_t
{
	stmt_fnsig_t *sig;
	stmt_block_t *blk;
	stmt_fndef_t(const size_t &line, const size_t &col, stmt_fnsig_t *sig, stmt_block_t *blk);
	~stmt_fndef_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_header_t : public stmt_base_t
{
	// name is comma separated list of include files - along with bracket/quotes to be used,
	// flags is (optional) include cli parameters (space separated)
	lex::Lexeme names, flags;
	stmt_header_t(const size_t &line, const size_t &col, const lex::Lexeme &names,
		      const lex::Lexeme &flags);

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_lib_t : public stmt_base_t
{
	// flags is the space separated list of lib flags
	lex::Lexeme flags;
	stmt_lib_t(const size_t &line, const size_t &col, const lex::Lexeme &flags);

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_extern_t : public stmt_base_t
{
	lex::Lexeme fname; // name of the function
	stmt_header_t *headers;
	stmt_lib_t *libs;
	stmt_fnsig_t *sig;
	// headers and libs can be set separately - by default nullptr
	stmt_extern_t(const size_t &line, const size_t &col, const lex::Lexeme &fname,
		      stmt_header_t *headers, stmt_lib_t *libs, stmt_fnsig_t *sig);
	~stmt_extern_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_enumdef_t : public stmt_base_t
{
	std::vector<stmt_var_t *> items;
	// stmt_var_t contains only val(expr) here, no type
	stmt_enumdef_t(const size_t &line, const size_t &col,
		       const std::vector<stmt_var_t *> &items);
	~stmt_enumdef_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

// both declaration and definition
struct stmt_struct_t : public stmt_base_t
{
	bool decl;
	std::vector<lex::Lexeme> templates;
	std::vector<stmt_var_t *> fields;
	// stmt_var_t contains only type here, no val
	stmt_struct_t(const size_t &line, const size_t &col, const bool &decl,
		      const std::vector<lex::Lexeme> &templates,
		      const std::vector<stmt_var_t *> &fields);
	~stmt_struct_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_vardecl_t : public stmt_base_t
{
	std::vector<stmt_var_t *> decls;
	// stmt_var_t can contain any combination of type, in, val(any), or all three
	stmt_vardecl_t(const size_t &line, const size_t &col,
		       const std::vector<stmt_var_t *> &decls);
	~stmt_vardecl_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct cond_t
{
	stmt_base_t *cond; // can be nullptr (else)
	stmt_block_t *blk;
};

struct stmt_cond_t : public stmt_base_t
{
	std::vector<cond_t> conds;
	stmt_cond_t(const size_t &line, const size_t &col, const std::vector<cond_t> &conds);
	~stmt_cond_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_forin_t : public stmt_base_t
{
	lex::Lexeme iter;
	stmt_base_t *in; // L01
	stmt_block_t *blk;
	stmt_forin_t(const size_t &line, const size_t &col, const lex::Lexeme &iter,
		     stmt_base_t *in, stmt_block_t *blk);
	~stmt_forin_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_for_t : public stmt_base_t
{
	stmt_base_t *init; // either of stmt_vardecl_t or stmt_expr_t
	stmt_base_t *cond;
	stmt_base_t *incr;
	stmt_block_t *blk;
	// init, cond, incr can be nullptr
	stmt_for_t(const size_t &line, const size_t &col, stmt_base_t *init, stmt_base_t *cond,
		   stmt_base_t *incr, stmt_block_t *blk);
	~stmt_for_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_while_t : public stmt_base_t
{
	stmt_base_t *cond;
	stmt_block_t *blk;
	stmt_while_t(const size_t &line, const size_t &col, stmt_base_t *cond, stmt_block_t *blk);
	~stmt_while_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};

struct stmt_ret_t : public stmt_base_t
{
	stmt_base_t *val;
	stmt_ret_t(const size_t &line, const size_t &col, stmt_base_t *val);
	~stmt_ret_t();

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};
struct stmt_cont_t : public stmt_base_t
{
	stmt_cont_t(const size_t &line, const size_t &col);

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};
struct stmt_break_t : public stmt_base_t
{
	stmt_break_t(const size_t &line, const size_t &col);

	void disp(const bool &has_next);

	// bool check_type(Type &t, Type *expect = nullptr);
};
} // namespace parser
} // namespace sc

#endif // PARSER_STMTS_HPP