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

#include "parser/Parse.hpp"

#include <unordered_set>

#include "Error.hpp"

namespace sc
{
namespace parser
{
// on successful parse, returns true, and tree is allocated
// if with_brace is true, it will attempt to find the beginning and ending brace for each block
bool parse_block(ParseHelper &p, StmtBlock *&tree, const bool &with_brace)
{
	tree = nullptr;

	std::vector<Stmt *> stmts;
	Stmt *stmt = nullptr;

	lex::Lexeme &start = p.peak();

	if(with_brace) {
		if(!p.acceptn(lex::LBRACE)) {
			err::set(p.peak(), "expected opening braces '{' for block, found: %s",
				 p.peak().tok.str().c_str());
			return false;
		}
	}

	while(p.valid() && (!with_brace || !p.accept(lex::RBRACE))) {
		bool skip_cols = false;
		// logic
		if(p.accept(lex::LET)) {
			if(!parse_vardecl(p, stmt)) goto fail;
		} else if(p.accept(lex::IF)) {
			if(!parse_conds(p, stmt)) goto fail;
			skip_cols = true;
		} else if(p.accept(lex::FOR)) {
			if(p.peakt(1) == lex::IDEN && p.peakt(2) == lex::IN) {
				if(!parse_forin(p, stmt)) goto fail;
			} else {
				if(!parse_for(p, stmt)) goto fail;
			}
			skip_cols = true;
		} else if(p.accept(lex::WHILE)) {
			if(!parse_while(p, stmt)) goto fail;
			skip_cols = true;
		} else if(p.accept(lex::RETURN)) {
			if(!parse_ret(p, stmt)) goto fail;
		} else if(p.accept(lex::CONTINUE)) {
			if(!parse_continue(p, stmt)) goto fail;
		} else if(p.accept(lex::BREAK)) {
			if(!parse_break(p, stmt)) goto fail;
		} else if(!parse_expr(p, stmt)) {
			goto fail;
		}

		if(skip_cols || p.acceptn(lex::COLS)) {
			stmts.push_back(stmt);
			stmt = nullptr;
			continue;
		}
		err::set(p.peak(), "expected semicolon for end of statement, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

	if(with_brace) {
		if(!p.acceptn(lex::RBRACE)) {
			err::set(p.peak(), "expected closing braces '}' for block, found: %s",
				 p.peak().tok.str().c_str());
			goto fail;
		}
	}

	tree = new StmtBlock(p.get_src(), start.line, start.col_beg, stmts);
	return true;
fail:
	for(auto &stmt : stmts) delete stmt;
	if(stmt) delete stmt;
	return false;
}

bool parse_type(ParseHelper &p, StmtType *&type)
{
	type = nullptr;

	size_t ptr  = 0;
	size_t info = 0;
	std::vector<lex::Lexeme> name;
	std::vector<lex::Lexeme> templates;
	Stmt *count   = nullptr;
	Stmt *fn      = nullptr;
	bool dot_turn = false; // to ensure type name is in the form <name><dot><name>...
	std::unordered_set<std::string> templnames;

	lex::Lexeme &start = p.peak();

	if(p.accept(lex::COMPTIME, lex::FN)) {
		if(!parse_fnsig(p, fn)) goto fail;
		type = new StmtType(p.get_src(), start.line, start.col_beg, fn);
		return true;
	}

	if(p.acceptn(lex::PreVA)) info |= TypeInfoMask::VARIADIC;

	while(p.acceptn(lex::MUL)) ++ptr;

	if(p.acceptn(lex::BAND)) info |= TypeInfoMask::REF;
	if(p.acceptn(lex::STATIC)) info |= TypeInfoMask::STATIC;
	if(p.acceptn(lex::CONST)) info |= TypeInfoMask::CONST;
	if(p.acceptn(lex::VOLATILE)) info |= TypeInfoMask::VOLATILE;

	while(p.accept(lex::IDEN, lex::DOT)) {
		if(!dot_turn && !p.accept(lex::IDEN)) {
			err::set(p.peak(), "expected identifier here, found dot");
			goto fail;
		}
		if(dot_turn && !p.accept(lex::DOT)) {
			err::set(p.peak(), "expected dot here, found identifier");
			goto fail;
		}
		dot_turn = !dot_turn;
		name.push_back(p.peak());
		p.next();
	}
	if(name.empty()) {
		err::set(p.peak(), "failed to parse type");
		goto fail;
	}

	if(!p.acceptn(lex::LT)) goto after_templates;
	// templates
	while(true) {
		if(!p.accept(lex::IDEN)) {
			err::set(p.peak(), "expected template name, found: %s",
				 p.peak().tok.str().c_str());
			goto fail;
		}
		if(templnames.find(p.peak().data.s) != templnames.end()) {
			err::set(p.peak(), "this template name is already used "
					   "before in this template group");
			goto fail;
		}
		templnames.insert(p.peak().data.s);
		templates.push_back(p.peak());
		p.next();
		if(!p.acceptn(lex::COMMA)) break;
	}
	if(!p.acceptn(lex::GT)) {
		err::set(p.peak(), "expected '>' for end of template names, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
after_templates:
	type = new StmtType(p.get_src(), start.line, start.col_beg, ptr, info, name, templates);
	return true;
fail:
	if(count) delete count;
	if(fn) delete fn;
	return false;
}

bool parse_simple(ParseHelper &p, Stmt *&data)
{
	data = nullptr;

	if(!p.peak().tok.is_data()) {
		err::set(p.peak(), "expected data here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

	lex::Lexeme &val = p.peak();
	p.next();

	data = new StmtSimple(p.get_src(), val.line, val.col_beg, val);
	return true;
}

bool parse_expr(ParseHelper &p, Stmt *&expr)
{
	return parse_expr_17(p, expr);
}

// Left Associative
// ,
bool parse_expr_17(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	size_t commas = 0;

	if(!parse_expr_16(p, rhs)) {
		return false;
	}

	while(p.accept(lex::COMMA)) {
		++commas;
		oper = p.peak();
		p.next();
		if(!parse_expr_16(p, lhs)) {
			goto fail;
		}
		rhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		lhs = nullptr;
	}

	if(rhs->type == parser::EXPR) {
		as<StmtExpr>(rhs)->commas = commas;
	}

	expr = rhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// ?:
bool parse_expr_16(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs     = nullptr;
	Stmt *rhs     = nullptr;
	Stmt *lhs_lhs = nullptr;
	Stmt *lhs_rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_15(p, lhs)) {
		return false;
	}
	if(!p.accept(lex::QUEST)) {
		expr = lhs;
		return true;
	}

	oper = p.peak();
	p.next();
	lex::Lexeme oper_inside;

	if(!parse_expr_15(p, lhs_lhs)) {
		goto fail;
	}
	if(!p.accept(lex::COL)) {
		err::set(p.peak(), "expected ':' for ternary operator, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}
	oper_inside = p.peak();
	p.next();
	if(!parse_expr_15(p, lhs_rhs)) {
		goto fail;
	}
	rhs = new StmtExpr(p.get_src(), oper_inside.line, oper_inside.col_beg, lhs_lhs, oper_inside,
			   lhs_rhs);
	goto after_quest;

after_quest:
	expr = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
	return true;
fail:
	if(lhs_rhs) delete lhs_rhs;
	if(lhs_lhs) delete lhs_lhs;
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Right Associative
// =
bool parse_expr_15(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_14(p, rhs)) {
		return false;
	}

	while(p.accept(lex::ASSN)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_14(p, lhs)) {
			goto fail;
		}
		rhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		lhs = nullptr;
	}

	expr = rhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// += -=
// *= /= %=
// <<= >>=
// &= |= ^=
// or-block
bool parse_expr_14(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs	  = nullptr;
	Stmt *rhs	  = nullptr;
	StmtBlock *or_blk = nullptr;
	lex::Lexeme or_blk_var;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_13(p, lhs)) {
		return false;
	}

	while(p.accept(lex::ADD_ASSN, lex::SUB_ASSN, lex::MUL_ASSN) ||
	      p.accept(lex::DIV_ASSN, lex::MOD_ASSN, lex::LSHIFT_ASSN) ||
	      p.accept(lex::RSHIFT_ASSN, lex::BAND_ASSN, lex::BOR_ASSN) || p.accept(lex::BNOT_ASSN))
	{
		oper = p.peak();
		p.next();
		if(!parse_expr_13(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;

	if(!p.acceptn(lex::OR)) return true;

	if(p.accept(lex::IDEN)) {
		or_blk_var = p.peak();
		p.next();
	}

	if(!parse_block(p, or_blk)) {
		goto fail;
	}
	if(expr->type != EXPR) {
		expr = new StmtExpr(p.get_src(), expr->line, expr->col, expr, {}, nullptr);
	}
	as<StmtExpr>(expr)->or_blk     = or_blk;
	as<StmtExpr>(expr)->or_blk_var = or_blk_var;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	if(or_blk) delete or_blk;
	return false;
}
// Left Associative
// ||
bool parse_expr_13(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_12(p, lhs)) {
		return false;
	}

	while(p.accept(lex::LOR)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_12(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// &&
bool parse_expr_12(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_11(p, lhs)) {
		return false;
	}

	while(p.accept(lex::LAND)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_11(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// |
bool parse_expr_11(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_10(p, lhs)) {
		return false;
	}

	while(p.accept(lex::BOR)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_10(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// ^
bool parse_expr_10(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_09(p, lhs)) {
		return false;
	}

	while(p.accept(lex::BAND)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_09(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// &
bool parse_expr_09(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_08(p, lhs)) {
		return false;
	}

	while(p.accept(lex::BAND)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_08(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// == !=
bool parse_expr_08(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_07(p, lhs)) {
		return false;
	}

	while(p.accept(lex::EQ, lex::NE)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_07(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// < <=
// > >=
bool parse_expr_07(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_06(p, lhs)) {
		return false;
	}

	while(p.accept(lex::LT, lex::LE) || p.accept(lex::GT, lex::GE)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_06(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// << >>
bool parse_expr_06(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_05(p, lhs)) {
		return false;
	}

	while(p.accept(lex::LSHIFT, lex::RSHIFT)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_05(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// + -
bool parse_expr_05(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_04(p, lhs)) {
		return false;
	}

	while(p.accept(lex::ADD, lex::SUB)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_04(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Left Associative
// * / %
bool parse_expr_04(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;
	Stmt *rhs = nullptr;

	lex::Lexeme oper;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_03(p, lhs)) {
		return false;
	}

	while(p.accept(lex::MUL, lex::DIV, lex::MOD)) {
		oper = p.peak();
		p.next();
		if(!parse_expr_03(p, rhs)) {
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), start.line, start.col_beg, lhs, oper, rhs);
		rhs = nullptr;
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	return false;
}
// Right Associative (single operand)
// ++ -- (pre)
// + - (unary)
// * & (deref, addrof)
// ! ~ (log/bit)
bool parse_expr_03(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;

	std::vector<lex::Lexeme> opers;

	lex::Lexeme &start = p.peak();

	while(p.accept(lex::XINC, lex::XDEC) || p.accept(lex::ADD, lex::SUB) ||
	      p.accept(lex::MUL, lex::BAND) || p.accept(lex::LNOT, lex::BNOT))
	{
		if(p.peakt() == lex::XINC) p.sett(lex::INCX);
		if(p.peakt() == lex::XDEC) p.sett(lex::DECX);
		if(p.peakt() == lex::ADD) p.sett(lex::UADD);
		if(p.peakt() == lex::SUB) p.sett(lex::USUB);
		if(p.peakt() == lex::MUL) p.sett(lex::UMUL);
		if(p.peakt() == lex::BAND) p.sett(lex::UAND);
		opers.insert(opers.begin(), p.peak());
		p.next();
	}

	if(!parse_expr_02(p, lhs)) {
		return false;
	}

	for(auto &op : opers) {
		lhs = new StmtExpr(p.get_src(), op.line, op.col_beg, lhs, op, nullptr);
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	return false;
}
// Left Associative
// ++ -- (post)
// ... (postva)
bool parse_expr_02(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	Stmt *lhs = nullptr;

	std::vector<lex::Lexeme> opers;

	lex::Lexeme &start = p.peak();

	if(!parse_expr_01(p, lhs)) {
		return false;
	}

	if(p.accept(lex::XINC, lex::XDEC, lex::PreVA)) {
		if(p.peakt() == lex::PreVA) p.sett(lex::PostVA);
		lhs =
		new StmtExpr(p.get_src(), p.peak().line, p.peak().col_beg, lhs, p.peak(), nullptr);
		p.next();
	}

	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	return false;
}
bool parse_expr_01(ParseHelper &p, Stmt *&expr)
{
	expr = nullptr;

	lex::Lexeme &start = p.peak();
	lex::Lexeme dot;

	Stmt *lhs      = nullptr;
	Stmt *rhs      = nullptr;
	bool is_intrin = false;
	std::vector<StmtType *> templates;
	StmtType *templ = nullptr;
	std::vector<Stmt *> args;
	Stmt *arg = nullptr;

	if(p.acceptn(lex::LPAREN)) {
		if(!parse_expr(p, expr)) {
			goto fail;
		}
		if(!p.acceptn(lex::RPAREN)) {
			err::set(p.peak(),
				 "expected ending parenthesis ')' for expression, found: %s",
				 p.peak().tok.str().c_str());
			goto fail;
		}
		return true;
	}

begin:
	if(p.acceptn(lex::AT)) is_intrin = true;

	if(p.acceptd() && !parse_simple(p, lhs)) goto fail;
	goto begin_brack;

after_dot:
	if(!p.acceptd() || !parse_simple(p, rhs)) goto fail;
	if(lhs && rhs) {
		lhs = new StmtExpr(p.get_src(), dot.line, dot.col_beg, lhs, dot, rhs);
		rhs = nullptr;
	}

begin_brack:
	if(p.accept(lex::LBRACK)) {
		lex::Lexeme oper;
		p.sett(lex::SUBS);
		oper = p.peak();
		p.next();
		if(is_intrin) {
			err::set(p.peak(), "only function calls can be intrinsic;"
					   " attempted subscript here");
			goto fail;
		}
		if(!parse_expr_16(p, rhs)) {
			err::set(oper, "failed to parse expression for subscript");
			goto fail;
		}
		if(!p.acceptn(lex::RBRACK)) {
			err::set(p.peak(),
				 "expected closing bracket for"
				 " subscript expression, found: %s",
				 p.peak().tok.str().c_str());
			goto fail;
		}
		lhs = new StmtExpr(p.get_src(), oper.line, oper.col_beg, lhs, oper, rhs);
		rhs = nullptr;
		if(p.accept(lex::LBRACK, lex::LPAREN) ||
		   (p.peakt() == lex::DOT && p.peakt(1) == lex::LT))
			goto begin_brack;
	} else if(p.accept(lex::LPAREN)) {
		lex::Lexeme oper;
		if(!p.accept(lex::LPAREN)) {
			err::set(p.peak(),
				 "expected opening parenthesis for function call, found: %s",
				 p.peak().tok.str().c_str());
			goto fail;
		}
		p.sett(lex::FNCALL);
		oper = p.peak();
		p.next();
		if(p.acceptn(lex::RPAREN)) {
			goto post_args;
		}
		// parse templates and arguments
		while(true) {
			if(p.acceptn(lex::COL)) {
				if(!parse_type(p, templ)) goto fail;
				templates.push_back(templ);
				templ = nullptr;
			} else {
				if(!parse_expr_16(p, arg)) goto fail;
				args.push_back(arg);
				arg = nullptr;
			}
			if(!p.acceptn(lex::COMMA)) break;
		}
		if(!p.acceptn(lex::RPAREN)) {
			err::set(p.peak(),
				 "expected closing parenthesis after function"
				 " call arguments, found: %s",
				 p.peak().tok.str().c_str());
			goto fail;
		}
	post_args:
		rhs  = new StmtFnCallInfo(p.get_src(), oper.line, oper.col_beg, templates, args);
		lhs  = new StmtExpr(p.get_src(), oper.line, oper.col_beg, lhs, oper, rhs);
		rhs  = nullptr;
		args = {};
		templates      = {};
		lhs->is_intrin = is_intrin;

		if(p.accept(lex::LBRACK, lex::LPAREN)) goto begin_brack;
	}

dot:
	if(p.acceptn(lex::DOT, lex::ARROW)) {
		if(lhs && rhs) {
			lhs = new StmtExpr(p.get_src(), p.peak(-1).line, p.peak(-1).col_beg, lhs,
					   p.peak(-1), rhs);
			rhs = nullptr;
		}
		dot = p.peak(-1);
		goto after_dot;
	}

done:
	if(lhs && rhs) {
		lhs = new StmtExpr(p.get_src(), dot.line, dot.col_beg, lhs, dot, rhs);
		rhs = nullptr;
	}
	expr = lhs;
	return true;
fail:
	if(lhs) delete lhs;
	if(rhs) delete rhs;
	for(auto &t : templates) delete t;
	if(templ) delete templ;
	for(auto &a : args) delete a;
	if(arg) delete arg;
	return false;
}

bool parse_var(ParseHelper &p, StmtVar *&var, const Occurs &intype, const Occurs &otype,
	       const Occurs &oval)
{
	var = nullptr;

	if(!p.accept(lex::IDEN)) {
		err::set(p.peak(), "expected identifier for variable name, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
	lex::Lexeme &name = p.peak();
	p.next();
	StmtType *in   = nullptr;
	StmtType *type = nullptr;
	Stmt *val      = nullptr;

in:
	if(intype == Occurs::NO && p.accept(lex::IN)) {
		err::set(p.peak(), "unexpected 'in' here");
		goto fail;
	}
	if(!p.acceptn(lex::IN)) {
		goto type;
	}
	if(!parse_type(p, in)) {
		err::set(p.peak(), "failed to parse in-type for variable: %s", name.data.s.c_str());
		goto fail;
	}

type:
	if(otype == Occurs::NO && p.accept(lex::COL)) {
		err::set(p.peak(), "unexpected beginning of type here");
		goto fail;
	}
	if(!p.acceptn(lex::COL)) {
		goto val;
	}
	if(!parse_type(p, type)) {
		err::set(p.peak(), "failed to parse type for variable: %s", name.data.s.c_str());
		goto fail;
	}

val:
	if(oval == Occurs::NO && p.accept(lex::ASSN)) {
		err::set(p.peak(), "unexpected beginning of value assignment here");
		goto fail;
	}
	if(!p.acceptn(lex::ASSN)) {
		goto done;
	}
	// if(p.accept(lex::ENUM)) {
	// 	if(!parse_enum(p, val)) goto fail;
	// } else
	if(p.accept(lex::STRUCT)) {
		if(!parse_struct(p, val)) goto fail;
	} else if(p.accept(lex::COMPTIME, lex::FN)) {
		if(!parse_fndef(p, val)) goto fail;
	} else if(p.accept(lex::EXTERN)) {
		if(!parse_extern(p, val)) goto fail;
	} else if(!parse_expr_16(p, val)) {
		goto fail;
	}

done:
	if(!type && !val) {
		err::set(name, "invalid variable declaration - no type or value set");
		goto fail;
	}
	if(in) {
		if(type) {
			err::set(name, "let-in statements can only have values (function "
				       "definitions) - no types allowed");
			goto fail;
		}
		if(val && val->type != FNDEF) {
			err::set(name, "only functions can be created using let-in statements");
			goto fail;
		}
		in->info |= TypeInfoMask::REF;
		lex::Lexeme selfeme = lex::Lexeme(in->line, in->col, in->col, lex::IDEN, "self");
		StmtVar *self = new StmtVar(p.get_src(), in->line, in->col, selfeme, in, nullptr);
		StmtFnSig *valsig = as<StmtFnDef>(val)->sig;
		for(auto &t : in->templates) {
			valsig->templates.push_back(t);
		}
		in->templates.clear();
		std::vector<StmtVar *> &params = valsig->params;
		params.insert(params.begin(), self);
	}
	var = new StmtVar(p.get_src(), name.line, name.col_beg, name, type, val);
	return true;
fail:
	if(in) delete in;
	if(type) delete type;
	if(val) delete val;
	return false;
}

bool parse_fnsig(ParseHelper &p, Stmt *&fsig)
{
	fsig = nullptr;

	std::vector<lex::Lexeme> templates;
	std::vector<StmtVar *> params;
	StmtVar *var = nullptr;
	std::unordered_set<std::string> argnames;
	bool found_va	  = false;
	StmtType *rettype = nullptr;
	bool comptime	  = false;
	std::unordered_set<std::string> templnames;
	lex::Lexeme &start = p.peak();

	if(p.acceptn(lex::COMPTIME)) comptime = true;

	if(!p.acceptn(lex::FN)) {
		err::set(p.peak(), "expected 'fn' here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

	if(!p.acceptn(lex::LT)) goto after_templates;

	// templates
	while(true) {
		if(!p.accept(lex::IDEN)) {
			err::set(p.peak(), "expected template name, found: %s",
				 p.peak().tok.str().c_str());
			goto fail;
		}
		if(templnames.find(p.peak().data.s) != templnames.end()) {
			err::set(p.peak(), "this template name is already used "
					   "before in this template group");
			goto fail;
		}
		templnames.insert(p.peak().data.s);
		templates.push_back(p.peak());
		p.next();
		if(!p.acceptn(lex::COMMA)) break;
	}
	if(!p.acceptn(lex::GT)) {
		err::set(p.peak(), "expected '>' for end of template names, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}

after_templates:
	if(!p.acceptn(lex::LPAREN)) {
		err::set(p.peak(), "expected opening parenthesis for function args, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
	if(p.acceptn(lex::RPAREN)) goto post_args;

	// args
	while(true) {
		if(argnames.find(p.peak().data.s) != argnames.end()) {
			err::set(p.peak(), "this argument name is already used "
					   "before in this function signature");
			goto fail;
		}
		if(templnames.find(p.peak().data.s) != templnames.end()) {
			err::set(p.peak(), "this argument name is already used before"
					   " for a template in this function signature");
			goto fail;
		}
		argnames.insert(p.peak().data.s);
		if(!parse_var(p, var, Occurs::NO, Occurs::YES, Occurs::NO)) {
			goto fail;
		}
		if(var->vtype->info & TypeInfoMask::VARIADIC) {
			found_va = true;
			if(!comptime) {
				err::set(start, "variadic function call must be compile time");
				goto fail;
			}
		}
		if(var->name.data.s == "any" && !found_va) {
			err::set(start, "type 'any' can be only used for variadic functions");
			goto fail;
		}
		params.push_back(var);
		var = nullptr;
		if(!p.acceptn(lex::COMMA)) break;
		if(found_va) {
			err::set(p.peak(), "no parameter can exist after variadic");
			goto fail;
		}
	}

	if(!p.acceptn(lex::RPAREN)) {
		err::set(p.peak(), "expected closing parenthesis after function args, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

post_args:
	if(p.acceptn(lex::COL) && !parse_type(p, rettype)) {
		err::set(p.peak(), "failed to parse return type for function");
		goto fail;
	}
	if(!rettype) {
		size_t line = p.peak(-1).line;
		size_t col  = p.peak(-1).col_beg;
		rettype	    = new StmtType(p.get_src(), line, col, 0, 0,
					   {lex::Lexeme(line, col, col, lex::VOID, "void")}, {});
	}

	fsig =
	new StmtFnSig(p.get_src(), start.line, start.col_beg, templates, params, rettype, comptime);
	return true;
fail:
	if(var) delete var;
	for(auto &p : params) delete p;
	if(rettype) delete rettype;
	return false;
}
bool parse_fndef(ParseHelper &p, Stmt *&fndef)
{
	fndef = nullptr;

	Stmt *sig	   = nullptr;
	StmtBlock *blk	   = nullptr;
	lex::Lexeme &start = p.peak();

	if(!parse_fnsig(p, sig)) goto fail;
	if(!parse_block(p, blk)) goto fail;

	fndef = new StmtFnDef(p.get_src(), start.line, start.col_beg, (StmtFnSig *)sig, blk);
	return true;
fail:
	if(sig) delete sig;
	if(blk) delete blk;
	return false;
}

bool parse_header(ParseHelper &p, StmtHeader *&header)
{
	header = nullptr;

	lex::Lexeme names, flags;

	if(!p.accept(lex::IDEN, lex::STR)) {
		err::set(p.peak(),
			 "expected string or identifier for the name of header, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
	names = p.peak();
	p.next();

	if(!p.acceptn(lex::COL)) goto done;

	if(!p.accept(lex::IDEN, lex::STR)) {
		err::set(p.peak(), "expected string or identifier for the header flags, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
	flags = p.peak();
	p.next();

done:
	header = new StmtHeader(p.get_src(), names.line, names.col_beg, names, flags);
	return true;
}
bool parse_lib(ParseHelper &p, StmtLib *&lib)
{
	lib = nullptr;

	lex::Lexeme flags;

	if(!p.accept(lex::IDEN, lex::STR)) {
		err::set(p.peak(), "expected string or identifier for the lib flags, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
	flags = p.peak();
	p.next();

	lib = new StmtLib(p.get_src(), flags.line, flags.col_beg, flags);
	return true;
}
bool parse_extern(ParseHelper &p, Stmt *&ext)
{
	ext = nullptr;

	lex::Lexeme name; // name of the function
	StmtHeader *headers = nullptr;
	StmtLib *libs	    = nullptr;
	Stmt *sig	    = nullptr;

	if(!p.acceptn(lex::EXTERN)) {
		err::set(p.peak(), "expected extern keyword here, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}

	if(!p.acceptn(lex::LBRACK)) {
		err::set(p.peak(), "expected opening bracket for extern information, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}

	if(!p.accept(lex::IDEN)) {
		err::set(p.peak(), "expected function name identifier or string here, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
	name = p.peak();
	p.next();

	if(!p.acceptn(lex::COMMA)) goto sig;

	if(!parse_header(p, headers)) goto fail;
	if(!p.acceptn(lex::COMMA)) goto endinfo;
	if(!parse_lib(p, libs)) goto fail;

endinfo:
	if(!p.acceptn(lex::RBRACK)) {
		err::set(p.peak(), "expected closing bracket after extern information, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}

sig:
	if(!parse_fnsig(p, sig)) goto fail;
	ext =
	new StmtExtern(p.get_src(), name.line, name.col_beg, name, headers, libs, (StmtFnSig *)sig);
	return true;
fail:
	if(headers) delete headers;
	if(libs) delete libs;
	if(sig) delete sig;
	return false;
}

bool parse_struct(ParseHelper &p, Stmt *&sd)
{
	sd = nullptr;

	bool decl = false;
	std::vector<lex::Lexeme> templates;
	std::vector<StmtVar *> fields;
	StmtVar *field = nullptr;
	std::unordered_set<std::string> fieldnames;
	std::unordered_set<std::string> templnames;
	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::STRUCT)) {
		err::set(p.peak(), "expected 'struct' keyword here, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}

	if(p.acceptn(lex::LT)) {
		while(true) {
			if(!p.accept(lex::IDEN)) {
				err::set(p.peak(), "expected template name, found: %s",
					 p.peak().tok.str().c_str());
				return false;
			}
			if(templnames.find(p.peak().data.s) != templnames.end()) {
				err::set(p.peak(), "this template name is already used "
						   "before in this template group");
				goto fail;
			}
			templnames.insert(p.peak().data.s);
			templates.push_back(p.peak());
			p.next();
			if(!p.acceptn(lex::COMMA)) break;
		}
		if(!p.acceptn(lex::GT)) {
			err::set(p.peak(), "expected '>' for end of template names, found: %s",
				 p.peak().tok.str().c_str());
			return false;
		}
	}

	if(!p.acceptn(lex::LBRACE)) {
		decl = true;
		goto done;
	}

	while(p.accept(lex::IDEN)) {
		if(fieldnames.find(p.peak().data.s) != fieldnames.end()) {
			err::set(p.peak(), "this field name is already used "
					   "before in this same structure");
			goto fail;
		}
		fieldnames.insert(p.peak().data.s);
		if(!parse_var(p, field, Occurs::NO, Occurs::YES, Occurs::NO)) goto fail;
		fields.push_back(field);
		field = nullptr;
		if(!p.acceptn(lex::COLS)) break;
	}
	if(!p.acceptn(lex::RBRACE)) {
		err::set(p.peak(),
			 "expected closing brace for struct/trait"
			 " declaration/definition, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

done:
	sd = new StmtStruct(p.get_src(), start.line, start.col_beg, decl, templates, fields);
	return true;

fail:
	if(field) delete field;
	for(auto &f : fields) delete f;
	return false;
}

bool parse_vardecl(ParseHelper &p, Stmt *&vd)
{
	vd = nullptr;

	std::vector<StmtVar *> decls;
	StmtVar *decl	   = nullptr;
	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::LET)) {
		err::set(p.peak(), "expected 'let' keyword here, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}

	while(p.accept(lex::IDEN)) {
		if(!parse_var(p, decl, Occurs::MAYBE, Occurs::MAYBE, Occurs::MAYBE)) goto fail;
		decls.push_back(decl);
		decl = nullptr;
		if(!p.acceptn(lex::COMMA)) break;
	}

	vd = new StmtVarDecl(p.get_src(), start.line, start.col_beg, decls);
	return true;

fail:
	if(decl) delete decl;
	for(auto &decl : decls) delete decl;
	return false;
}

bool parse_conds(ParseHelper &p, Stmt *&conds)
{
	conds = nullptr;

	std::vector<cond_t> cvec;
	cond_t c	   = {nullptr, nullptr};
	lex::Lexeme &start = p.peak();

cond:
	if(!p.acceptn(lex::IF)) {
		err::set(p.peak(), "expected 'if' here, found: %s", p.peak().tok.str().c_str());
		goto fail;
	}

	if(!parse_expr_15(p, c.cond)) {
		err::set(p.peak(), "failed to parse condition for if/else if statement");
		goto fail;
	}

blk:
	if(!parse_block(p, c.blk)) {
		err::set(p.peak(), "failed to parse block for conditional");
		goto fail;
	}

	cvec.push_back(c);
	c = {nullptr, nullptr};

	if(p.peakt() == lex::ELSE) {
		p.next();
		if(p.peakt() == lex::IF) goto cond;
		goto blk;
	}

	conds = new StmtCond(p.get_src(), start.line, start.col_beg, cvec);
	return true;

fail:
	if(c.cond) delete c.cond;
	if(c.blk) delete c.blk;
	for(auto &ce : cvec) {
		if(ce.cond) delete ce.cond;
		if(ce.blk) delete ce.blk;
	}
	return false;
}
bool parse_forin(ParseHelper &p, Stmt *&fin)
{
	fin = nullptr;

	lex::Lexeme iter;
	Stmt *in	   = nullptr; // L01
	StmtBlock *blk	   = nullptr;
	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::FOR)) {
		err::set(p.peak(), "expected 'for' here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

	if(!p.accept(lex::IDEN)) {
		err::set(p.peak(), "expected iterator (identifier) here, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}
	iter = p.peak();
	p.next();

	if(!p.acceptn(lex::IN)) {
		err::set(p.peak(), "expected 'in' here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

	if(!parse_expr_01(p, in)) {
		err::set(p.peak(), "failed to parse expression for 'in'");
		goto fail;
	}

	if(!p.accept(lex::LBRACE)) {
		err::set(p.peak(), "expected block for for-in construct, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

	if(!parse_block(p, blk)) {
		err::set(p.peak(), "failed to parse block for for-in construct");
		goto fail;
	}

	fin = new StmtForIn(p.get_src(), start.line, start.col_beg, iter, in, blk);
	return true;
fail:
	if(in) delete in;
	if(blk) delete blk;
	return false;
}
bool parse_for(ParseHelper &p, Stmt *&f)
{
	f = nullptr;

	Stmt *init	   = nullptr; // either of StmtVarDecl or StmtExpr
	Stmt *cond	   = nullptr;
	Stmt *incr	   = nullptr;
	StmtBlock *blk	   = nullptr;
	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::FOR)) {
		err::set(p.peak(), "expected 'for' here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

init:
	if(p.acceptn(lex::COLS)) goto cond;

	if(p.accept(lex::LET)) {
		if(!parse_vardecl(p, init)) goto fail;
	} else {
		if(!parse_expr(p, init)) goto fail;
	}
	if(!p.acceptn(lex::COLS)) {
		err::set(p.peak(), "expected semicolon here, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

cond:
	if(p.acceptn(lex::COLS)) goto incr;

	if(!parse_expr_16(p, cond)) goto fail;
	if(!p.acceptn(lex::COLS)) {
		err::set(p.peak(), "expected semicolon here, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

incr:
	if(p.acceptn(lex::LBRACE)) goto body;

	if(!parse_expr(p, incr)) goto fail;
	if(!p.accept(lex::LBRACE)) {
		err::set(p.peak(), "expected braces for body here, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

body:
	if(!parse_block(p, blk)) {
		err::set(p.peak(), "failed to parse block for 'for' construct");
		goto fail;
	}

	f = new StmtFor(p.get_src(), start.line, start.col_beg, init, cond, incr, blk);
	return true;
fail:
	if(init) delete init;
	if(cond) delete cond;
	if(incr) delete incr;
	if(blk) delete blk;
	return false;
}
bool parse_while(ParseHelper &p, Stmt *&w)
{
	w = nullptr;

	Stmt *cond	   = nullptr;
	StmtBlock *blk	   = nullptr;
	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::WHILE)) {
		err::set(p.peak(), "expected 'while' here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

	if(!parse_expr_16(p, cond)) goto fail;
	if(!p.acceptn(lex::COLS)) {
		err::set(p.peak(), "expected semicolon here, found: %s",
			 p.peak().tok.str().c_str());
		goto fail;
	}

	if(!parse_block(p, blk)) {
		err::set(p.peak(), "failed to parse block for 'for' construct");
		goto fail;
	}

	w = new StmtWhile(p.get_src(), start.line, start.col_beg, cond, blk);
	return true;
fail:
	if(cond) delete cond;
	if(blk) delete blk;
	return false;
}
bool parse_ret(ParseHelper &p, Stmt *&ret)
{
	ret = nullptr;

	Stmt *val	   = nullptr;
	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::RETURN)) {
		err::set(p.peak(), "expected 'return' here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

	if(p.accept(lex::COLS)) goto done;

	if(!parse_expr_16(p, val)) {
		err::set(p.peak(), "failed to parse expression for return value");
		goto fail;
	}

done:
	ret = new StmtRet(p.get_src(), start.line, start.col_beg, val);
	return true;
fail:
	if(val) delete val;
	return false;
}
bool parse_continue(ParseHelper &p, Stmt *&cont)
{
	cont = nullptr;

	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::CONTINUE)) {
		err::set(p.peak(), "expected 'continue' here, found: %s",
			 p.peak().tok.str().c_str());
		return false;
	}

	cont = new StmtContinue(p.get_src(), start.line, start.col_beg);
	return true;
}
bool parse_break(ParseHelper &p, Stmt *&brk)
{
	brk = nullptr;

	lex::Lexeme &start = p.peak();

	if(!p.acceptn(lex::BREAK)) {
		err::set(p.peak(), "expected 'break' here, found: %s", p.peak().tok.str().c_str());
		return false;
	}

	brk = new StmtContinue(p.get_src(), start.line, start.col_beg);
	return true;
}
} // namespace parser
} // namespace sc
