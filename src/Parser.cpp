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

#include "Parser.hpp"

#include "Error.hpp"
#include "parser/VarMgr.hpp"

namespace sc
{
namespace parser
{
// on successful parse, returns true, and tree is allocated
bool parse(const std::string &file, std::vector<lex::Lexeme> &toks, VarMgr &vars)
{
	size_t src_id = vars.get_src_id(file);
	ParseHelper p(toks, src_id);
	stmt_block_t *tree = nullptr;
	if(!parse_block(p, tree, false)) return false;
	vars.manage_ptree(src_id, tree);
	tree->set_parent(nullptr);
	vars.addsrc(src_id);
	vars.pushsrc(src_id);
	if(!vars.init_typefns_called()) vars.init_typefns();
	if(!tree->assign_type(vars)) {
		err::set(tree->line, tree->col, "failed to assign types while parsing");
		return false;
	}
	vars.popsrc();
	return true;
}
} // namespace parser
} // namespace sc
