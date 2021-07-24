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
///////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtBlock::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	std::vector<Stmt *> newstmts;
	for(auto &s : stmts) {
		newstmts.push_back(s->hidden_copy(copy_vtyp, copy_val, this));
	}
	Stmt *res = new StmtBlock(src_id, line, col, newstmts);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtType::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *newfn = fn ? fn->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	if(fn) {
		Stmt *res = new StmtType(src_id, line, col, fn);
		if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
		if(copy_val) res->value = value;
		return res;
	}
	Stmt *res = new StmtType(src_id, line, col, ptr, info, name, templates);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtSimple ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtSimple::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *res = new StmtSimple(src_id, line, col, val);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnCallInfo::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	std::vector<StmtType *> newtemplates;
	std::vector<Stmt *> newargs;
	for(auto &t : templates) {
		newtemplates.push_back(
		static_cast<StmtType *>(t->hidden_copy(copy_vtyp, copy_val, this)));
	}
	for(auto &a : args) {
		newargs.push_back(a->hidden_copy(copy_vtyp, copy_val, this));
	}
	Stmt *res = new StmtFnCallInfo(src_id, line, col, newtemplates, newargs);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtExpr::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *newlhs  = lhs ? lhs->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	Stmt *newrhs  = rhs ? rhs->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	StmtExpr *res = new StmtExpr(src_id, line, col, newlhs, oper, newrhs);
	if(or_blk)
		res->or_blk =
		static_cast<StmtBlock *>(or_blk->hidden_copy(copy_vtyp, copy_val, this));
	res->or_blk_var = or_blk_var;
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtVar::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	StmtType *newvtype =
	vtype ? static_cast<StmtType *>(vtype->hidden_copy(copy_vtyp, copy_val, this)) : nullptr;
	Stmt *newval = val ? val->hidden_copy(copy_vtyp, copy_val, this) : nullptr;

	Stmt *res = new StmtVar(src_id, line, col, name, newvtype, newval);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnSig::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	std::vector<StmtVar *> newparams;
	for(auto &p : params) {
		newparams.push_back(
		static_cast<StmtVar *>(p->hidden_copy(copy_vtyp, copy_val, this)));
	}
	StmtType *newrettype =
	rettype ? static_cast<StmtType *>(rettype->hidden_copy(copy_vtyp, copy_val, this))
		: nullptr;

	Stmt *res = new StmtFnSig(src_id, line, col, templates, newparams, newrettype, comptime);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnDef::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	StmtFnSig *newsig = static_cast<StmtFnSig *>(sig->hidden_copy(copy_vtyp, copy_val, this));
	StmtBlock *newblk =
	blk ? static_cast<StmtBlock *>(blk->hidden_copy(copy_vtyp, copy_val, this)) : nullptr;
	Stmt *res = new StmtFnDef(src_id, line, col, newsig, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtHeader ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtHeader::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *res = new StmtHeader(src_id, line, col, names, flags);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtLib //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtLib::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *res = new StmtLib(src_id, line, col, flags);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtExtern ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtExtern::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	StmtHeader *newheaders =
	headers ? static_cast<StmtHeader *>(headers->hidden_copy(copy_vtyp, copy_val, this))
		: nullptr;
	StmtLib *newlibs =
	libs ? static_cast<StmtLib *>(libs->hidden_copy(copy_vtyp, copy_val, this)) : nullptr;
	StmtFnSig *newsig = static_cast<StmtFnSig *>(sig->hidden_copy(copy_vtyp, copy_val, this));
	Stmt *res	  = new StmtExtern(src_id, line, col, fname, newheaders, newlibs, newsig);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtEnum ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtEnum::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	std::vector<StmtVar *> newitems;
	for(auto &i : items) {
		newitems.push_back(
		static_cast<StmtVar *>(i->hidden_copy(copy_vtyp, copy_val, this)));
	}
	Stmt *res = new StmtEnum(src_id, line, col, newitems);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtStruct //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtStruct::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	std::vector<StmtVar *> newfields;
	for(auto &f : fields) {
		newfields.push_back(
		static_cast<StmtVar *>(f->hidden_copy(copy_vtyp, copy_val, this)));
	}
	Stmt *res = new StmtStruct(src_id, line, col, decl, templates, newfields);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtVarDecl ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtVarDecl::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	std::vector<StmtVar *> newdecls;
	for(auto &d : decls) {
		newdecls.push_back(
		static_cast<StmtVar *>(d->hidden_copy(copy_vtyp, copy_val, this)));
	}
	Stmt *res = new StmtVarDecl(src_id, line, col, newdecls);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtCond::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	std::vector<cond_t> newconds;
	for(auto &c : conds) {
		cond_t nc{c.cond ? c.cond->hidden_copy(copy_vtyp, copy_val, this) : nullptr,
			  static_cast<StmtBlock *>(c.blk->hidden_copy(copy_vtyp, copy_val, this))};
		newconds.push_back(nc);
	}
	Stmt *res = new StmtCond(src_id, line, col, newconds);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtForIn ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtForIn::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *newin	  = in->hidden_copy(copy_vtyp, copy_val, this);
	StmtBlock *newblk = static_cast<StmtBlock *>(blk->hidden_copy(copy_vtyp, copy_val, this));
	Stmt *res	  = new StmtForIn(src_id, line, col, iter, newin, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFor::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *newinit	  = init ? init->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	Stmt *newcond	  = cond ? cond->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	Stmt *newincr	  = incr ? incr->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	StmtBlock *newblk = static_cast<StmtBlock *>(blk->hidden_copy(copy_vtyp, copy_val, this));
	Stmt *res	  = new StmtFor(src_id, line, col, newinit, newcond, newincr, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtWhile::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *newcond	  = cond ? cond->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	StmtBlock *newblk = static_cast<StmtBlock *>(blk->hidden_copy(copy_vtyp, copy_val, this));
	Stmt *res	  = new StmtWhile(src_id, line, col, newcond, newblk);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtRet::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *newval = val ? val->hidden_copy(copy_vtyp, copy_val, this) : nullptr;
	Stmt *res    = new StmtRet(src_id, line, col, newval);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtContinue /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtContinue::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *res = new StmtContinue(src_id, line, col);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtBreak::hidden_copy(const bool &copy_vtyp, const bool &copy_val, Stmt *par)
{
	Stmt *res = new StmtBreak(src_id, line, col);
	if(copy_vtyp) res->vtyp = vtyp ? vtyp->copy() : nullptr;
	if(copy_val) res->value = value;
	res->is_intrin = is_intrin;
	res->parent    = par;
	return res;
}
} // namespace parser
} // namespace sc