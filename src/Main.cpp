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

	parser::RAIIParser parser(args);
	size_t src_id = 0;
	if(!parser.add_src(file, src_id)) return 1;
	if(!parser.parse(src_id)) return 1;
	if(!parser.assign_type(src_id)) return 1;
	if(!parser.const_fold(src_id)) return 1;

	parser.show_toks(false);
	parser.show_ptrees(false);
	return 0;
}