/*
	MIT License

	Copyright (c) 2021 Scribe Language Repositories

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#ifndef ANALYZER_TYPESYSTEM_HPP
#define ANALYZER_TYPESYSTEM_HPP

#include <string>
#include <unordered_map>

#include "parser/Stmts.hpp"

namespace sc
{
namespace typesys
{
enum Types
{
	SIMPLE,
	FN,
	EXTERN,
	TRAIT,
	STRUCT,
};
struct type_base_t
{
	Types type;
	size_t line, col;
	size_t ptr;  // number of ptrs
	size_t info; // all from TypeInfoMask
	std::vector<type_base_t *> arrcounts;
	type_base_t(const Types &type, const size_t &line, const size_t &col, const size_t &ptr,
		    const size_t &info, const std::vector<type_base_t *> &arrcounts);
	virtual ~type_base_t();

	bool cmp(type_base_t *other);

	virtual bool operator==(type_base_t *other) = 0;
	inline bool operator!=(type_base_t *other)
	{
		return *this == other ? false : true;
	}
};
struct type_simple_t : public type_base_t
{
	std::string name;
	type_simple_t(const size_t &line, const size_t &col, const size_t &ptr, const size_t &info,
		      const std::vector<type_base_t *> &arrcounts, const std::string &name);

	bool operator==(type_base_t *other);
};
struct type_fn_t : public type_base_t
{
	std::vector<lex::Lexeme> templates;
	std::vector<type_base_t *> args;
	type_base_t *ret;
	type_fn_t(const size_t &line, const size_t &col, const size_t &ptr, const size_t &info,
		  const std::vector<type_base_t *> &arrcounts,
		  const std::vector<lex::Lexeme> &templates, const std::vector<type_base_t *> args,
		  type_base_t *ret);
	~type_fn_t();

	bool operator==(type_base_t *other);
};
struct type_extern_t : public type_base_t
{
	std::string name;
	std::string header_name, header_flags;
	std::string libs;
	type_fn_t *fn;
	type_extern_t(const size_t &line, const size_t &col, const size_t &ptr, const size_t &info,
		      const std::vector<type_base_t *> &arrcounts, const std::string &name,
		      const std::string &header_name, const std::string &header_flags,
		      const std::string &libs, type_fn_t *fn);
	~type_extern_t();

	bool operator==(type_base_t *other);
};
struct type_struct_t : public type_base_t
{
	bool decl;
	std::vector<lex::Lexeme> templates;
	std::vector<type_base_t *> fields;
	type_struct_t(const size_t &line, const size_t &col, const size_t &ptr, const size_t &info,
		      const std::vector<type_base_t *> &arrcounts, const bool &decl,
		      const std::vector<lex::Lexeme> &templates,
		      const std::vector<type_base_t *> &fields);
	~type_struct_t();

	bool operator==(type_base_t *other);
};

struct VarTypeScope
{
	// vars on each scope
	std::unordered_map<std::string, type_base_t *> types;
};
struct VarTypeStack
{
	std::vector<VarTypeScope> scopes;
};
struct VarTypes
{
	VarTypeScope globals;
	// maps (full) path sources files to VarsSrc
	std::unordered_map<std::string, VarTypeStack> srcvars;
};
} // namespace typesys
} // namespace sc

#endif // ANALYZER_TYPESYSTEM_HPP