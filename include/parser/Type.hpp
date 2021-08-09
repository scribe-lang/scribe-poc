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

#ifndef PARSER_TYPE_HPP
#define PARSER_TYPE_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

#include "parser/Stmts.hpp"
#include "parser/Value.hpp"

inline bool startswith(const std::string &src, const std::string &term)
{
	return src.rfind(term, 0) == 0;
}

template<typename T> inline bool is_one_of(const std::vector<T> &vec, const T &elem)
{
	for(auto &v : vec) {
		if(v == elem) return true;
	}
	return false;
}

namespace sc
{
namespace parser
{
enum Types
{
	TSIMPLE,
	TSTRUCT,
	TENUM,
	TFUNC,
	TFUNCMAP,
	TVARIADIC,
};

struct Type
{
	Types type;
	Stmt *parent; // associated stmt with type (can be nullptr if required)
	int64_t id;
	size_t ptr;
	size_t info;
	intrinsic_fn_t intrin_fn;

	Type(const Types &type, Stmt *parent, const size_t &ptr, const size_t &info);
	Type(const int64_t &id, const Types &type, Stmt *parent, const size_t &ptr,
	     const size_t &info, intrinsic_fn_t intrin_fn);
	virtual ~Type();

	virtual Type *copy(const size_t &append_info = 0)				   = 0;
	virtual Type *specialize(const std::unordered_map<std::string, Type *> &templates) = 0;
	// ignore_id is for templates
	bool compatible_base(Type *rhs, const bool &is_templ, const size_t &line,
			     const size_t &col);
	virtual bool compatible(Type *rhs, const size_t &line, const size_t &col) = 0;
	virtual bool assignTemplateActuals(Type *actual,
					   std::unordered_map<std::string, Type *> &templates,
					   const size_t &line, const size_t &col) = 0;

	inline void set_intrinsic(intrinsic_fn_t intrinsic)
	{
		intrin_fn = intrinsic;
	}
	inline bool call_intrinsic(TypeMgr &types, ValueMgr &values, StmtExpr *base,
				   StmtFnCallInfo *args)
	{
		return intrin_fn ? intrin_fn(types, values, base, args->templates, args->args)
				 : true;
	}

	bool booleanCompatible();
	bool integerCompatible();

	std::string str_base();
	virtual std::string str() = 0;
	std::string mangled_name_base();
	virtual std::string mangled_name() = 0;
};

template<typename T> T *as(Type *t)
{
	return static_cast<T *>(t);
}

struct TypeSimple : public Type
{
	// is template is checked by the condition - name begins with '@'
	std::string name;

	TypeSimple(Stmt *parent, const size_t &ptr, const size_t &info, const std::string &name);
	TypeSimple(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		   intrinsic_fn_t intrin_fn, const std::string &name);

	Type *copy(const size_t &append_info = 0);
	Type *specialize(const std::unordered_map<std::string, Type *> &templates);
	bool compatible(Type *rhs, const size_t &line, const size_t &col);
	bool assignTemplateActuals(Type *actual, std::unordered_map<std::string, Type *> &templates,
				   const size_t &line, const size_t &col);

	std::string str();
	std::string mangled_name();
};

struct TypeStruct : public Type
{
	bool is_decl_only;
	bool is_import; // does not delete stored fields (intended to prevent unnecessary copies)
	bool is_def;
	size_t templ;
	std::vector<std::string> field_order;
	std::unordered_map<std::string, Type *> fields;

	TypeStruct(Stmt *parent, const size_t &ptr, const size_t &info, const bool &is_import,
		   const size_t &templ, const std::vector<std::string> &field_order,
		   const std::unordered_map<std::string, Type *> &fields);
	TypeStruct(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		   const bool &is_import, const bool &is_def, intrinsic_fn_t intrin_fn,
		   const size_t &templ, const std::vector<std::string> &field_order,
		   const std::unordered_map<std::string, Type *> &fields);
	~TypeStruct();

	inline void set_decl_only(const bool &decl_only)
	{
		is_decl_only = decl_only;
	}

