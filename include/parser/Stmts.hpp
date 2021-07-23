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
struct VarMgr;
struct type_base_t;
struct type_func_t;
struct type_struct_t;

enum StmtType
{
	BLOCK,
	TYPE,
	SIMPLE,
	EXPR,
	FNCALLINFO,
	VAR,   // Var and (Type or Val) (<var> : <type> = <value>)
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

struct stmt_base_t
{
	StmtType type;
	stmt_base_t *parent;
	size_t src_id;
	size_t line;
	size_t col;
	type_base_t *vtyp;
	bool is_specialized; // to prevent cycles (fn -> type_fn -> fn ...)
	bool is_intrin;	     // if this is an intrinsic function call
	stmt_base_t(const StmtType &type, const size_t &src_id, const size_t &line,
		    const size_t &col);
	virtual ~stmt_base_t();

	// NEVER use hidden_copy(); instead use copy()
	stmt_base_t *copy(const bool &copy_vtyp);
	virtual stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par) = 0;
	virtual void disp(const bool &has_next)					  = 0;
	virtual void set_parent(stmt_base_t *parent)				  = 0;
	virtual bool assign_type(VarMgr &vars)					  = 0;
	virtual bool call_intrinsic(VarMgr &vars)				  = 0;
	virtual stmt_base_t *executecomptime(VarMgr &vars)			  = 0;

	stmt_base_t *get_parent_with_type(const StmtType &typ);

	std::string typestr();
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
	stmt_type_t(const size_t &src_id, const size_t &line, const size_t &col, const size_t &ptr,
		    const size_t &info, const std::vector<lex::Lexeme> &name,
		    const std::vector<lex::Lexeme> &templates);
	stmt_type_t(const size_t &src_id, const size_t &line, const size_t &col, stmt_base_t *fn);
	~stmt_type_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);

	std::string getname();
};

