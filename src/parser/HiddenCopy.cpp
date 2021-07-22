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

stmt_base_t *stmt_block_t::hidden_copy()
{
	std::vector<stmt_base_t *> newstmts;
	for(auto &s : stmts) {
		newstmts.push_back(s->hidden_copy());
	}
	stmt_base_t *res = new stmt_block_t(line, col, newstmts);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_type_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_type_t::hidden_copy()
{
	stmt_base_t *newfn = fn ? fn->hidden_copy() : nullptr;
	std::vector<stmt_base_t *> newcounts;
	for(auto &c : counts) newcounts.push_back(c->hidden_copy());
	if(fn) {
		stmt_base_t *res = new stmt_type_t(line, col, fn);
		res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
		return res;
	}
	stmt_base_t *res = new stmt_type_t(line, col, ptr, info, name, templates, newcounts);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_simple_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_simple_t::hidden_copy()
{
	stmt_base_t *res = new stmt_simple_t(line, col, val);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// stmt_fncallinfo_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fncallinfo_t::hidden_copy()
{
	std::vector<stmt_type_t *> newtemplates;
	std::vector<stmt_base_t *> newargs;
	for(auto &t : templates) {
		newtemplates.push_back(static_cast<stmt_type_t *>(t->hidden_copy()));
	}
	for(auto &a : args) {
		newargs.push_back(a->hidden_copy());
	}
	stmt_base_t *res = new stmt_fncallinfo_t(line, col, newtemplates, newargs);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_expr_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_expr_t::hidden_copy()
{
	stmt_base_t *newlhs = lhs ? lhs->hidden_copy() : nullptr;
	stmt_base_t *newrhs = rhs ? rhs->hidden_copy() : nullptr;
	stmt_expr_t *res    = new stmt_expr_t(line, col, newlhs, oper, newrhs);
	if(or_blk) res->or_blk = static_cast<stmt_block_t *>(or_blk->hidden_copy());
	res->or_blk_var = or_blk_var;
	res->vtyp	= vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	= is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_var_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_var_t::hidden_copy()
{
	stmt_type_t *newvtype = vtype ? static_cast<stmt_type_t *>(vtype->hidden_copy()) : nullptr;
	stmt_base_t *newval   = val ? val->hidden_copy() : nullptr;

	stmt_base_t *res = new stmt_var_t(line, col, name, newvtype, newval);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fnsig_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fnsig_t::hidden_copy()
{
	std::vector<stmt_var_t *> newparams;
	for(auto &p : params) {
		newparams.push_back(static_cast<stmt_var_t *>(p->hidden_copy()));
	}
	stmt_type_t *newrettype =
	rettype ? static_cast<stmt_type_t *>(rettype->hidden_copy()) : nullptr;

	stmt_base_t *res = new stmt_fnsig_t(line, col, templates, newparams, newrettype, comptime);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_fndef_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_fndef_t::hidden_copy()
{
	stmt_fnsig_t *newsig = static_cast<stmt_fnsig_t *>(sig->hidden_copy());
	stmt_block_t *newblk = blk ? static_cast<stmt_block_t *>(blk->hidden_copy()) : nullptr;
	stmt_base_t *res     = new stmt_fndef_t(line, col, newsig, newblk);
	res->vtyp	     = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	     = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_header_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_header_t::hidden_copy()
{
	stmt_base_t *res = new stmt_header_t(line, col, names, flags);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_lib_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_lib_t::hidden_copy()
{
	stmt_base_t *res = new stmt_lib_t(line, col, flags);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_extern_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_extern_t::hidden_copy()
{
	stmt_header_t *newheaders =
	headers ? static_cast<stmt_header_t *>(headers->hidden_copy()) : nullptr;
	stmt_lib_t *newlibs  = libs ? static_cast<stmt_lib_t *>(libs->hidden_copy()) : nullptr;
	stmt_fnsig_t *newsig = static_cast<stmt_fnsig_t *>(sig->hidden_copy());
	stmt_base_t *res     = new stmt_extern_t(line, col, fname, newheaders, newlibs, newsig);
	res->vtyp	     = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	     = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_enumdef_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_enumdef_t::hidden_copy()
{
	std::vector<stmt_var_t *> newitems;
	for(auto &i : items) {
		newitems.push_back(static_cast<stmt_var_t *>(i->hidden_copy()));
	}
	stmt_base_t *res = new stmt_enumdef_t(line, col, newitems);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_struct_t //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_struct_t::hidden_copy()
{
	std::vector<stmt_var_t *> newfields;
	for(auto &f : fields) {
		newfields.push_back(static_cast<stmt_var_t *>(f->hidden_copy()));
	}
	stmt_base_t *res = new stmt_struct_t(line, col, decl, templates, newfields);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// stmt_vardecl_t ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_vardecl_t::hidden_copy()
{
	std::vector<stmt_var_t *> newdecls;
	for(auto &d : decls) {
		newdecls.push_back(static_cast<stmt_var_t *>(d->hidden_copy()));
	}
	stmt_base_t *res = new stmt_vardecl_t(line, col, newdecls);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cond_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_cond_t::hidden_copy()
{
	std::vector<cond_t> newconds;
	for(auto &c : conds) {
		cond_t nc{c.cond ? c.cond->hidden_copy() : nullptr,
			  static_cast<stmt_block_t *>(c.blk->hidden_copy())};
		newconds.push_back(nc);
	}
	stmt_base_t *res = new stmt_cond_t(line, col, newconds);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// stmt_forin_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_forin_t::hidden_copy()
{
	stmt_base_t *newin   = in->hidden_copy();
	stmt_block_t *newblk = static_cast<stmt_block_t *>(blk->hidden_copy());
	stmt_base_t *res     = new stmt_forin_t(line, col, iter, newin, newblk);
	res->vtyp	     = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	     = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_for_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_for_t::hidden_copy()
{
	stmt_base_t *newinit = init ? init->hidden_copy() : nullptr;
	stmt_base_t *newcond = cond ? cond->hidden_copy() : nullptr;
	stmt_base_t *newincr = incr ? incr->hidden_copy() : nullptr;
	stmt_block_t *newblk = static_cast<stmt_block_t *>(blk->hidden_copy());
	stmt_base_t *res     = new stmt_for_t(line, col, newinit, newcond, newincr, newblk);
	res->vtyp	     = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	     = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_while_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_while_t::hidden_copy()
{
	stmt_base_t *newcond = cond ? cond->hidden_copy() : nullptr;
	stmt_block_t *newblk = static_cast<stmt_block_t *>(blk->hidden_copy());
	stmt_base_t *res     = new stmt_while_t(line, col, newcond, newblk);
	res->vtyp	     = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	     = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_ret_t //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_ret_t::hidden_copy()
{
	stmt_base_t *newval = val ? val->hidden_copy() : nullptr;
	stmt_base_t *res    = new stmt_ret_t(line, col, newval);
	res->vtyp	    = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	    = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_cont_t /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_cont_t::hidden_copy()
{
	stmt_base_t *res = new stmt_cont_t(line, col);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// stmt_break_t ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

stmt_base_t *stmt_break_t::hidden_copy()
{
	stmt_base_t *res = new stmt_break_t(line, col);
	res->vtyp	 = vtyp ? vtyp->copy() : nullptr;
	res->is_intrin	 = is_intrin;
	return res;
}
} // namespace parser
} // namespace sc