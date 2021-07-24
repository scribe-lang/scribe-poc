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
struct TypeMgr;
struct Type;
struct TypeFunc;
struct TypeStruct;

struct ValueMgr;
struct Value;

class RAIIParser;

enum Stmts
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

struct Stmt
{
	Stmts type;
	Stmt *parent;
	size_t src_id;
	size_t line;
	size_t col;
	bool is_specialized; // to prevent cycles (fn -> type_fn -> fn ...)
	bool is_intrin;	     // if this is an intrinsic function call

	Type *vtyp;
	Value *value;

	Stmt(const Stmts &type, const size_t &src_id, const size_t &line, const size_t &col);
	virtual ~Stmt();

	// NEVER use hidden_copy(); instead use copy()
	Stmt *copy(const bool &copy_vtyp, const bool &copy_val);
	virtual Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par) = 0;
	virtual void disp(const bool &has_next)						  = 0;
	virtual void set_parent(Stmt *parent)						  = 0;
	virtual bool assign_type(TypeMgr &types)					  = 0;
	virtual bool const_fold(TypeMgr &types, ValueMgr &vals)				  = 0;
	// comptime execute here
	virtual bool call_intrinsic(TypeMgr &types) = 0;

	Stmt *get_parent_with_type(const Stmts &typ);

	std::string typestr();

	// returns vtyp and value as string
	std::string extrastr();
};

template<typename T> T *as(Stmt *data)
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

struct StmtType : public Stmt
{
	bool func;
	size_t ptr;  // number of ptrs
	size_t info; // all from TypeInfoMask
	std::vector<lex::Lexeme> name;
	std::vector<lex::Lexeme> templates;
	Stmt *fn;
	StmtType(const size_t &src_id, const size_t &line, const size_t &col, const size_t &ptr,
		 const size_t &info, const std::vector<lex::Lexeme> &name,
		 const std::vector<lex::Lexeme> &templates);
	StmtType(const size_t &src_id, const size_t &line, const size_t &col, Stmt *fn);
	~StmtType();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);

	std::string getname();
};

