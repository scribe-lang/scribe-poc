/*
	MIT License

	Copyright (c) 2021 Scribe Language Repositories

	Permission is hereby granted, free of charge, to any person obtaining a
	hidden_copy of this software and associated documentation files (the "Software"), to
	deal in the Software without restriction, including without limitation the
	rights to use, hidden_copy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#include "parser/Stmts.hpp"
#include "parser/Type.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_block_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_block_t::hidden_copy(const bool &copy_vtyp)
{
	std::vector<stmt_base_t *> newstmts;
	for(auto &s : stmts) {
		newstmts.push_back(s->hidden_copy(copy_vtyp));
	}
	stmt_base_t *res = new stmt_block_t(src_id, line, col, newstmts);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_type_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *newfn = fn ? fn->hidden_copy(copy_vtyp) : nullptr;
	std::vector<stmt_base_t *> newcounts;
	if(fn) {
		stmt_base_t *res = new stmt_type_t(src_id, line, col, fn);
		if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
		return res;
	}
	stmt_base_t *res = new stmt_type_t(src_id, line, col, ptr, info, name, templates);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_simple_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *res = new stmt_simple_t(src_id, line, col, val);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// stmt_fncallinfo_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fncallinfo_t::hidden_copy(const bool &copy_vtyp)
{
	std::vector<stmt_type_t *> newtemplates;
	std::vector<stmt_base_t *> newargs;
	for(auto &t : templates) {
		newtemplates.push_back(static_cast<stmt_type_t *>(t->hidden_copy(copy_vtyp)));
	}
	for(auto &a : args) {
		newargs.push_back(a->hidden_copy(copy_vtyp));
	}
	stmt_base_t *res = new stmt_fncallinfo_t(src_id, line, col, newtemplates, newargs);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_expr_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *newlhs = lhs ? lhs->hidden_copy(copy_vtyp) : nullptr;
	stmt_base_t *newrhs = rhs ? rhs->hidden_copy(copy_vtyp) : nullptr;
	stmt_expr_t *res    = new stmt_expr_t(src_id, line, col, newlhs, oper, newrhs);
	if(or_blk) res->or_blk = static_cast<stmt_block_t *>(or_blk->hidden_copy(copy_vtyp));
	res->or_blk_var = or_blk_var;
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_var_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_var_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_type_t *newvtype =
	vtype ? static_cast<stmt_type_t *>(vtype->hidden_copy(copy_vtyp)) : nullptr;
	stmt_base_t *newval = val ? val->hidden_copy(copy_vtyp) : nullptr;

	stmt_base_t *res = new stmt_var_t(src_id, line, col, name, newvtype, newval);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fnsig_t::hidden_copy(const bool &copy_vtyp)
{
	std::vector<stmt_var_t *> newparams;
	for(auto &p : params) {
		newparams.push_back(static_cast<stmt_var_t *>(p->hidden_copy(copy_vtyp)));
	}
	stmt_type_t *newrettype =
	rettype ? static_cast<stmt_type_t *>(rettype->hidden_copy(copy_vtyp)) : nullptr;

	stmt_base_t *res =
	new stmt_fnsig_t(src_id, line, col, templates, newparams, newrettype, comptime);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fndef_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_fnsig_t *newsig = static_cast<stmt_fnsig_t *>(sig->hidden_copy(copy_vtyp));
	stmt_block_t *newblk =
	blk ? static_cast<stmt_block_t *>(blk->hidden_copy(copy_vtyp)) : nullptr;
	stmt_base_t *res = new stmt_fndef_t(src_id, line, col, newsig, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_header_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *res = new stmt_header_t(src_id, line, col, names, flags);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_lib_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *res = new stmt_lib_t(src_id, line, col, flags);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_extern_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_header_t *newheaders =
	headers ? static_cast<stmt_header_t *>(headers->hidden_copy(copy_vtyp)) : nullptr;
	stmt_lib_t *newlibs =
	libs ? static_cast<stmt_lib_t *>(libs->hidden_copy(copy_vtyp)) : nullptr;
	stmt_fnsig_t *newsig = static_cast<stmt_fnsig_t *>(sig->hidden_copy(copy_vtyp));
	stmt_base_t *res = new stmt_extern_t(src_id, line, col, fname, newheaders, newlibs, newsig);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_enumdef_t::hidden_copy(const bool &copy_vtyp)
{
	std::vector<stmt_var_t *> newitems;
	for(auto &i : items) {
		newitems.push_back(static_cast<stmt_var_t *>(i->hidden_copy(copy_vtyp)));
	}
	stmt_base_t *res = new stmt_enumdef_t(src_id, line, col, newitems);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_struct_t::hidden_copy(const bool &copy_vtyp)
{
	std::vector<stmt_var_t *> newfields;
	for(auto &f : fields) {
		newfields.push_back(static_cast<stmt_var_t *>(f->hidden_copy(copy_vtyp)));
	}
	stmt_base_t *res = new stmt_struct_t(src_id, line, col, decl, templates, newfields);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_vardecl_t::hidden_copy(const bool &copy_vtyp)
{
	std::vector<stmt_var_t *> newdecls;
	for(auto &d : decls) {
		newdecls.push_back(static_cast<stmt_var_t *>(d->hidden_copy(copy_vtyp)));
	}
	stmt_base_t *res = new stmt_vardecl_t(src_id, line, col, newdecls);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_cond_t::hidden_copy(const bool &copy_vtyp)
{
	std::vector<cond_t> newconds;
	for(auto &c : conds) {
		cond_t nc{c.cond ? c.cond->hidden_copy(copy_vtyp) : nullptr,
			  static_cast<stmt_block_t *>(c.blk->hidden_copy(copy_vtyp))};
		newconds.push_back(nc);
	}
	stmt_base_t *res = new stmt_cond_t(src_id, line, col, newconds);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_forin_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *newin   = in->hidden_copy(copy_vtyp);
	stmt_block_t *newblk = static_cast<stmt_block_t *>(blk->hidden_copy(copy_vtyp));
	stmt_base_t *res     = new stmt_forin_t(src_id, line, col, iter, newin, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_for_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *newinit = init ? init->hidden_copy(copy_vtyp) : nullptr;
	stmt_base_t *newcond = cond ? cond->hidden_copy(copy_vtyp) : nullptr;
	stmt_base_t *newincr = incr ? incr->hidden_copy(copy_vtyp) : nullptr;
	stmt_block_t *newblk = static_cast<stmt_block_t *>(blk->hidden_copy(copy_vtyp));
	stmt_base_t *res     = new stmt_for_t(src_id, line, col, newinit, newcond, newincr, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_while_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *newcond = cond ? cond->hidden_copy(copy_vtyp) : nullptr;
	stmt_block_t *newblk = static_cast<stmt_block_t *>(blk->hidden_copy(copy_vtyp));
	stmt_base_t *res     = new stmt_while_t(src_id, line, col, newcond, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_ret_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *newval = val ? val->hidden_copy(copy_vtyp) : nullptr;
	stmt_base_t *res    = new stmt_ret_t(src_id, line, col, newval);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_cont_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *res = new stmt_cont_t(src_id, line, col);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_break_t::hidden_copy(const bool &copy_vtyp)
{
	stmt_base_t *res = new stmt_break_t(src_id, line, col);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin = is_intrin;
	return res;
}
} // namespace parser
} // namespace sc