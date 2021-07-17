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

#include <cstdio>
#include <stdexcept>

#include "Args.hpp"
#include "Config.hpp"
#include "Error.hpp"
#include "FS.hpp"
#include "Lex.hpp"
#include "Parser.hpp"
#include "parser/VarMgr.hpp"

int main(int argc, char **argv)
{
	using namespace sc;
	args::ArgParser args(argc, (const char **)argv);
	args.add("version").set_short("v").set_long("version").set_help("prints program version");
	args.add("tokens").set_short("t").set_long("tokens").set_help("shows lexical tokens");
	args.add("parse").set_short("p").set_long("parse").set_help("shows AST");
	args.add("semantic").set_short("s").set_long("semantic").set_help("shows Semantic Tree");

	args.parse();

	if(args.has("help")) {
		args.print_help(stdout);
		return 0;
	}

	if(args.has("version")) {
		fprintf(stdout, "%s %d.%d.%d\nBuilt with %s\nOn %s\n", PROJECT, SCRIBE_MAJOR,
			SCRIBE_MINOR, SCRIBE_PATCH, BUILD_CXX_COMPILER, BUILD_DATE);
		return 0;
	}
	std::string file = args.get(1);
	if(file.empty()) {
		fprintf(stderr, "Error: no source provided to read from\n");
		return 1;
	}

	if(!fs::exists(file)) {
		fprintf(stderr, "Error: file %s does not exist\n", file.c_str());
		return 1;
	}
	file = fs::abs_path(file);

	std::string data;
	if(!fs::read(file, data)) return 1;

	std::vector<lex::Lexeme> toks;
	if(!lex::tokenize(data, toks)) {
		err::show(stderr, data, file);
		return 1;
	}
	if(args.has("tokens")) {
		printf("Tokens:\n");
		for(auto &l : toks) {
			printf("%s\n", l.str().c_str());
		}
	}

	parser::stmt_block_t *ptree = nullptr;
	if(!parser::parse(toks, ptree)) {
		err::show(stderr, data, file);
		return 1;
	}
	if(args.has("parse")) {
		printf("AST:\n");
		ptree->disp(false);
	}

	parser::VarMgr vartypes;
	vartypes.addsrc(file);
	vartypes.pushsrc(file);
	if(!ptree->assign_type(vartypes)) {
		err::show(stderr, data, file);
		return 1;
	}
	vartypes.popsrc();

	if(args.has("semantic")) {
		printf("Semantic Tree:\n");
		ptree->disp(false);
	}

	delete ptree;
	return 0;
fail:
	delete ptree;
	return 1;
}