struct StmtBlock : public Stmt
{
	std::vector<Stmt *> stmts;
	StmtBlock(const size_t &src_id, const size_t &line, const size_t &col,
		  const std::vector<Stmt *> &stmts);
	~StmtBlock();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtSimple : public Stmt
{
	lex::Lexeme val;
	StmtSimple(const size_t &src_id, const size_t &line, const size_t &col,
		   const lex::Lexeme &val);
	~StmtSimple();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtFnCallInfo : public Stmt
{
	std::vector<StmtType *> templates;
	std::vector<Stmt *> args;
	StmtFnCallInfo(const size_t &src_id, const size_t &line, const size_t &col,
		       const std::vector<StmtType *> &templates, const std::vector<Stmt *> &args);
	~StmtFnCallInfo();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtExpr : public Stmt
{
	size_t commas;
	Stmt *lhs;
	lex::Lexeme oper;
	Stmt *rhs;
	StmtBlock *or_blk;
	lex::Lexeme or_blk_var;
	// or_blk and or_blk_var can be set separately - nullptr/INVALID by default
	StmtExpr(const size_t &src_id, const size_t &line, const size_t &col, Stmt *lhs,
		 const lex::Lexeme &oper, Stmt *rhs);
	~StmtExpr();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtVar : public Stmt
{
	lex::Lexeme name;
	StmtType *vtype;
	Stmt *val; // either of expr, funcdef, enumdef, or structdef
	// at least one of type or val must be present
	StmtVar(const size_t &src_id, const size_t &line, const size_t &col,
		const lex::Lexeme &name, StmtType *vtype, Stmt *val);
	~StmtVar();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtFnSig : public Stmt
{
	std::vector<lex::Lexeme> templates;
	// StmtVar contains only type here, no val
	std::vector<StmtVar *> params;
	StmtType *rettype;
	bool comptime;
	StmtFnSig(const size_t &src_id, const size_t &line, const size_t &col,
		  const std::vector<lex::Lexeme> &templates, std::vector<StmtVar *> &params,
		  StmtType *rettype, const bool &comptime);
	~StmtFnSig();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtFnDef : public Stmt
{
	StmtFnSig *sig;
	StmtBlock *blk;
	StmtFnDef(const size_t &src_id, const size_t &line, const size_t &col, StmtFnSig *sig,
		  StmtBlock *blk);
	~StmtFnDef();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtHeader : public Stmt
{
	// name is comma separated list of include files - along with bracket/quotes to be used,
	// flags is (optional) include cli parameters (space separated)
	lex::Lexeme names, flags;
	StmtHeader(const size_t &src_id, const size_t &line, const size_t &col,
		   const lex::Lexeme &names, const lex::Lexeme &flags);

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtLib : public Stmt
{
	// flags is the space separated list of lib flags
	lex::Lexeme flags;
	StmtLib(const size_t &src_id, const size_t &line, const size_t &col,
		const lex::Lexeme &flags);

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtExtern : public Stmt
{
	lex::Lexeme fname; // name of the function
	StmtHeader *headers;
	StmtLib *libs;
	StmtFnSig *sig;
	// headers and libs can be set separately - by default nullptr
	StmtExtern(const size_t &src_id, const size_t &line, const size_t &col,
		   const lex::Lexeme &fname, StmtHeader *headers, StmtLib *libs, StmtFnSig *sig);
	~StmtExtern();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtEnum : public Stmt
{
	std::vector<StmtVar *> items;
	// StmtVar contains only val(expr) here, no type
	StmtEnum(const size_t &src_id, const size_t &line, const size_t &col,
		 const std::vector<StmtVar *> &items);
	~StmtEnum();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

// both declaration and definition
struct StmtStruct : public Stmt
{
	bool decl;
	std::vector<lex::Lexeme> templates;
	std::vector<StmtVar *> fields;
	// StmtVar contains only type here, no val
	StmtStruct(const size_t &src_id, const size_t &line, const size_t &col, const bool &decl,
		   const std::vector<lex::Lexeme> &templates, const std::vector<StmtVar *> &fields);
	~StmtStruct();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtVarDecl : public Stmt
{
	std::vector<StmtVar *> decls;
	// StmtVar can contain any combination of type, in, val(any), or all three
	StmtVarDecl(const size_t &src_id, const size_t &line, const size_t &col,
		    const std::vector<StmtVar *> &decls);
	~StmtVarDecl();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct cond_t
{
	Stmt *cond; // can be nullptr (else)
	StmtBlock *blk;
};

struct StmtCond : public Stmt
{
	std::vector<cond_t> conds;
	StmtCond(const size_t &src_id, const size_t &line, const size_t &col,
		 const std::vector<cond_t> &conds);
	~StmtCond();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtForIn : public Stmt
{
	lex::Lexeme iter;
	Stmt *in; // L01
	StmtBlock *blk;
	StmtForIn(const size_t &src_id, const size_t &line, const size_t &col,
		  const lex::Lexeme &iter, Stmt *in, StmtBlock *blk);
	~StmtForIn();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtFor : public Stmt
{
	Stmt *init; // either of StmtVarDecl or StmtExpr
	Stmt *cond;
	Stmt *incr;
	StmtBlock *blk;
	// init, cond, incr can be nullptr
	StmtFor(const size_t &src_id, const size_t &line, const size_t &col, Stmt *init, Stmt *cond,
		Stmt *incr, StmtBlock *blk);
	~StmtFor();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtWhile : public Stmt
{
	Stmt *cond;
	StmtBlock *blk;
	StmtWhile(const size_t &src_id, const size_t &line, const size_t &col, Stmt *cond,
		  StmtBlock *blk);
	~StmtWhile();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};

struct StmtRet : public Stmt
{
	Stmt *val;
	StmtRet(const size_t &src_id, const size_t &line, const size_t &col, Stmt *val);
	~StmtRet();

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};
struct StmtContinue : public Stmt
{
	StmtContinue(const size_t &src_id, const size_t &line, const size_t &col);

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};
struct StmtBreak : public Stmt
{
	StmtBreak(const size_t &src_id, const size_t &line, const size_t &col);

	Stmt *hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par);
	void disp(const bool &has_next);
	void set_parent(Stmt *parent);
	bool assign_type(TypeMgr &types);
	bool const_fold(TypeMgr &types, ValueMgr &vals);
	bool call_intrinsic(TypeMgr &types);
};
} // namespace parser
} // namespace sc

#endif // PARSER_STMTS_HPP