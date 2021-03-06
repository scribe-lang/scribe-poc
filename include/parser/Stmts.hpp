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
struct TypeFunc;
struct TypeStruct;
struct TypeSimple;
struct Type;
class Module;

struct Value;
struct ValueMgr;

struct Stmt;
struct StmtType;
struct StmtExpr;
struct StmtFnCallInfo;

typedef bool (*intrinsic_fn_t)(TypeMgr &types, ValueMgr &values, StmtExpr *base,
			       const std::vector<StmtType *> &templates,
			       const std::vector<Stmt *> &args);
#define INTRINSIC(name)                                                         \
	bool intrinsic_##name(TypeMgr &types, ValueMgr &values, StmtExpr *base, \
			      const std::vector<StmtType *> &templates,         \
			      const std::vector<Stmt *> &args)

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
	Stmts stmt_type;
	Module *mod;
	size_t line;
	size_t col;
	Stmt *parent;

	// these members are not assigned on stmt creation
	// Stmts with is_specialized are not explicitly typeAssigned in a block
	// their type assignment is done in InitTemplateFn
	bool is_specialized; // to prevent cycles (fn -> type_fn -> fn ...)
	bool is_comptime;
	// 0 => not specialized
	size_t specialized_id;

	Type *type;
	Value *value;

	// if a Stmt is type casted, this defines which type it is cast from
	Type *cast_from;

	// these must NEVER be erased (excluding copy)
	// since the values are deleted by clearValue(), this will be an exception
	size_t variadic_index;

	Stmt(const Stmts &stmt_type, Module *mod, const size_t &line, const size_t &col);
	virtual ~Stmt();

	// NEVER use hiddenCopy(); instead use copy()
	Stmt *copy(const bool &with_value = false);
	virtual Stmt *hiddenCopy(const bool &with_value, Stmt *par) = 0;
	virtual void disp(const bool &has_next)			    = 0;
	virtual void setParent(Stmt *parent)			    = 0;
	virtual bool assignType(TypeMgr &types)			    = 0;
	virtual bool assignValue(TypeMgr &types, ValueMgr &vals)    = 0;
	virtual void clearValue()				    = 0;
	virtual void setValueUnique(ValueMgr &vals)		    = 0;
	virtual void mergeValues(Stmt *stmt)			    = 0;

	Stmt *getParentWithType(const Stmts &typ, Stmt **childofparent = nullptr);
	Stmt *getTopLevelParent();

	void setSpecialized(const bool &specialized);
	bool isSpecialized();
	void setComptime(const bool &comptime);
	bool isComptime();
	void setSpecializedID(const size_t &id);
	const size_t &getSpecializedID();
	void setVariadicIndex(const size_t &va_idx);
	const size_t &getVariadicIndex();

	// calls to->copy() as well
	void cast(Type *to);
	bool isCast();
	Type *getCastFrom();

	// if value is set, updates it (and all references of it),
	// else, sets the value
	void updateValue(ValueMgr &values, Value *newvalue);

	std::string typeString();

	std::string stmtTypeString();
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
	StmtType(Module *mod, const size_t &line, const size_t &col, const size_t &ptr,
		 const size_t &info, const std::vector<lex::Lexeme> &name,
		 const std::vector<lex::Lexeme> &templates);
	StmtType(Module *mod, const size_t &line, const size_t &col, Stmt *fn);
	~StmtType();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);

	std::string getname();
};

