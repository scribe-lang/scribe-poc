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
#include "parser/TypeMgr.hpp"
#include "parser/ValueMgr.hpp"

namespace sc
{
namespace parser
{
struct Stmt;

class Module
{
	std::string id;
	std::string path;
	std::string code;
	std::vector<lex::Lexeme> tokens;
	Stmt *ptree;

public:
	Module(const std::string &id, const std::string &path, const std::string &code);
	~Module();

	bool tokenize();
	bool parseTokens();
	bool assignType(TypeMgr &types);
	// performs rearrangement of ptree to make all imports in order
	void rearrangeParseTree();
	void cleanupParseTree();

	const std::string &getID();
	const std::string &getPath();
	const std::string &getCode();
	const std::vector<lex::Lexeme> &getTokens();
	Stmt *&getParseTree();

	void dumpTokens();
	void dumpParseTree();
};

class RAIIParser
{
	args::ArgParser &args;

	TypeMgr types;
	ValueMgr values;

	// as new sources are imported, they'll be pushed back
	// the reverse iteration of this list will give the order of imports
	std::vector<std::string> modulestack;

	std::unordered_map<std::string, Module *> modules;

	Module *addModule(const std::string &path);

public:
	RAIIParser(args::ArgParser &args);
	~RAIIParser();

	bool hasModule(const std::string &path);
	Module *getModule(const std::string &path);
	const std::vector<std::string> &getModuleStack();

	bool parse(const std::string &path);
	void cleanupParseTrees();

	args::ArgParser &getCommandArgs();

	ValueMgr &getValueMgr();

	// force ignores arg parser
	void dumpTokens(const bool &force);
	void dumpParseTree(const bool &force);
};
} // namespace parser
} // namespace sc

#endif // PARSER_HPP