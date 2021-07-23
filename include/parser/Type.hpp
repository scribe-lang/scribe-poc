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
std::vector<std::string> basenumtypes();

enum Types
{
	TSIMPLE,
	TSTRUCT,
	TENUM,
	TFUNC,
	TFUNCMAP,
	TVARIADIC,
};

typedef bool (*intrinsic_fn_t)(VarMgr &vars, stmt_base_t *stmt);
#define INTRINSIC(name) bool intrinsic_##name(VarMgr &vars, stmt_base_t *stmt)

struct type_base_t
{
	Types type;
	stmt_base_t *parent; // associated stmt with type (can be nullptr if required)
	int64_t id;
	size_t ptr;
	size_t info;
	std::vector<type_base_t *> counts; // for arrays
	intrinsic_fn_t intrin_fn;

	type_base_t(const Types &type, stmt_base_t *parent, const size_t &ptr, const size_t &info);
	type_base_t(const int64_t &id, const Types &type, stmt_base_t *parent, const size_t &ptr,
		    const size_t &info, intrinsic_fn_t intrin_fn);
	virtual ~type_base_t();

	virtual type_base_t *copy()						     = 0;
	virtual type_base_t *specialize(const std::vector<type_base_t *> &templates) = 0;
	// ignore_id is for templates
	bool compatible_base(type_base_t *rhs, const bool &is_templ, const size_t &line,
			     const size_t &col);
	virtual bool compatible(type_base_t *rhs, const size_t &line, const size_t &col) = 0;

	inline void add_count(type_base_t *count)
	{
		counts.push_back(count);
	}

	inline void set_intrinsic(intrinsic_fn_t intrinsic)
	{
		intrin_fn = intrinsic;
	}
	inline bool call_intrinsic(VarMgr &vars, stmt_base_t *stmt)
	{
		return intrin_fn ? intrin_fn(vars, stmt) : true;
	}

	std::string str_base();
	virtual std::string str() = 0;
	std::string mangled_name_base();
	virtual std::string mangled_name() = 0;
};

struct type_simple_t : public type_base_t
{
	// is template is checked by the condition - name begins with '@'
	std::string name;

	type_simple_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
		      const std::string &name);
	type_simple_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr, const size_t &info,
		      intrinsic_fn_t intrin_fn, const std::string &name);

	type_base_t *copy();
	type_base_t *specialize(const std::vector<type_base_t *> &templates);
	bool compatible(type_base_t *rhs, const size_t &line, const size_t &col);

	std::string str();
	std::string mangled_name();
};

struct type_struct_t : public type_base_t
{
	bool is_decl_only;
	bool is_ref; // does not delete stored fields (intended to prevent unnecessary copies)
	bool is_def;
	size_t templ;
	std::vector<std::string> field_order;
	std::unordered_map<std::string, type_base_t *> fields;

	type_struct_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
		      const bool &is_ref, const size_t &templ,
		      const std::vector<std::string> &field_order,
		      const std::unordered_map<std::string, type_base_t *> &fields);
	type_struct_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr, const size_t &info,
		      const bool &is_ref, const bool &is_def, intrinsic_fn_t intrin_fn,
		      const size_t &templ, const std::vector<std::string> &field_order,
		      const std::unordered_map<std::string, type_base_t *> &fields);
	~type_struct_t();

	inline void set_decl_only(const bool &decl_only)
	{
		is_decl_only = decl_only;
	}

	type_base_t *copy();
	type_base_t *specialize(const std::vector<type_base_t *> &templates);
	bool compatible(type_base_t *rhs, const size_t &line, const size_t &col);
	// checks if instantiation is viable with callinfo, returns specialized instance of struct
	// if true; nullptr if false
	type_struct_t *specialize_compatible_call(stmt_fncallinfo_t *callinfo,
						  std::vector<type_base_t *> &templates);

	std::string str();
	std::string mangled_name();

	bool add_field(const std::string &name, type_base_t *val);
	bool add_field_copy(const std::string &name, type_base_t *val);

	void set_fields(const std::vector<std::string> &order,
			const std::unordered_map<std::string, type_base_t *> &vals);
	void set_fields_copy(const std::vector<std::string> &order,
			     const std::unordered_map<std::string, type_base_t *> &vals);

	type_base_t *get_field(const std::string &name);

	inline bool has_field(const std::string &name)
	{
		return fields.find(name) != fields.end();
	}
};

struct type_func_t : public type_base_t
{
	size_t scope;
	size_t templ;
	bool comptime;
	std::vector<type_base_t *> args;
	type_base_t *rettype;

	type_func_t(stmt_base_t *parent, const size_t &ptr, const size_t &info, const size_t &scope,
		    const size_t &templ, const bool &comptime,
		    const std::vector<type_base_t *> &args, type_base_t *rettype);
	type_func_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr, const size_t &info,
		    intrinsic_fn_t intrin_fn, const size_t &scope, const size_t &templ,
		    const bool &comptime, const std::vector<type_base_t *> &args,
		    type_base_t *rettype);
	~type_func_t();

	type_base_t *copy();
	type_base_t *specialize(const std::vector<type_base_t *> &templates);
	bool compatible(type_base_t *rhs, const size_t &line, const size_t &col);
	// checks for compatibility and specializes the signature (for templates)
	type_func_t *specialize_compatible_call(stmt_fncallinfo_t *callinfo,
						std::vector<type_base_t *> &templates);

	std::string str();
	std::string mangled_name();
};

struct type_funcmap_t : public type_base_t
{
	std::unordered_map<std::string, type_func_t *> funcs;
	type_funcmap_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
		       const std::unordered_map<std::string, type_func_t *> &funcs);
	type_funcmap_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
		       const size_t &info,
		       const std::unordered_map<std::string, type_func_t *> &funcs);

	type_base_t *copy();
	type_base_t *specialize(const std::vector<type_base_t *> &templates);
	bool compatible(type_base_t *rhs, const size_t &line, const size_t &col);

	std::string str();
	std::string mangled_name();

	type_func_t *decide_func(stmt_fncallinfo_t *callinfo,
				 std::vector<type_base_t *> &templates);
	type_func_t *decide_func(type_base_t *vartype);
};

struct type_variadic_t : public type_base_t
{
	std::vector<type_base_t *> args;
	type_variadic_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
			const std::vector<type_base_t *> &args);
	type_variadic_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
			const size_t &info, const std::vector<type_base_t *> &args);

	type_base_t *copy();
	type_base_t *specialize(const std::vector<type_base_t *> &templates);
	bool compatible(type_base_t *rhs, const size_t &line, const size_t &col);

	std::string str();
	std::string mangled_name();
};
} // namespace parser
} // namespace sc

#endif // PARSER_TYPE_HPP