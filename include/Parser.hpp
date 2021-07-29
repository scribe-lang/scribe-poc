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

#ifndef PARSER_HPP
#define PARSER_HPP

#include <cstddef>

#include "Args.hpp"
#include "Lex.hpp"
#include "parser/Parse.hpp"
#include "parser/TypeMgr.hpp"
#include "parser/ValueMgr.hpp"

namespace sc
{
namespace parser
{
class RAIIParser
{
	args::ArgParser &args;

	// as new sources are imported, they'll be pushed back
	// this is NOT used to fetch current src_id or something
	std::vector<std::string> srcstack;

	std::unordered_map<size_t, std::string> srcdata;
	std::unordered_map<size_t, std::vector<lex::Lexeme>> srctoks;
	std::unordered_map<size_t, Stmt *> srcstmts;

	TypeMgr types;
	ValueMgr vals;

	bool add_src(const std::string &file_path, size_t &src_id);
	bool parse_src(const size_t &src_id);
	bool assign_type(const size_t &src_id);

public:
	RAIIParser(args::ArgParser &args);
	~RAIIParser();

	bool src_exists(const std::string &file_path);
	size_t get_srcid(const std::string &file_path);

	bool parse(const std::string &file_path);

	inline std::vector<lex::Lexeme> &get_toks(const size_t &src_id)
	{
		return srctoks[src_id];
	}
	inline Stmt *&get_ptree(const size_t &src_id)
	{
		return srcstmts[src_id];
	}

	inline TypeMgr &get_types()
	{
		return types;
	}
	inline ValueMgr &get_vals()
	{
		return vals;
	}

	// force ignores arg parser
	void show_toks(const bool &force);
	void show_ptrees(const bool &force);
};
} // namespace parser
} // namespace sc

#endif // PARSER_HPP