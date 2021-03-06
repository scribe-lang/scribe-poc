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

#include <unistd.h>

#include "Error.hpp"
#include "FS.hpp"
#include "parser/Cleanup.hpp"
#include "parser/Parse.hpp"
#include "parser/ParseHelper.hpp"
#include "Utils.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// Module ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Module::Module(const std::string &id, const std::string &path, const std::string &code)
	: id(id), path(path), code(code), tokens(), ptree(nullptr)
{}
Module::~Module()
{
	if(ptree) delete ptree;
}
bool Module::tokenize()
{
	if(!lex::tokenize(code, tokens)) {
		err::show(stderr);
		return false;
	}
	return true;
}
bool Module::parseTokens()
{
	ParseHelper p(this, tokens);
	if(!parse_block(p, (StmtBlock *&)ptree, false)) {
		err::show(stderr);
		return false;
	}
	ptree->setParent(nullptr);
	return true;
}
bool Module::assignType(TypeMgr &types)
{
	if(!types.initTypeFuncsCalled()) types.initTypeFuncs();
	if(!ptree->assignType(types)) {
		err::set(ptree, "failed to assign types while parsing");
		err::show(stderr);
		return false;
	}
	return true;
}
void Module::rearrangeParseTree()
{
	if(ptree->stmt_type != BLOCK) {
		return;
	}
	StmtBlock *tree		   = as<StmtBlock>(ptree);
	std::vector<Stmt *> &stmts = tree->stmts;
	std::vector<Stmt *> newstmts;
	bool first_done = false;
	for(auto it = stmts.begin(); it != stmts.end();) {
		if(!*it) {
			if(!first_done) first_done = true;
			it = stmts.erase(it);
			continue;
		}
		if(!first_done) {
			++it;
			continue;
		}
		newstmts.push_back(*it);
		it = stmts.erase(it);
	}
	if(newstmts.empty()) return;
	newstmts.insert(newstmts.end(), stmts.begin(), stmts.end());
	tree->stmts = newstmts;
}
void Module::cleanupParseTree()
{
	cleanup(ptree, &ptree);
}
const std::string &Module::getID()
{
	return id;
}
const std::string &Module::getPath()
{
	return path;
}
const std::string &Module::getCode()
{
	return code;
}
const std::vector<lex::Lexeme> &Module::getTokens()
{
	return tokens;
}
Stmt *&Module::getParseTree()
{
	return ptree;
}
void Module::dumpTokens()
{
	printf("Source: %s\n", path.c_str());
	for(auto &t : tokens) {
		printf("%s\n", t.str().c_str());
	}
}
void Module::dumpParseTree()
{
	printf("Source: %s\n", path.c_str());
	ptree->disp(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// RAIIParser /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

RAIIParser::RAIIParser(args::ArgParser &args) : args(args), types(this), values(this) {}
RAIIParser::~RAIIParser()
{
	for(auto &m : modules) delete m.second;
}

Module *RAIIParser::addModule(const std::string &path)
{
	auto res = modules.find(path);
	if(res != modules.end()) return res->second;

	std::string code;
	if(!fs::read(path, code)) {
		return nullptr;
	}

	Module *mod = new Module(std::to_string(modulestack.size()), path, code);
	Pointer<Module> mptr(mod);

	modulestack.push_back(path);
	err::pushModule(mod);

	if(!mod->tokenize() || !mod->parseTokens() || !mod->assignType(types)) {
		err::popModule();
		modulestack.pop_back();
		return nullptr;
	}
	mod->rearrangeParseTree();

	err::popModule();
	if(modulestack.size() > 1) modulestack.pop_back();

	mptr.unset();
	modules[path] = mod;
	return mod;
}
bool RAIIParser::hasModule(const std::string &path)
{
	return modules.find(path) != modules.end();
}
Module *RAIIParser::getModule(const std::string &path)
{
	auto res = modules.find(path);
	if(res != modules.end()) return res->second;
	return nullptr;
}
const std::vector<std::string> &RAIIParser::getModuleStack()
{
	return modulestack;
}
bool RAIIParser::parse(const std::string &path)
{
	if(hasModule(path)) {
		fprintf(stderr, "cannot parse an existing source: %s\n", path.c_str());
		return false;
	}

	std::string wd = fs::cwd();
	fs::scwd(fs::parentDir(path));
	size_t src_id = 0;
	if(!addModule(path)) return false;
	fs::scwd(wd);
	return true;
}
void RAIIParser::cleanupParseTrees()
{
	for(auto file = modulestack.rbegin(); file != modulestack.rend(); ++file) {
		modules[*file]->cleanupParseTree();
	}
}
args::ArgParser &RAIIParser::getCommandArgs()
{
	return args;
}
ValueMgr &RAIIParser::getValueMgr()
{
	return values;
}
void RAIIParser::dumpTokens(const bool &force)
{
	if(!args.has("tokens") && !force) return;

	printf("-------------------------------------------------- Token(s) "
	       "--------------------------------------------------\n");
	for(auto file = modulestack.rbegin(); file != modulestack.rend(); ++file) {
		printf("\n\n");
		modules[*file]->dumpTokens();
	}
}
void RAIIParser::dumpParseTree(const bool &force)
{
	if(!args.has("parse") && !args.has("semantic") && !force) return;

	printf("-------------------------------------------------- Parse Tree(s) "
	       "--------------------------------------------------\n");
	for(auto file = modulestack.rbegin(); file != modulestack.rend(); ++file) {
		printf("\n\n");
		modules[*file]->dumpParseTree();
	}
}
} // namespace parser
} // namespace sc
