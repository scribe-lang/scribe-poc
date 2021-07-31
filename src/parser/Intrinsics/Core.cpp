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

#define HAS_VALID_VAL(vtyp) (vtyp->val && vtyp->val->has_data())

#define VERIFY_VALS_BINOP()                                                     \
	if(!HAS_VALID_VAL(call->vtyp) || !HAS_VALID_VAL(args->args[0]->vtyp)) { \
		call->vtyp->val = types.get(VUNKNOWN);                          \
		return true;                                                    \
	}

namespace sc
{
namespace parser
{
INTRINSIC(import)
{
	size_t &line = base->line;
	size_t &col  = base->col;

	Value *mod = args->args[0]->vtyp->val;
	if(!mod || !mod->has_data() || mod->type != VSTR) {
		err::set(line, col, "import's argument must be a comptime string");
		return false;
	}
	const std::string &modname = mod->s;
	if(modname.empty()) {
		err::set(line, col, "no module provided");
		return false;
	}
	std::string file = modname + ".sc";

	if(!fs::exists(file)) {
		fprintf(stderr, "Error: file %s does not exist\n", file.c_str());
		return false;
	}
	file = fs::abs_path(file);

	RAIIParser *parser = types.get_parser();
	size_t src_id	   = 0;
	if(parser->src_exists(file)) {
		src_id = parser->get_srcid(file);
		goto gen_struct;
	}
	if(!parser->parse(file)) {
		err::set(line, col, "failed to parse source: %s", file.c_str());
		return false;
	}
	src_id = parser->get_srcid(file);

gen_struct:
	SrcTypes *src	= types.get_src(src_id);
	LayerTypes *top = src->get_top();
	if(!top) {
		err::set(line, col, "module '%s' contains no stack to get items from",
			 file.c_str());
		return false;
	}
	std::unordered_map<std::string, Type *> &items = top->get_items();
	if(items.empty()) return true;
	TypeStruct *src_st = new TypeStruct(base, 0, 0, nullptr, true, {}, {}, {});
	src_st->is_def	   = false;
	for(auto &i : items) {
		src_st->add_field(i.first, i.second);
	}
	if(base->vtyp) delete base->vtyp;
	base->vtyp = src_st;
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
	StmtFnDef *fn = static_cast<StmtFnDef *>(base->get_parent_with_type(FNDEF));
	if(!fn) {
		err::set(base->line, base->col,
			 "the function enclosing this intrinsic is not a variadic function");
		return false;
	}
	TypeVariadic *va = nullptr;
	for(auto &a : static_cast<TypeFunc *>(fn->sig->vtyp)->args) {
		if(a->type == TVARIADIC) va = static_cast<TypeVariadic *>(a);
	}
	if(!va) {
		err::set(base->line, base->col,
			 "the enclosing function for va_len() must be a variadic");
		return false;
	}
	base->vtyp->val = types.get((int64_t)va->args.size());
	return true;
}
INTRINSIC(array)
{
	printf("call: %s\n", call->str().c_str());
	return true;
}
INTRINSIC(comptime_strlen)
{
	Value *mod = args->args[0]->vtyp->val;
	if(!mod || !mod->has_data() || mod->type != VSTR) {
		err::set(base->line, base->col,
			 "comptime_strlen's argument must be a comptime string");
		return false;
	}
	base->vtyp->val = types.get((int64_t)mod->s.size());
	return true;
}
} // namespace parser
} // namespace sc