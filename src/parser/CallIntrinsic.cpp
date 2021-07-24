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
#include "parser/Type.hpp"

namespace sc
{
namespace parser
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBlock::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &s : stmts) {
		if(!s->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for statement in block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtType::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(fn && !fn->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for function type");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtSimple ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtSimple::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnCallInfo::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &t : templates) {
		if(!t->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for template");
			return false;
		}
	}
	for(auto &a : args) {
		if(!a->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for argument");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExpr::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(lhs && !lhs->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for LHS");
		return false;
	}
	if(rhs && !rhs->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for LHS");
		return false;
	}
	// TODO: or-var & or-blk
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVar::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(val && !val->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for 'val'");
		return false;
	}
	if(vtype && !vtype->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for 'type'");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnSig::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &p : params) {
		if(!p->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for parameter");
			return false;
		}
	}
	if(rettype && !rettype->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for return type");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnDef::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(!sig->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for function signature");
		return false;
	}
	if(blk && !blk->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtHeader ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtHeader::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtLib //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtLib::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtExtern ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExtern::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(!sig->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for function signature");
		return false;
	}
	if(headers && !headers->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for headers");
		return false;
	}
	if(libs && !libs->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for libs");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtEnum ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtEnum::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &i : items) {
		if(!i->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for enum item");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtStruct //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtStruct::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &f : fields) {
		if(!f->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for struct field");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// StmtVarDecl ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVarDecl::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &d : decls) {
		if(!d->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for var decl");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtCond::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	for(auto &c : conds) {
		if(c.cond && !c.cond->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for condition");
			return false;
		}
		if(!c.blk->call_intrinsic(types)) {
			err::set(line, col, "failed to call intrinsic for block");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// StmtForIn ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtForIn::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(!in->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for 'in' in foreach");
		return false;
	}
	if(!blk->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFor::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(init && !init->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for for loop init");
		return false;
	}
	if(cond && !cond->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for for loop cond");
		return false;
	}
	if(incr && !incr->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for for loop incr");
		return false;
	}
	if(!blk->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtWhile::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(cond && !cond->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for for loop cond");
		return false;
	}
	if(!blk->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for block");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtRet::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	if(val && !val->call_intrinsic(types)) {
		err::set(line, col, "failed to call intrinsic for return value");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtContinue /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtContinue::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBreak::call_intrinsic(TypeMgr &types)
{
	if(is_intrin && vtyp && !vtyp->call_intrinsic(types, this)) {
		err::set(line, col, "failed to call intrinsic from type: %s", vtyp->str().c_str());
		return false;
	}
	return true;
}
} // namespace parser
} // namespace sc