struct StmtBlock : public Stmt
{
	std::vector<Stmt *> stmts;
	StmtBlock(Module *mod, const size_t &line, const size_t &col,
		  const std::vector<Stmt *> &stmts);
	~StmtBlock();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtSimple : public Stmt
{
	lex::Lexeme val;
	bool applied_module_id;

	StmtSimple(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &val);
	~StmtSimple();

	void setAppliedModuleID(const bool &applied);
	bool isAppliedModuleID();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtFnCallInfo : public Stmt
{
	std::vector<StmtType *> templates;
	std::vector<Stmt *> args;
	StmtFnCallInfo(Module *mod, const size_t &line, const size_t &col,
		       const std::vector<StmtType *> &templates, const std::vector<Stmt *> &args);
	~StmtFnCallInfo();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtExpr : public Stmt
{
	size_t commas;
	Stmt *lhs;
	lex::Lexeme oper;
	Stmt *rhs;
	StmtBlock *or_blk;
	lex::Lexeme or_blk_var;
	intrinsic_fn_t intrin_fn;
	bool is_intrinsic; // if @ is present before function name
	int64_t decidedfn_id;

	// or_blk and or_blk_var can be set separately - nullptr/INVALID by default
	StmtExpr(Module *mod, const size_t &line, const size_t &col, Stmt *lhs,
		 const lex::Lexeme &oper, Stmt *rhs);
	~StmtExpr();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);

	void setIntrinsicFunc(intrinsic_fn_t intrin);
	bool hasIntrinsicFunc();
	bool isIntrinsic();
	bool callIntrinsic(TypeMgr &types, ValueMgr &values, StmtExpr *base,
			   const std::vector<StmtType *> &templates,
			   const std::vector<Stmt *> &args);

	void setParseIntrinsic(const bool &pi);
	bool isParseIntrinsic();

	void setDecidedFuncID(const int64_t &id);
	int64_t &getDecidedFuncID();
};

struct StmtVar : public Stmt
{
	lex::Lexeme name;
	StmtType *vtype;
	Stmt *val; // either of expr, funcdef, enumdef, or structdef
	// at least one of type or val must be present
	StmtVar(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &name,
		StmtType *vtype, Stmt *val);
	~StmtVar();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtFnSig : public Stmt
{
	std::vector<lex::Lexeme> templates;
	// StmtVar contains only type here, no val
	std::vector<StmtVar *> args;
	StmtType *rettype;
	bool has_variadic;
	bool is_member;
	StmtFnSig(Module *mod, const size_t &line, const size_t &col,
		  const std::vector<lex::Lexeme> &templates, std::vector<StmtVar *> &args,
		  StmtType *rettype, const bool &has_variadic);
	~StmtFnSig();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);

	void setMember(const bool &is_mem);
	bool isMember();
};

struct StmtFnDef : public Stmt
{
	StmtFnSig *sig;
	StmtBlock *blk;
	StmtFnDef(Module *mod, const size_t &line, const size_t &col, StmtFnSig *sig,
		  StmtBlock *blk);
	~StmtFnDef();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtHeader : public Stmt
{
	// name is comma separated list of include files - along with bracket/quotes to be used,
	// flags is (optional) include cli parameters (space separated)
	lex::Lexeme names, flags;
	StmtHeader(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &names,
		   const lex::Lexeme &flags);

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtLib : public Stmt
{
	// flags is the space separated list of lib flags
	lex::Lexeme flags;
	StmtLib(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &flags);

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtExtern : public Stmt
{
	lex::Lexeme fname; // name of the function
	StmtHeader *headers;
	StmtLib *libs;
	StmtFnSig *sig;
	// headers and libs can be set separately - by default nullptr
	StmtExtern(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &fname,
		   StmtHeader *headers, StmtLib *libs, StmtFnSig *sig);
	~StmtExtern();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtEnum : public Stmt
{
	std::vector<lex::Lexeme> items;
	// StmtVar contains only val(expr) here, no type
	StmtEnum(Module *mod, const size_t &line, const size_t &col,
		 const std::vector<lex::Lexeme> &items);
	~StmtEnum();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

// both declaration and definition
struct StmtStruct : public Stmt
{
	bool decl;
	std::vector<lex::Lexeme> templates;
	std::vector<StmtVar *> fields;
	// StmtVar contains only type here, no val
	StmtStruct(Module *mod, const size_t &line, const size_t &col, const bool &decl,
		   const std::vector<lex::Lexeme> &templates, const std::vector<StmtVar *> &fields);
	~StmtStruct();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtVarDecl : public Stmt
{
	std::vector<StmtVar *> decls;
	// StmtVar can contain any combination of type, in, val(any), or all three
	StmtVarDecl(Module *mod, const size_t &line, const size_t &col,
		    const std::vector<StmtVar *> &decls);
	~StmtVarDecl();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct cond_t
{
	Stmt *cond; // can be nullptr (else)
	StmtBlock *blk;
};

struct StmtCond : public Stmt
{
	std::vector<cond_t> conds;
	bool is_inline;
	StmtCond(Module *mod, const size_t &line, const size_t &col,
		 const std::vector<cond_t> &conds);
	~StmtCond();

	void setInline(const bool &_inline);
	bool isInline();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtForIn : public Stmt
{
	lex::Lexeme iter;
	Stmt *in; // L01
	StmtBlock *blk;
	StmtForIn(Module *mod, const size_t &line, const size_t &col, const lex::Lexeme &iter,
		  Stmt *in, StmtBlock *blk);
	~StmtForIn();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtFor : public Stmt
{
	Stmt *init; // either of StmtVarDecl or StmtExpr
	Stmt *cond;
	Stmt *incr;
	StmtBlock *blk;
	bool is_inline;
	// init, cond, incr can be nullptr
	StmtFor(Module *mod, const size_t &line, const size_t &col, Stmt *init, Stmt *cond,
		Stmt *incr, StmtBlock *blk);
	~StmtFor();

	void setInline(const bool &_inline);
	bool isInline();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtWhile : public Stmt
{
	Stmt *cond;
	StmtBlock *blk;
	StmtWhile(Module *mod, const size_t &line, const size_t &col, Stmt *cond, StmtBlock *blk);
	~StmtWhile();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};

struct StmtRet : public Stmt
{
	Stmt *val;
	StmtRet(Module *mod, const size_t &line, const size_t &col, Stmt *val);
	~StmtRet();

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};
struct StmtContinue : public Stmt
{
	StmtContinue(Module *mod, const size_t &line, const size_t &col);

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};
struct StmtBreak : public Stmt
{
	StmtBreak(Module *mod, const size_t &line, const size_t &col);

	Stmt *hiddenCopy(const bool &with_value, Stmt *par);
	void disp(const bool &has_next);
	void setParent(Stmt *parent);
	bool assignType(TypeMgr &types);
	bool assignValue(TypeMgr &types, ValueMgr &vals);
	void clearValue();
	void setValueUnique(ValueMgr &vals);
	void mergeValues(Stmt *stmt);
};
} // namespace parser
} // namespace sc

#endif // PARSER_STMTS_HPP