struct stmt_block_t : public stmt_base_t
{
	std::vector<stmt_base_t *> stmts;
	stmt_block_t(const size_t &src_id, const size_t &line, const size_t &col,
		     const std::vector<stmt_base_t *> &stmts);
	~stmt_block_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_simple_t : public stmt_base_t
{
	lex::Lexeme val;
	stmt_simple_t(const size_t &src_id, const size_t &line, const size_t &col,
		      const lex::Lexeme &val);
	~stmt_simple_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_fncallinfo_t : public stmt_base_t
{
	std::vector<stmt_type_t *> templates;
	std::vector<stmt_base_t *> args;
	stmt_fncallinfo_t(const size_t &src_id, const size_t &line, const size_t &col,
			  const std::vector<stmt_type_t *> &templates,
			  const std::vector<stmt_base_t *> &args);
	~stmt_fncallinfo_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
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
	stmt_expr_t(const size_t &src_id, const size_t &line, const size_t &col, stmt_base_t *lhs,
		    const lex::Lexeme &oper, stmt_base_t *rhs);
	~stmt_expr_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_var_t : public stmt_base_t
{
	lex::Lexeme name;
	stmt_type_t *vtype;
	stmt_base_t *val; // either of expr, funcdef, enumdef, or structdef
	// at least one of type or val must be present
	stmt_var_t(const size_t &src_id, const size_t &line, const size_t &col,
		   const lex::Lexeme &name, stmt_type_t *vtype, stmt_base_t *val);
	~stmt_var_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_fnsig_t : public stmt_base_t
{
	std::vector<lex::Lexeme> templates;
	// stmt_var_t contains only type here, no val
	std::vector<stmt_var_t *> params;
	stmt_type_t *rettype;
	bool comptime;
	stmt_fnsig_t(const size_t &src_id, const size_t &line, const size_t &col,
		     const std::vector<lex::Lexeme> &templates, std::vector<stmt_var_t *> &params,
		     stmt_type_t *rettype, const bool &comptime);
	~stmt_fnsig_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_fndef_t : public stmt_base_t
{
	stmt_fnsig_t *sig;
	stmt_block_t *blk;
	stmt_fndef_t(const size_t &src_id, const size_t &line, const size_t &col, stmt_fnsig_t *sig,
		     stmt_block_t *blk);
	~stmt_fndef_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_header_t : public stmt_base_t
{
	// name is comma separated list of include files - along with bracket/quotes to be used,
	// flags is (optional) include cli parameters (space separated)
	lex::Lexeme names, flags;
	stmt_header_t(const size_t &src_id, const size_t &line, const size_t &col,
		      const lex::Lexeme &names, const lex::Lexeme &flags);

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_lib_t : public stmt_base_t
{
	// flags is the space separated list of lib flags
	lex::Lexeme flags;
	stmt_lib_t(const size_t &src_id, const size_t &line, const size_t &col,
		   const lex::Lexeme &flags);

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_extern_t : public stmt_base_t
{
	lex::Lexeme fname; // name of the function
	stmt_header_t *headers;
	stmt_lib_t *libs;
	stmt_fnsig_t *sig;
	// headers and libs can be set separately - by default nullptr
	stmt_extern_t(const size_t &src_id, const size_t &line, const size_t &col,
		      const lex::Lexeme &fname, stmt_header_t *headers, stmt_lib_t *libs,
		      stmt_fnsig_t *sig);
	~stmt_extern_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_enumdef_t : public stmt_base_t
{
	std::vector<stmt_var_t *> items;
	// stmt_var_t contains only val(expr) here, no type
	stmt_enumdef_t(const size_t &src_id, const size_t &line, const size_t &col,
		       const std::vector<stmt_var_t *> &items);
	~stmt_enumdef_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

// both declaration and definition
struct stmt_struct_t : public stmt_base_t
{
	bool decl;
	std::vector<lex::Lexeme> templates;
	std::vector<stmt_var_t *> fields;
	// stmt_var_t contains only type here, no val
	stmt_struct_t(const size_t &src_id, const size_t &line, const size_t &col, const bool &decl,
		      const std::vector<lex::Lexeme> &templates,
		      const std::vector<stmt_var_t *> &fields);
	~stmt_struct_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_vardecl_t : public stmt_base_t
{
	std::vector<stmt_var_t *> decls;
	// stmt_var_t can contain any combination of type, in, val(any), or all three
	stmt_vardecl_t(const size_t &src_id, const size_t &line, const size_t &col,
		       const std::vector<stmt_var_t *> &decls);
	~stmt_vardecl_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct cond_t
{
	stmt_base_t *cond; // can be nullptr (else)
	stmt_block_t *blk;
};

struct stmt_cond_t : public stmt_base_t
{
	std::vector<cond_t> conds;
	stmt_cond_t(const size_t &src_id, const size_t &line, const size_t &col,
		    const std::vector<cond_t> &conds);
	~stmt_cond_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_forin_t : public stmt_base_t
{
	lex::Lexeme iter;
	stmt_base_t *in; // L01
	stmt_block_t *blk;
	stmt_forin_t(const size_t &src_id, const size_t &line, const size_t &col,
		     const lex::Lexeme &iter, stmt_base_t *in, stmt_block_t *blk);
	~stmt_forin_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_for_t : public stmt_base_t
{
	stmt_base_t *init; // either of stmt_vardecl_t or stmt_expr_t
	stmt_base_t *cond;
	stmt_base_t *incr;
	stmt_block_t *blk;
	// init, cond, incr can be nullptr
	stmt_for_t(const size_t &src_id, const size_t &line, const size_t &col, stmt_base_t *init,
		   stmt_base_t *cond, stmt_base_t *incr, stmt_block_t *blk);
	~stmt_for_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_while_t : public stmt_base_t
{
	stmt_base_t *cond;
	stmt_block_t *blk;
	stmt_while_t(const size_t &src_id, const size_t &line, const size_t &col, stmt_base_t *cond,
		     stmt_block_t *blk);
	~stmt_while_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};

struct stmt_ret_t : public stmt_base_t
{
	stmt_base_t *val;
	stmt_ret_t(const size_t &src_id, const size_t &line, const size_t &col, stmt_base_t *val);
	~stmt_ret_t();

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};
struct stmt_cont_t : public stmt_base_t
{
	stmt_cont_t(const size_t &src_id, const size_t &line, const size_t &col);

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};
struct stmt_break_t : public stmt_base_t
{
	stmt_break_t(const size_t &src_id, const size_t &line, const size_t &col);

	stmt_base_t *hidden_copy(const bool &copy_vtyp, stmt_base_t *par);
	void disp(const bool &has_next);
	void set_parent(stmt_base_t *parent);
	bool assign_type(VarMgr &vars);
	bool call_intrinsic(VarMgr &vars);
	stmt_base_t *executecomptime(VarMgr &vars);
};
} // namespace parser
} // namespace sc

#endif // PARSER_STMTS_HPP