	Type *copy(const size_t &append_info = 0);
	Type *specialize(const std::unordered_map<std::string, Type *> &templates);
	bool compatible(Type *rhs, const size_t &line, const size_t &col);
	// checks if instantiation is viable with callinfo, returns specialized instance of struct
	// if true; nullptr if false
	TypeStruct *specialize_compatible_call(StmtFnCallInfo *callinfo,
					       std::unordered_map<std::string, Type *> &templates);
	bool assignTemplateActuals(Type *actual, std::unordered_map<std::string, Type *> &templates,
				   const size_t &line, const size_t &col);

	std::string str();
	std::string mangled_name();

	bool add_field(const std::string &name, Type *val);
	bool add_field_copy(const std::string &name, Type *val);

	void set_fields(const std::vector<std::string> &order,
			const std::unordered_map<std::string, Type *> &vals);
	void set_fields_copy(const std::vector<std::string> &order,
			     const std::unordered_map<std::string, Type *> &vals);

	Type *get_field(const std::string &name);

	inline bool has_field(const std::string &name)
	{
		return fields.find(name) != fields.end();
	}
};

struct TypeFunc : public Type
{
	size_t scope;
	size_t templ;
	bool has_va;
	std::vector<Type *> args;
	Type *rettype;

	TypeFunc(Stmt *parent, const size_t &ptr, const size_t &info, const size_t &scope,
		 const size_t &templ, const bool &has_va, const std::vector<Type *> &args,
		 Type *rettype);
	TypeFunc(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		 intrinsic_fn_t intrin_fn, const size_t &scope, const size_t &templ,
		 const bool &has_va, const std::vector<Type *> &args, Type *rettype);
	~TypeFunc();

	Type *copy(const size_t &append_info = 0);
	Type *specialize(const std::unordered_map<std::string, Type *> &templates);
	bool compatible(Type *rhs, const size_t &line, const size_t &col);
	// checks for compatibility and specializes the signature (for templates)
	TypeFunc *specialize_compatible_call(StmtFnCallInfo *callinfo,
					     std::unordered_map<std::string, Type *> &templates);
	bool assignTemplateActuals(Type *actual, std::unordered_map<std::string, Type *> &templates,
				   const size_t &line, const size_t &col);

	std::string str();
	std::string mangled_name();
};

struct TypeFuncMap : public Type
{
	std::unordered_map<std::string, TypeFunc *> funcs;
	Type *self; // if member call, self will have the caller's type which must be put in arglist
		    // at calling point
	TypeFuncMap(Stmt *parent, const size_t &ptr, const size_t &info,
		    const std::unordered_map<std::string, TypeFunc *> &funcs);
	TypeFuncMap(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		    const std::unordered_map<std::string, TypeFunc *> &funcs, Type *self);
	~TypeFuncMap();

	Type *copy(const size_t &append_info = 0);
	Type *specialize(const std::unordered_map<std::string, Type *> &templates);
	bool compatible(Type *rhs, const size_t &line, const size_t &col);
	bool assignTemplateActuals(Type *actual, std::unordered_map<std::string, Type *> &templates,
				   const size_t &line, const size_t &col);

	void setSelf(Type *s);
	Type *&getSelf();

	std::string str();
	std::string mangled_name();

	TypeFunc *decide_func(StmtFnCallInfo *callinfo,
			      std::unordered_map<std::string, Type *> &templates);
	TypeFunc *decide_func(Type *vartype);
};

struct TypeVariadic : public Type
{
	std::vector<Type *> args;
	// if indexing is already done or not (only usable if indexing is done)
	bool is_indexed;
	TypeVariadic(Stmt *parent, const size_t &ptr, const size_t &info,
		     const std::vector<Type *> &args);
	TypeVariadic(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		     const std::vector<Type *> &args);
	~TypeVariadic();

	Type *copy(const size_t &append_info = 0);
	Type *specialize(const std::unordered_map<std::string, Type *> &templates);
	bool compatible(Type *rhs, const size_t &line, const size_t &col);
	bool assignTemplateActuals(Type *actual, std::unordered_map<std::string, Type *> &templates,
				   const size_t &line, const size_t &col);

	void setIndexed(const bool &indexed);
	bool isIndexed();

	std::string str();
	std::string mangled_name();

	Type *get_arg(const size_t &idx);
};
} // namespace parser
} // namespace sc

#endif // PARSER_TYPE_HPP