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

	if(!args[0]->assignValue(types, values) || args[0]->value->type != VSTR) {
		err::set(line, col, "import must be a compile time computable string");
		return false;
	}
	const std::string &modname = args[0]->value->s;
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
	if(parser->hasModule(file)) {
		goto gen_struct;
	}
	if(!parser->parse(file)) {
		err::set(line, col, "failed to parse source: %s", file.c_str());
		return false;
	}

gen_struct:
	SrcTypes *src	= types.getModule(file);
	LayerTypes *top = src->get_top();
	if(!top) {
		err::set(line, col, "module '%s' contains no stack to get items from",
			 file.c_str());
		return false;
	}
	std::unordered_map<std::string, Type *> &items = top->get_items();
	if(items.empty()) return true;
	TypeStruct *src_st = new TypeStruct(base, 0, 0, true, {}, {}, {});
	src_st->is_def	   = false;
	src_st->is_import  = true;
	for(auto &i : items) {
		src_st->add_field(i.first, i.second);
	}
	if(base->type) delete base->type;
	base->type = src_st;
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
	// TODO: set value here
	// original: = args->args[0]->type->val;
	Value *mod = nullptr;
	if(!mod || !mod->has_data() || mod->type != VSTR) {
		err::set(base->line, base->col,
			 "comptime_strlen's argument must be a comptime string");
		return false;
	}
	// TODO: set value here
	// original: base->type->val = types.get((int64_t)mod->s.size());
	return true;
}
} // namespace parser
} // namespace sc