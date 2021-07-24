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
#include "FS.hpp"
#include "parser/TypeMgr.hpp"
#include "parser/ValueMgr.hpp"

namespace sc
{
namespace parser
{
RAIIParser::RAIIParser(args::ArgParser &args) : args(args), types(this), vals(this) {}
RAIIParser::~RAIIParser()
{
	for(auto &s : srcstmts) delete s.second;
}

bool RAIIParser::add_src(const std::string &file_path, size_t &src_id)
{
	for(size_t i = 0; i < srcstack.size(); ++i) {
		if(srcstack[i] == file_path) return i;
	}

	src_id = srcstack.size();

	srcdata[src_id]	  = {};
	std::string &data = srcdata[src_id];
	if(!fs::read(file_path, data)) {
		srcdata.erase(src_id);
		return false;
	}

	srctoks[src_id]		       = {};
	std::vector<lex::Lexeme> &toks = srctoks[src_id];
	if(!lex::tokenize(data, toks)) {
		err::show(stderr, data, file_path);
		srctoks.erase(src_id);
		return false;
	}
	srcstack.push_back(file_path);
	return true;
}

bool RAIIParser::parse(const size_t &src_id)
{
	ParseHelper p(srctoks[src_id], src_id);
	StmtBlock *tree = nullptr;
	if(!parse_block(p, tree, false)) {
		err::show(stderr, srcdata[src_id], srcstack[src_id]);
		return false;
	}
	tree->set_parent(nullptr);
	srcstmts[src_id] = tree;
	return true;
}
bool RAIIParser::assign_type(const size_t &src_id)
{
	types.addsrc(src_id);
	types.pushsrc(src_id);
	if(!types.init_typefns_called()) types.init_typefns();
	Stmt *&tree = srcstmts[src_id];
	if(!tree->assign_type(types)) {
		err::set(tree->line, tree->col, "failed to assign types while parsing");
		err::show(stderr, srcdata[src_id], srcstack[src_id]);
		return false;
	}
	types.popsrc();
	return true;
}
bool RAIIParser::const_fold(const size_t &src_id)
{
	Stmt *&tree = srcstmts[src_id];
	vals.add_src(src_id);
	vals.push_src(src_id);
	if(!tree->const_fold(types, vals)) {
		err::set(tree->line, tree->col, "failed to const fold while parsing");
		err::show(stderr, srcdata[src_id], srcstack[src_id]);
		return false;
	}
	vals.pop_src();
	return true;
}
void RAIIParser::show_toks(const bool &force)
{
	if(!args.has("tokens") && !force) return;

	printf("-------------------------------------------------- Token(s) "
	       "--------------------------------------------------\n");
	size_t i = srcstack.size() - 1;
	for(auto src = srcstack.rbegin(); src != srcstack.rend(); ++src) {
		printf("\n\nSource: %s\n", src->c_str());
		auto &toks = srctoks[i--];
		for(auto &t : toks) {
			printf("%s\n", t.str().c_str());
		}
	}
}
void RAIIParser::show_ptrees(const bool &force)
{
	if(!args.has("parse") && !args.has("semantic") && !force) return;

	printf("-------------------------------------------------- Parse Tree(s) "
	       "--------------------------------------------------\n");
	size_t i = srcstack.size() - 1;
	for(auto src = srcstack.rbegin(); src != srcstack.rend(); ++src) {
		printf("\n\nSource: %s\n", src->c_str());
		auto &tree = srcstmts[i--];
		tree->disp(false);
	}
}
} // namespace parser
} // namespace sc
