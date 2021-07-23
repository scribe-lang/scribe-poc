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

	size_t src_id = vars.get_src_id(file);

	if(vars.src_exists(src_id)) {
		goto gen_struct;
	}

	if(!fs::read(file, data)) return false;

	if(!lex::tokenize(data, toks)) {
		err::show(stderr, data, file);
		return false;
	}

	if(!parser::parse(file, toks, vars)) {
		err::show(stderr, data, file);
		return false;
	}

gen_struct:
	VarSrc *src   = vars.get_src(src_id);
	VarLayer *top = src->get_top();
	if(!top) {
		err::set(line, col, "module '%s' contains no stack to get items from",
			 file.c_str());
		return false;
	}
	std::unordered_map<std::string, type_base_t *> &items = top->get_items();
	if(items.empty()) return true;
	type_struct_t *src_st = new type_struct_t(stmt, 0, 0, true, {}, {}, {});
	src_st->is_def	      = false;
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
	// stmt_fndef_t *fn = static_cast<stmt_fndef_t *>(stmt->get_parent_with_type(FNDEF));
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
	// for(auto &a : static_cast<type_func_t *>(fn->sig->vtyp)->args) {
	// 	if(a->info & VARIADIC) ++variadics;
	// }
	// printf("function contains %zu variadics\n", variadics);
	if(stmt->vtyp) delete stmt->vtyp;
	stmt->vtyp = vars.get_copy("i32", stmt->parent);
	return true;
}
} // namespace parser
} // namespace sc