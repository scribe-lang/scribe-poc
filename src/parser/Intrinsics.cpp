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
#include "parser/VarMgr.hpp"

namespace sc
{
namespace parser
{
INTRINSIC(import)
{
	size_t &line = stmt->line;
	size_t &col  = stmt->col;

	stmt_expr_t *fncall	   = static_cast<stmt_expr_t *>(stmt);
	stmt_fncallinfo_t *arginfo = static_cast<stmt_fncallinfo_t *>(fncall->rhs);

	stmt_simple_t *mod	   = static_cast<stmt_simple_t *>(arginfo->args[0]);
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
	std::string data;
	std::vector<lex::Lexeme> toks;
	parser::stmt_block_t *ptree = nullptr;

	if(vars.src_exists(file)) {
		goto gen_struct;
	}

	if(!fs::read(file, data)) return false;

	if(!lex::tokenize(data, toks)) {
		err::show(stderr, data, file);
		return false;
	}

	if(!parser::parse(toks, ptree)) {
		err::show(stderr, data, file);
		return false;
	}

	vars.addsrc(file);
	vars.pushsrc(file);
	if(!ptree->assign_type(vars)) {
		err::show(stderr, data, file);
		return false;
	}
	vars.popsrc();

gen_struct:
	VarSrc *src   = vars.get_src(file);
	VarLayer *top = src->get_top();
	if(!top) {
		err::set(line, col, "module '%s' contains no stack to get items from",
			 file.c_str());
		return false;
	}
	std::unordered_map<std::string, type_base_t *> &items = top->get_items();
	if(items.empty()) return true;
	type_struct_t *src_st = new type_struct_t(stmt, 0, 0, true, {}, {}, {});
	for(auto &i : items) {
		src_st->add_field(i.first, i.second);
	}
	if(fncall->vtyp) delete fncall->vtyp;
	fncall->vtyp = src_st;
	delete ptree;
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
} // namespace parser
} // namespace sc