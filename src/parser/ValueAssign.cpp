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

#include <cassert>
#include <cinttypes>

#include "Error.hpp"
#include "Parser.hpp"
#include "parser/Stmts.hpp"
#include "parser/ValueMgr.hpp"

#define CHECK_VALUE(x) (x && x->value && x->value->has_data())

namespace sc
{
namespace parser
{
static bool break_stmt	  = false;
static bool continue_stmt = false;
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBlock ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBlock::assignValue(TypeMgr &types, ValueMgr &vals)
{
	for(auto &s : stmts) {
		if(!s) break;
		if(!s->assignValue(types, vals)) return false;
		if(break_stmt || continue_stmt) break;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtType /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtType::assignValue(TypeMgr &types, ValueMgr &vals)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtSimple ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtSimple::assignValue(TypeMgr &types, ValueMgr &vals)
{
	switch(val.tok.val) {
	// case lex::VOID: value = vals.get(VVOID); break;
	case lex::VOID: err::set(val, "void cannot be a value"); return false;
	case lex::TRUE: value = vals.get((int64_t)1); break;
	case lex::FALSE: // fallthrough
	case lex::NIL: value = vals.get((int64_t)0); break;
	case lex::INT: value = vals.get(val.data.i); break;
	case lex::FLT: value = vals.get((double)val.data.f); break;
	case lex::CHAR: value = vals.get((int64_t)val.data.s[0]); break;
	case lex::STR: value = vals.get(val.data.s); break;
	case lex::IDEN: {
		if(!type) {
			err::set(val, "variable does not exist");
			return false;
		}
		// nothing to do for funcmap
		if(type->type == TFUNCMAP || type->type == TFUNC) {
			value = nullptr;
			return true;
		}
		if(!type->parent) {
			err::set(val, "type '%s' has no parent", type->str().c_str());
			return false;
		}
		assert(type->parent->stmt_type == VAR && "parent must be a variable declaration");
		StmtVar *pvar = as<StmtVar>(type->parent);
		// nothing to do with functions - they will be executed by StmtExpr
		if(pvar->val && pvar->val->stmt_type == FNDEF) {
			value = nullptr;
			return true;
		}
		if(!type->parent->value && !type->parent->assignValue(types, vals)) {
			err::set(val, "this variable is not comptime");
			return false;
		}
		value = type->parent->value;
		break;
	}
	default: return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// StmtFnCallInfo //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnCallInfo::assignValue(TypeMgr &types, ValueMgr &vals)
{
	for(auto &a : args) {
		if(!a->assignValue(types, vals)) {
			err::set(a->line, a->col,
				 "failed to determine value"
				 " for comptime function call");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtExpr /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExpr::assignValue(TypeMgr &types, ValueMgr &vals)
{
	if(lhs && !lhs->assignValue(types, vals)) {
		err::set(lhs->line, lhs->col, "failed to determine value of LHS");
		return false;
	}
	if(oper.tok.val == lex::EMPTY) {
		value = lhs->value;
		return true;
	}
	if(oper.tok.val == lex::DOT) {
		Types rhstype = rhs->type->type;
		if(rhstype == TFUNC || rhstype == TFUNCMAP || rhstype == TVARIADIC) {
			value = lhs->value;
			return true;
		}
		value = lhs->value->st[as<StmtSimple>(rhs)->val.data.s];
		return true;
	}
	if(rhs && !rhs->assignValue(types, vals)) {
		err::set(rhs->line, rhs->col, "failed to determine value of RHS");
		return false;
	}
	if(oper.tok.val == lex::SUBS) {
		if(lhs->type->type == TVARIADIC) {
			if(rhs->value->i >= lhs->value->v.size()) {
				err::set(line, col,
					 "variadic length is less than"
					 " the subscript value (va: %zu, subscript: %" PRId64 "",
					 lhs->value->v.size(), rhs->value->i);
				return false;
			}
			value = lhs->value->v[rhs->value->i];
			return true;
		}
	}
	if(!hasIntrinsicFunc()) {
		assert(lhs->type->parent->stmt_type == VAR &&
		       "parent must be a variable declaration");
		StmtFnCallInfo *finfo = as<StmtFnCallInfo>(rhs);
		if(!finfo->assignValue(types, vals)) {
			err::set(line, col, "failed to determine values for function call args");
			return false;
		}
		StmtVar *lvar = as<StmtVar>(lhs->type->parent);
		if(lvar->val->stmt_type == FNDEF) {
			StmtFnDef *def	   = as<StmtFnDef>(lvar->val);
			StmtFnSig *sig	   = as<StmtFnSig>(def->sig);
			size_t self_offset = 0;
			if(lhs->stmt_type == EXPR) {
				self_offset	    = 1;
				sig->args[0]->value = vals.get(lhs->value);
			}
			size_t args_end = sig->args.size();
			if(sig->has_variadic) {
				--args_end;
			}
			for(size_t i = 0; i < args_end; ++i) {
				sig->args[i + self_offset]->value = vals.get(finfo->args[i]->value);
			}
			if(sig->has_variadic) {
				size_t j = 0;
				std::vector<Value *> vvec;
				for(size_t i = args_end; i < finfo->args.size(); ++i) {
					vvec.push_back(vals.get(finfo->args[i]->value));
				}
				sig->args[args_end]->value = vals.get(vvec);
			}
			if(!def->assignValue(types, vals)) {
				err::set(line, col, "failed to determine value for function call");
				return false;
			}
			value = def->value;
			def->clearValue();
			return true;
		} else if(lvar->val->stmt_type == STRUCTDEF) {
			StmtStruct *def = as<StmtStruct>(lvar->val);
			std::unordered_map<std::string, Value *> fields;
			std::vector<std::string> fieldsorder;
			for(size_t i = 0; i < finfo->args.size(); ++i) {
				fields[def->fields[i]->name.data.s] =
				vals.get(finfo->args[i]->value);
				fieldsorder.push_back(def->fields[i]->name.data.s);
			}
			value = vals.get(fields, fieldsorder);
			return true;
		}
	}
	if(lhs && lhs->type->type != TFUNC && !lhs->value) {
		err::set(line, col, "LHS has no value for function call");
		return false;
	}
	if(rhs && rhs->stmt_type != FNCALLINFO && !rhs->value) {
		err::set(line, col, "RHS has no value for function call");
		return false;
	}
	std::vector<Stmt *> args;
	if(lhs && lhs->type->type != TFUNC) {
		args.push_back(lhs);
	}
	if(rhs) {
		if(rhs->stmt_type == FNCALLINFO) {
			for(auto &a : as<StmtFnCallInfo>(rhs)->args) {
				args.push_back(a);
			}
		} else {
			args.push_back(rhs);
		}
	}
	return callIntrinsic(types, vals, this, {}, args);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtVar //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVar::assignValue(TypeMgr &types, ValueMgr &vals)
{
	if(parent->stmt_type == FNSIG && isComptime() && value) {
		return true;
	}
	if(!val) {
		err::set(name, "'comptime' requires value to be present for the variable");
		return false;
	}
	// don't bother with functions that still have templates or are variadic
	if(val->stmt_type == FNDEF) {
		StmtFnSig *sig = as<StmtFnDef>(val)->sig;
		if(sig->templates.size() > 0 || sig->has_variadic) {
			return true;
		}
	}
	if(!val->assignValue(types, vals)) {
		err::set(name, "failed to compute value for comptime variable");
		return false;
	}
	value = val->value;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnSig ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnSig::assignValue(TypeMgr &types, ValueMgr &vals)
{
	// handled by StmtExpr
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFnDef ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFnDef::assignValue(TypeMgr &types, ValueMgr &vals)
{
	assert(blk && "no block for function definition");
	if(!blk->assignValue(types, vals)) {
		err::set(line, col, "failed to assign value for function block");
		return false;
	}
	value = blk->value;
	if(!value) {
		err::set(line, col, "failed to assign value for function definition");
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtHeader ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtHeader::assignValue(TypeMgr &types, ValueMgr &vals)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtLib //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtLib::assignValue(TypeMgr &types, ValueMgr &vals)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtExtern ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtExtern::assignValue(TypeMgr &types, ValueMgr &vals)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtEnum //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtEnum::assignValue(TypeMgr &types, ValueMgr &vals)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtStruct /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtStruct::assignValue(TypeMgr &types, ValueMgr &vals)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtVarDecl ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtVarDecl::assignValue(TypeMgr &types, ValueMgr &vals)
{
	for(auto &d : decls) {
		if(!d->assignValue(types, vals)) {
			err::set(d->name, "failed to assign value for variable declaration");
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtCond /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtCond::assignValue(TypeMgr &types, ValueMgr &vals)
{
	if(is_inline) {
		if(conds.empty()) return true;
		if(!conds[0].blk->assignValue(types, vals)) {
			err::set(line, col, "failed to assign value for inline-conditional");
			return false;
		}
		return true;
	}
	for(auto &c : conds) {
		if(!c.cond) {
			if(!c.blk->assignValue(types, vals)) {
				err::set(line, col, "failed to determine else-block value");
				return false;
			}
			break;
		}
		if(!c.cond->assignValue(types, vals)) {
			err::set(line, col, "failed to determine conditional value");
			return false;
		}
		if(c.cond->value->i == 0) continue;
		if(!c.blk->assignValue(types, vals)) {
			err::set(line, col, "failed to determine condition-block value");
			return false;
		}
		break;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// StmtForIn /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtForIn::assignValue(TypeMgr &types, ValueMgr &vals)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtFor //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtFor::assignValue(TypeMgr &types, ValueMgr &vals)
{
	assert(blk && "no block for for-loop");
	if(is_inline) {
		if(init && !init->assignValue(types, vals)) {
			err::set(line, col, "failed to assign value for for-loop init");
			return false;
		}
		if(!blk->assignValue(types, vals)) {
			err::set(line, col, "failed to assign value for for-loop block");
			return false;
		}
		clearValue();
		return true;
	}
	if(init && !init->assignValue(types, vals)) {
		err::set(line, col, "failed to assign value for for-init statement");
		return false;
	}
	while(!cond || (cond->assignValue(types, vals) && cond->value->i != 0)) {
		if(!blk->assignValue(types, vals)) {
			err::set(line, col, "failed to assign value for for-loop block");
			return false;
		}
		continue_stmt = false;
		if(break_stmt) break;
		if(incr) incr->clearValue();
		if(incr && !incr->assignValue(types, vals)) {
			err::set(line, col, "failed to determine incr value for for-loop");
			return false;
		}
		cond->clearValue();
	}
	break_stmt = false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtWhile ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtWhile::assignValue(TypeMgr &types, ValueMgr &vals)
{
	assert(blk && "no block for while-loop");
	while(!cond || (cond->assignValue(types, vals) && cond->value->i != 0)) {
		if(!blk->assignValue(types, vals)) {
			err::set(line, col, "failed to assign value for for-loop block");
			return false;
		}
		continue_stmt = false;
		if(break_stmt) break;
	}
	break_stmt = false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtRet //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtRet::assignValue(TypeMgr &types, ValueMgr &vals)
{
	if(val && !val->assignValue(types, vals)) {
		err::set(line, col, "failed to determine value of return argument");
		return false;
	}
	value	       = val ? val->value : vals.get(VVOID);
	StmtFnDef *def = as<StmtFnDef>(getParentWithType(FNDEF));
	if(!def) {
		err::set(line, col, "Could not find parent function definition of return");
		return false;
	}
	def->blk->value = value;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// StmtContinue ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtContinue::assignValue(TypeMgr &types, ValueMgr &vals)
{
	continue_stmt = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// StmtBreak ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool StmtBreak::assignValue(TypeMgr &types, ValueMgr &vals)
{
	break_stmt = true;
	return true;
}
} // namespace parser
} // namespace sc