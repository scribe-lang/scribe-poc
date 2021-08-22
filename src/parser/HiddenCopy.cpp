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

Stmt *StmtBlock::hiddenCopy(const bool &with_value, Stmt *par)
{
	std::vector<Stmt *> newstmts;
	for(auto &s : stmts) {
		if(!s) break;
		newstmts.push_back(s->hiddenCopy(with_value, this));
	}
	StmtBlock *res	    = new StmtBlock(mod, line, col, newstmts);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtType::hiddenCopy(const bool &with_value, Stmt *par)
{
	if(fn) {
		Stmt *newfn	    = fn->hiddenCopy(with_value, this);
		StmtType *res	    = new StmtType(mod, line, col, newfn);
		res->parent	    = par;
		res->is_specialized = is_specialized;
		res->specialized_id = specialized_id;
		res->is_comptime    = is_comptime;
		if(with_value) res->value = value;
		return res;
	}
	StmtType *res	    = new StmtType(mod, line, col, ptr, info, name, templates);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtSimple /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtSimple::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtSimple *res	       = new StmtSimple(mod, line, col, val);
	res->parent	       = par;
	res->is_specialized    = is_specialized;
	res->specialized_id    = specialized_id;
	res->is_comptime       = is_comptime;
	res->applied_module_id = applied_module_id;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtFnCallInfo ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnCallInfo::hiddenCopy(const bool &with_value, Stmt *par)
{
	std::vector<StmtType *> newtemplates;
	std::vector<Stmt *> newargs;
	for(auto &t : templates) {
		newtemplates.push_back(static_cast<StmtType *>(t->hiddenCopy(with_value, this)));
	}
	for(auto &a : args) {
		newargs.push_back(a->hiddenCopy(with_value, this));
	}
	StmtFnCallInfo *res = new StmtFnCallInfo(mod, line, col, newtemplates, newargs);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtExpr::hiddenCopy(const bool &with_value, Stmt *par)
{
	Stmt *newlhs  = lhs ? lhs->hiddenCopy(with_value, this) : nullptr;
	Stmt *newrhs  = rhs ? rhs->hiddenCopy(with_value, this) : nullptr;
	StmtExpr *res = new StmtExpr(mod, line, col, newlhs, oper, newrhs);
	if(or_blk) res->or_blk = static_cast<StmtBlock *>(or_blk->hiddenCopy(with_value, this));
	res->or_blk_var	    = or_blk_var;
	res->parent	    = par;
	res->is_intrinsic   = is_intrinsic;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtVar::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtType *newvtype = vtype ? as<StmtType>(vtype->hiddenCopy(with_value, this)) : nullptr;
	Stmt *newval	   = val ? val->hiddenCopy(with_value, this) : nullptr;

	StmtVar *res	    = new StmtVar(mod, line, col, name, newvtype, newval);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnSig::hiddenCopy(const bool &with_value, Stmt *par)
{
	std::vector<StmtVar *> newargs;
	for(auto &p : args) {
		newargs.push_back(static_cast<StmtVar *>(p->hiddenCopy(with_value, this)));
	}
	StmtType *newret =
	rettype ? static_cast<StmtType *>(rettype->hiddenCopy(with_value, this)) : nullptr;
	StmtFnSig *res = new StmtFnSig(mod, line, col, templates, newargs, newret, has_variadic);
	res->parent    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFnDef::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtFnSig *newsig = static_cast<StmtFnSig *>(sig->hiddenCopy(with_value, this));
	StmtBlock *newblk =
	blk ? static_cast<StmtBlock *>(blk->hiddenCopy(with_value, this)) : nullptr;
	StmtFnDef *res	    = new StmtFnDef(mod, line, col, newsig, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtHeader /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtHeader::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtHeader *res	    = new StmtHeader(mod, line, col, names, flags);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtLib ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtLib::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtLib *res	    = new StmtLib(mod, line, col, flags);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtExtern /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtExtern::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtHeader *newheaders =
	headers ? static_cast<StmtHeader *>(headers->hiddenCopy(with_value, this)) : nullptr;
	StmtLib *newlibs =
	libs ? static_cast<StmtLib *>(libs->hiddenCopy(with_value, this)) : nullptr;
	StmtFnSig *newsig   = static_cast<StmtFnSig *>(sig->hiddenCopy(with_value, this));
	StmtExtern *res	    = new StmtExtern(mod, line, col, fname, newheaders, newlibs, newsig);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtEnum //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtEnum::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtEnum *res	    = new StmtEnum(mod, line, col, items);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtStruct /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtStruct::hiddenCopy(const bool &with_value, Stmt *par)
{
	std::vector<StmtVar *> newfields;
	for(auto &f : fields) {
		newfields.push_back(static_cast<StmtVar *>(f->hiddenCopy(with_value, this)));
	}
	StmtStruct *res	    = new StmtStruct(mod, line, col, decl, templates, newfields);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtVarDecl /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtVarDecl::hiddenCopy(const bool &with_value, Stmt *par)
{
	std::vector<StmtVar *> newdecls;
	for(auto &d : decls) {
		newdecls.push_back(static_cast<StmtVar *>(d->hiddenCopy(with_value, this)));
	}
	StmtVarDecl *res    = new StmtVarDecl(mod, line, col, newdecls);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtCond::hiddenCopy(const bool &with_value, Stmt *par)
{
	std::vector<cond_t> newconds;
	for(auto &c : conds) {
		cond_t nc{c.cond ? c.cond->hiddenCopy(with_value, this) : nullptr,
			  static_cast<StmtBlock *>(c.blk->hiddenCopy(with_value, this))};
		newconds.push_back(nc);
	}
	StmtCond *res	    = new StmtCond(mod, line, col, newconds);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	res->is_inline = is_inline;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtForIn //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtForIn::hiddenCopy(const bool &with_value, Stmt *par)
{
	Stmt *newin	    = in->hiddenCopy(with_value, this);
	StmtBlock *newblk   = static_cast<StmtBlock *>(blk->hiddenCopy(with_value, this));
	StmtForIn *res	    = new StmtForIn(mod, line, col, iter, newin, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtFor::hiddenCopy(const bool &with_value, Stmt *par)
{
	Stmt *newinit	    = init ? init->hiddenCopy(with_value, this) : nullptr;
	Stmt *newcond	    = cond ? cond->hiddenCopy(with_value, this) : nullptr;
	Stmt *newincr	    = incr ? incr->hiddenCopy(with_value, this) : nullptr;
	StmtBlock *newblk   = static_cast<StmtBlock *>(blk->hiddenCopy(with_value, this));
	StmtFor *res	    = new StmtFor(mod, line, col, newinit, newcond, newincr, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	res->is_inline = is_inline;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtWhile::hiddenCopy(const bool &with_value, Stmt *par)
{
	Stmt *newcond	    = cond ? cond->hiddenCopy(with_value, this) : nullptr;
	StmtBlock *newblk   = static_cast<StmtBlock *>(blk->hiddenCopy(with_value, this));
	StmtWhile *res	    = new StmtWhile(mod, line, col, newcond, newblk);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtRet::hiddenCopy(const bool &with_value, Stmt *par)
{
	Stmt *newval	    = val ? val->hiddenCopy(with_value, this) : nullptr;
	StmtRet *res	    = new StmtRet(mod, line, col, newval);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtContinue ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtContinue::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtContinue *res   = new StmtContinue(mod, line, col);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Stmt *StmtBreak::hiddenCopy(const bool &with_value, Stmt *par)
{
	StmtBreak *res	    = new StmtBreak(mod, line, col);
	res->parent	    = par;
	res->is_specialized = is_specialized;
	res->specialized_id = specialized_id;
	res->is_comptime    = is_comptime;
	if(with_value) res->value = value;
	return res;
}
} // namespace parser
} // namespace sc