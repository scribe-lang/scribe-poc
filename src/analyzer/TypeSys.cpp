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

#include "analyzer/TypeSys.hpp"

namespace sc
{
namespace typesys
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_base_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

type_base_t::type_base_t(const Types &type, const size_t &line, const size_t &col,
			 const size_t &ptr, const size_t &info,
			 const std::vector<type_base_t *> &arrcounts)
	: type(type), line(line), col(col), ptr(ptr), info(info), arrcounts(arrcounts)
{}
type_base_t::~type_base_t()
{
	for(auto &ac : arrcounts) delete ac;
}

bool type_base_t::cmp(type_base_t *other)
{
	if(this->type != other->type) return false;
	if(this->ptr != other->ptr) return false;
	if(this->info != other->info) return false;
	if(this->arrcounts.size() != other->arrcounts.size()) return false;
	for(size_t i = 0; i < arrcounts.size(); ++i) {
		if(*this->arrcounts[i] != other->arrcounts[i]) return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// type_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

type_simple_t::type_simple_t(const size_t &line, const size_t &col, const size_t &ptr,
			     const size_t &info, const std::vector<type_base_t *> &arrcounts,
			     const std::string &name)
	: type_base_t(SIMPLE, line, col, ptr, info, arrcounts), name(name)
{}

bool type_simple_t::operator==(type_base_t *other)
{
	if(!cmp(other)) return false;
	if(this->name != ((type_simple_t *)other)->name) return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// type_fn_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

type_fn_t::type_fn_t(const size_t &line, const size_t &col, const size_t &ptr, const size_t &info,
		     const std::vector<type_base_t *> &arrcounts,
		     const std::vector<lex::Lexeme> &templates,
		     const std::vector<type_base_t *> args, type_base_t *ret)
	: type_base_t(FN, line, col, ptr, info, arrcounts), templates(templates), args(args),
	  ret(ret)
{}
type_fn_t::~type_fn_t()
{
	for(auto &a : args) delete a;
	if(ret) delete ret;
}

bool type_fn_t::operator==(type_base_t *other)
{
	if(!cmp(other)) return false;
	type_fn_t *oth = (type_fn_t *)other;
	if(this->templates.size() != oth->templates.size() || this->args.size() != oth->args.size())
		return false;
	for(size_t i = 0; i < this->templates.size(); ++i) {
		if(this->templates[i] != oth->templates[i]) return false;
	}
	for(size_t i = 0; i < this->args.size(); ++i) {
		if(*this->args[i] != oth->args[i]) return false;
	}
	if(*this->ret != oth->ret) return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// type_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

type_extern_t::type_extern_t(const size_t &line, const size_t &col, const size_t &ptr,
			     const size_t &info, const std::vector<type_base_t *> &arrcounts,
			     const std::string &name, const std::string &header_name,
			     const std::string &header_flags, const std::string &libs,
			     type_fn_t *fn)
	: type_base_t(EXTERN, line, col, ptr, info, arrcounts), name(name),
	  header_name(header_name), header_flags(header_flags), libs(libs), fn(fn)
{}
type_extern_t::~type_extern_t()
{
	if(fn) delete fn;
}

bool type_extern_t::operator==(type_base_t *other)
{
	if(!cmp(other)) return false;
	type_extern_t *oth = (type_extern_t *)other;
	if(this->name != oth->name || this->header_name != oth->header_name ||
	   this->header_flags != oth->header_flags || this->libs != oth->libs)
		return false;
	if(*this->fn != oth->fn) return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// type_struct_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

type_struct_t::type_struct_t(const size_t &line, const size_t &col, const size_t &ptr,
			     const size_t &info, const std::vector<type_base_t *> &arrcounts,
			     const bool &decl, const std::vector<lex::Lexeme> &templates,
			     const std::vector<type_base_t *> &fields)
	: type_base_t(STRUCT, line, col, ptr, info, arrcounts), templates(templates), fields(fields)
{}
type_struct_t::~type_struct_t()
{
	for(auto &f : fields) delete f;
}

bool type_struct_t::operator==(type_base_t *other)
{
	if(!cmp(other)) return false;
	type_struct_t *oth = (type_struct_t *)other;
	if(this->fields.size() != oth->fields.size()) return false;
	for(size_t i = 0; i < this->fields.size(); ++i) {
		if(*this->fields[i] != oth->fields[i]) return false;
	}
	return true;
}
} // namespace typesys
} // namespace sc
