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

#include "parser/Intrinsics.hpp"

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
	size_t &line = stmt->line;
	size_t &col  = stmt->col;

	StmtExpr *fncall	= static_cast<StmtExpr *>(stmt);
	StmtFnCallInfo *arginfo = static_cast<StmtFnCallInfo *>(fncall->rhs);

	StmtSimple *mod		   = static_cast<StmtSimple *>(arginfo->args[0]);
	const std::string &modname = mod->val.data.s;
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
	// do here
	size_t src_id	   = 0;
	RAIIParser *parser = types.get_parser();
	if(!parser->add_src(file, src_id)) return false;
	if(!parser->parse(src_id)) return false;
	if(!parser->assign_type(src_id)) return false;
	if(!parser->const_fold(src_id)) return false;

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
	TypeStruct *src_st = new TypeStruct(stmt, 0, 0, true, {}, {}, {});
	src_st->is_def	   = false;
	for(auto &i : items) {
		src_st->add_field(i.first, i.second);
	}
	if(fncall->vtyp) delete fncall->vtyp;
	fncall->vtyp = src_st;
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
	printf("called va_len intrinsic\n");
	// StmtFnDef *fn = static_cast<StmtFnDef *>(stmt->get_parent_with_type(FNDEF));
	// if(!fn) {
	// 	err::set(stmt->line, stmt->col, "this function must be called within a function");
	// 	return false;
	// }
	// if(!fn->vtyp) {
	// 	err::set(stmt->line, stmt->col,
	// 		 "the function enclosing this intrinsic is not a variadic function");
	// 	return false;
	// }
	// size_t variadics = 0;
	// for(auto &a : static_cast<TypeFunc *>(fn->sig->vtyp)->args) {
	// 	if(a->info & VARIADIC) ++variadics;
	// }
	// printf("function contains %zu variadics\n", variadics);
	if(stmt->vtyp) delete stmt->vtyp;
	stmt->vtyp = types.get_copy("i32", stmt->parent);
	return true;
}
} // namespace parser
} // namespace sc