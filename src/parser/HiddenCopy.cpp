/*
	MIT License

	Copyright (c) 2021 Scribe Language Repositories

	Permission is hereby granted, free of charge, to any person obtaining a
	hiddenCopy of this software and associated documentation files (the "Software"), to
	deal in the Software without restriction, including without limitation the
	rights to use, hiddenCopy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#include "parser/Stmts.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtBlock::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	std::vector<Stmt *> newstmts;
	for(auto &s : stmts) {
		newstmts.push_back(s->hiddenCopy(copy_type, copy_val, this));
	}
	StmtBlock *res	    = new StmtBlock(mod, line, col, newstmts);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtType::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	if(fn) {
		Stmt *newfn	    = fn->hiddenCopy(copy_type, copy_val, this);
		StmtType *res	    = new StmtType(mod, line, col, newfn);
		res->parent	    = par;
		res->is_specialized = is_specialized;
		res->is_comptime    = is_comptime;
		return res;
	}
	StmtType *res	    = new StmtType(mod, line, col, ptr, info, name, templates);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtSimple /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtSimple::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtSimple *res	    = new StmtSimple(mod, line, col, val);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtFnCallInfo ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnCallInfo::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	std::vector<StmtType *> newtemplates;
	std::vector<Stmt *> newargs;
	for(auto &t : templates) {
		newtemplates.push_back(
		static_cast<StmtType *>(t->hiddenCopy(copy_type, copy_val, this)));
	}
	for(auto &a : args) {
		newargs.push_back(a->hiddenCopy(copy_type, copy_val, this));
	}
	StmtFnCallInfo *res = new StmtFnCallInfo(mod, line, col, newtemplates, newargs);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtExpr::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	Stmt *newlhs  = lhs ? lhs->hiddenCopy(copy_type, copy_val, this) : nullptr;
	Stmt *newrhs  = rhs ? rhs->hiddenCopy(copy_type, copy_val, this) : nullptr;
	StmtExpr *res = new StmtExpr(mod, line, col, newlhs, oper, newrhs);
	if(or_blk)
		res->or_blk =
		static_cast<StmtBlock *>(or_blk->hiddenCopy(copy_type, copy_val, this));
	res->or_blk_var		= or_blk_var;
	res->parent		= par;
	res->is_parse_intrinsic = is_parse_intrinsic;
	res->is_specialized	= is_specialized;
	res->is_comptime	= is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtVar::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtType *newvtype =
	vtype ? static_cast<StmtType *>(vtype->hiddenCopy(copy_type, copy_val, this)) : nullptr;
	Stmt *newval = val ? val->hiddenCopy(copy_type, copy_val, this) : nullptr;

	StmtVar *res	    = new StmtVar(mod, line, col, name, newvtype, newval);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnSig::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	std::vector<StmtVar *> newargs;
	for(auto &p : args) {
		newargs.push_back(static_cast<StmtVar *>(p->hiddenCopy(copy_type, copy_val, this)));
	}
	StmtType *newret =
	rettype ? static_cast<StmtType *>(rettype->hiddenCopy(copy_type, copy_val, this)) : nullptr;
	StmtFnSig *res = new StmtFnSig(mod, line, col, templates, newargs, newret, has_variadic);
	res->parent    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnDef::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtFnSig *newsig = static_cast<StmtFnSig *>(sig->hiddenCopy(copy_type, copy_val, this));
	StmtBlock *newblk =
	blk ? static_cast<StmtBlock *>(blk->hiddenCopy(copy_type, copy_val, this)) : nullptr;
	StmtFnDef *res	    = new StmtFnDef(mod, line, col, newsig, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtHeader /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtHeader::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtHeader *res	    = new StmtHeader(mod, line, col, names, flags);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtLib ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtLib::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtLib *res	    = new StmtLib(mod, line, col, flags);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtExtern /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtExtern::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtHeader *newheaders =
	headers ? static_cast<StmtHeader *>(headers->hiddenCopy(copy_type, copy_val, this))
		: nullptr;
	StmtLib *newlibs =
	libs ? static_cast<StmtLib *>(libs->hiddenCopy(copy_type, copy_val, this)) : nullptr;
	StmtFnSig *newsig   = static_cast<StmtFnSig *>(sig->hiddenCopy(copy_type, copy_val, this));
	StmtExtern *res	    = new StmtExtern(mod, line, col, fname, newheaders, newlibs, newsig);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtEnum //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtEnum::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtEnum *res	    = new StmtEnum(mod, line, col, items);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtStruct /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtStruct::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	std::vector<StmtVar *> newfields;
	for(auto &f : fields) {
		newfields.push_back(
		static_cast<StmtVar *>(f->hiddenCopy(copy_type, copy_val, this)));
	}
	StmtStruct *res	    = new StmtStruct(mod, line, col, decl, templates, newfields);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtVarDecl /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtVarDecl::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	std::vector<StmtVar *> newdecls;
	for(auto &d : decls) {
		newdecls.push_back(
		static_cast<StmtVar *>(d->hiddenCopy(copy_type, copy_val, this)));
	}
	StmtVarDecl *res    = new StmtVarDecl(mod, line, col, newdecls);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtCond::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	std::vector<cond_t> newconds;
	for(auto &c : conds) {
		cond_t nc{c.cond ? c.cond->hiddenCopy(copy_type, copy_val, this) : nullptr,
			  static_cast<StmtBlock *>(c.blk->hiddenCopy(copy_type, copy_val, this))};
		newconds.push_back(nc);
	}
	StmtCond *res	    = new StmtCond(mod, line, col, newconds);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtForIn //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtForIn::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	Stmt *newin	    = in->hiddenCopy(copy_type, copy_val, this);
	StmtBlock *newblk   = static_cast<StmtBlock *>(blk->hiddenCopy(copy_type, copy_val, this));
	StmtForIn *res	    = new StmtForIn(mod, line, col, iter, newin, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFor::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	Stmt *newinit	    = init ? init->hiddenCopy(copy_type, copy_val, this) : nullptr;
	Stmt *newcond	    = cond ? cond->hiddenCopy(copy_type, copy_val, this) : nullptr;
	Stmt *newincr	    = incr ? incr->hiddenCopy(copy_type, copy_val, this) : nullptr;
	StmtBlock *newblk   = static_cast<StmtBlock *>(blk->hiddenCopy(copy_type, copy_val, this));
	StmtFor *res	    = new StmtFor(mod, line, col, newinit, newcond, newincr, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	res->is_inline	    = is_inline;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtWhile::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	Stmt *newcond	    = cond ? cond->hiddenCopy(copy_type, copy_val, this) : nullptr;
	StmtBlock *newblk   = static_cast<StmtBlock *>(blk->hiddenCopy(copy_type, copy_val, this));
	StmtWhile *res	    = new StmtWhile(mod, line, col, newcond, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtRet::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	Stmt *newval	    = val ? val->hiddenCopy(copy_type, copy_val, this) : nullptr;
	StmtRet *res	    = new StmtRet(mod, line, col, newval);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtContinue ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtContinue::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtContinue *res   = new StmtContinue(mod, line, col);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtBreak::hiddenCopy(const bool &copy_type, const bool &copy_val, Stmt *par)
{
	StmtBreak *res	    = new StmtBreak(mod, line, col);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->is_comptime    = is_comptime;
	return res;
}
} // namespace parser
} // namespace sc