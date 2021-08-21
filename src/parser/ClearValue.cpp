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

#include "parser/Stmts.hpp"
#include "parser/Type.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtBlock::clearValue()
{
	this->value = nullptr;
	for(auto &s : stmts) {
		s->clearValue();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtType::clearValue()
{
	this->value = nullptr;
	if(fn) fn->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtSimple ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtSimple::clearValue()
{
	this->value = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtFnCallInfo::clearValue()
{
	this->value = nullptr;
	for(auto &t : templates) {
		t->clearValue();
	}
	for(auto &a : args) {
		a->clearValue();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtExpr::clearValue()
{
	this->value = nullptr;
	if(lhs) lhs->clearValue();
	if(rhs) rhs->clearValue();
	// TODO: or-var & or-blk
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtVar::clearValue()
{
	if(isComptime()) return;
	this->value = nullptr;
	if(val) val->clearValue();
	if(vtype) vtype->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtFnSig::clearValue()
{
	this->value = nullptr;
	for(auto &p : args) {
		p->clearValue();
	}
	if(rettype) rettype->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtFnDef::clearValue()
{
	this->value = nullptr;
	sig->clearValue();
	if(blk) blk->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtHeader ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtHeader::clearValue()
{
	this->value = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtLib //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtLib::clearValue()
{
	this->value = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtExtern ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtExtern::clearValue()
{
	this->value = nullptr;
	sig->clearValue();
	if(headers) headers->clearValue();
	if(libs) libs->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtEnum //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtEnum::clearValue()
{
	this->value = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtStruct /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtStruct::clearValue()
{
	this->value = nullptr;
	for(auto &f : fields) {
		f->clearValue();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtVarDecl ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtVarDecl::clearValue()
{
	this->value = nullptr;
	for(auto &d : decls) {
		d->clearValue();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtCond::clearValue()
{
	this->value = nullptr;
	for(auto &c : conds) {
		if(c.cond) c.cond->clearValue();
		c.blk->clearValue();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtForIn /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtForIn::clearValue()
{
	this->value = nullptr;
	in->clearValue();
	blk->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtFor::clearValue()
{
	this->value = nullptr;
	if(init) init->clearValue();
	if(cond) cond->clearValue();
	if(incr) incr->clearValue();
	blk->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtWhile::clearValue()
{
	this->value = nullptr;
	if(cond) cond->clearValue();
	blk->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtRet::clearValue()
{
	this->value = nullptr;
	if(val) val->clearValue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtContinue ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtContinue::clearValue()
{
	this->value = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void StmtBreak::clearValue()
{
	this->value = nullptr;
}
} // namespace parser
} // namespace sc