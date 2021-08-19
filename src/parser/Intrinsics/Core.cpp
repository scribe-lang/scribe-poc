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

#include "Error.hpp"
#include "FS.hpp"
#include "Parser.hpp"
#include "parser/TypeMgr.hpp"

namespace sc
{
namespace parser
{
INTRINSIC(import)
{
	size_t &line = base->line;
	size_t &col  = base->col;

	Stmt *topparentbase = base->getTopLevelParent();

	if(!topparentbase || topparentbase->stmt_type != BLOCK) {
		err::set(line, col, "import not in any code block (internal error)");
		return false;
	}

	StmtBlock *topparent = as<StmtBlock>(topparentbase);

	if(!args[0]->assignValue(types, values) || args[0]->value->type != VVEC) {
		err::set(line, col, "import must be a compile time computable string");
		return false;
	}
	std::string modname = values.getStringFromVec(args[0]->value);
	if(modname.empty()) {
		err::set(line, col, "no module provided");
		return false;
	}
	std::string file = modname + ".sc";

	if(!fs::exists(file)) {
		fprintf(stderr, "Error: file %s does not exist\n", file.c_str());
		return false;
	}
	file = fs::absPath(file);

	RAIIParser *parser = types.getParser();
	Module *mod	   = nullptr;
	StmtBlock *blk	   = nullptr;
	if(parser->hasModule(file)) {
		mod = parser->getModule(file);
		goto gen_import;
	}
	if(!parser->parse(file)) {
		err::set(line, col, "failed to parse source: %s", file.c_str());
		return false;
	}
	mod = parser->getModule(file);
	blk = as<StmtBlock>(mod->getParseTree());
	for(auto &s : blk->stmts) {
		if(!s) continue;
		s->parent = topparent;
	}
	topparent->stmts.push_back(nullptr);
	topparent->stmts.insert(topparent->stmts.end(), blk->stmts.begin(), blk->stmts.end());
	blk->stmts.clear();

gen_import:
	if(base->type) delete base->type;
	base->type = new TypeImport(base, 0, 0, mod->getID());
	return true;
}
INTRINSIC(as)
{
	printf("called as intrinsic\n");
	return true;
}
INTRINSIC(szof)
{
	printf("called szof intrinsic\n");
	return true;
}
INTRINSIC(typid)
{
	printf("called typid intrinsic\n");
	return true;
}
INTRINSIC(va_len)
{
	StmtFnDef *fn = static_cast<StmtFnDef *>(base->getParentWithType(FNDEF));
	if(!fn) {
		err::set(base->line, base->col,
			 "the function enclosing this intrinsic is not a variadic function");
		return false;
	}
	TypeVariadic *va = nullptr;
	for(auto &a : static_cast<TypeFunc *>(fn->sig->type)->args) {
		if(a->type == TVARIADIC) va = static_cast<TypeVariadic *>(a);
	}
	if(!va) {
		err::set(base->line, base->col,
			 "the enclosing function for va_len() must be a variadic");
		return false;
	}
	base->value = values.get((int64_t)va->args.size());
	return true;
}
INTRINSIC(array)
{
	// printf("call: %s\n", call->str().c_str());
	return true;
}
INTRINSIC(comptime_strlen)
{
	Value *mod = args[0]->value;
	if(!mod || !mod->has_data() || mod->type != VVEC) {
		err::set(base->line, base->col,
			 "comptime_strlen's argument must be a comptime string");
		return false;
	}
	base->value = values.get((int64_t)mod->v.size());
	return true;
}
INTRINSIC(subscr)
{
	Value *lhs = args[0]->value;
	Value *rhs = args[1]->value;
	if(!lhs || !lhs->has_data()) {
		err::set(base->line, base->col,
			 "comptime pointer subscript is only applicable on comptime pointer data");
		return false;
	}
	if(!rhs || !rhs->has_data()) {
		err::set(base->line, base->col,
			 "comptime pointer subscript must be a comptime integer value");
		return false;
	}
	if(lhs->v.size() <= rhs->i) {
		err::set(base->line, base->col, "attempted to index '%zu', total count is '%zu'",
			 (size_t)rhs->i, lhs->v.size());
		return false;
	}
	if(args[0]->type->info & REF) {
		base->value = lhs->v[rhs->i];
	} else {
		base->value = values.get(lhs->v[rhs->i]);
	}
	return true;
}
} // namespace parser
} // namespace sc