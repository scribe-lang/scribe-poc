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

#include "Lex.hpp"

#include <string.h>
#include <string>

#include "Error.hpp"

namespace sc
{
namespace lex
{
const char *TokStrs[_LAST] = {
"INT",
"FLT",
"CHAR",
"STR",
"IDEN",

// Keywords
"let",
"fn",
"if",
"elif",
"else",
"for",
"in",
"while",
"return",
"continue",
"break",
"void",
"true",
"false",
"nil",
"or",
"static",
"const",
"volatile",
"extern",
"comptime",
"inline",
"struct",
"enum",
// "i8",
// "i16",
// "i32",
// "i64",
// "i128",
// "u8",
// "u16",
// "u32",
// "u64",
// "u128",
// "f32",
// "f64",

// Operators
"=",
// Arithmetic
"+",
"-",
"*",
"/",
"%",
"+=",
"-=",
"*=",
"/=",
"%=",
// Post/Pre Inc/Dec
"x++",
"++x",
"x--",
"--x",
// Unary (used by parser (in Expression.cpp))
"u+",
"u-",
"u&",
"u*",
// Logic
"&&",
"||",
"!",
// Comparison
"==",
"<",
">",
"<=",
">=",
"!=",
// Bitwise
"&",
"|",
"~",
"^",
"&=",
"|=",
"~=",
"^=",
// Others
"<<",
">>",
"<<=",
">>=",

"[]",
"()",

// Varargs
"x...",
"...x",

// Separators
".",
"?",
":",
",",
"@",
"SPC",
"TAB",
"NEWL",
";",
"->",
// Parenthesis, Braces, Brackets
"(",
")",
"{",
"}",
"[",
"]",

"<FEOF>",
"<INVALID>",
};

std::string view_backslash(const std::string &data);

Tok::Tok(const int &tok) : val((TokType)tok) {}

bool Data::cmp(Data &other, TokType type)
{
	switch(type) {
	case STR:
	case IDEN: return s == other.s;
	case INT: return i == other.i;
	case FLT: return f == other.f;
	default: return false;
	}
	return false;
}

Lexeme::Lexeme()
	: line(0), col_beg(0), col_end(0), tok(INVALID), data({.s = "", .i = 0lu, .f = 0.0})
{}
Lexeme::Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
	       const TokType &type)
	: line(line), col_beg(col_beg), col_end(col_end), tok(type),
	  data({.s = "", .i = 0lu, .f = 0.0})
{}
Lexeme::Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
	       const TokType &type, const std::string &_data)
	: line(line), col_beg(col_beg), col_end(col_end), tok(type),
	  data({.s = _data, .i = 0lu, .f = 0.0})
{}
Lexeme::Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
	       const int64_t &_data)
	: line(line), col_beg(col_beg), col_end(col_end), tok(INT),
	  data({.s = "", .i = _data, .f = 0.0})
{}
Lexeme::Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
	       const long double &_data)
	: line(line), col_beg(col_beg), col_end(col_end), tok(FLT),
	  data({.s = "", .i = 0lu, .f = _data})
{}
std::string Lexeme::str(const int64_t &pad)
{
	std::string res;
	int64_t len;
	res += tok.cstr();
	len = res.size();
	for(int64_t i = 0; i < pad - len; ++i) res += " ";
	if(pad == 0) res += " ";
	len = res.size();
	res += "[" + std::to_string(line) + ":" + std::to_string(col_beg) + "-" +
	       std::to_string(col_end) + "]";
	if(!tok.isData()) return res;
	len = res.size() - len;
	for(int64_t i = 0; i < pad - len; ++i) res += " ";
	if(pad == 0) res += " ";
	if(tok.val == CHAR || tok.val == STR || tok.val == IDEN) {
		res += view_backslash(data.s);
	} else if(tok.val == INT) {
		res += std::to_string(data.i);
	} else if(tok.val == FLT) {
		res += std::to_string(data.f);
	}
	return res;
}

static std::string get_name(const std::string &data, size_t &i);
static TokType classify_str(const std::string &str);
static std::string get_num(const std::string &data, size_t &i, size_t &line, size_t &line_start,
			   TokType &num_type, int &base);
static bool get_const_str(const std::string &data, char &quote_type, size_t &i, size_t &line,
			  size_t &line_start, std::string &buf);
static TokType get_operator(const std::string &data, size_t &i, const size_t &line,
			    const size_t &line_start);
static void remove_back_slash(std::string &s);

#define CURR (data[i])
#define NEXT (i + 1 < len ? data[i + 1] : 0)
#define PREV (len > 0 && i > 0 ? data[i - 1] : 0)
#define SET_OP_TYPE_BRK(type) \
	op_type = type;       \
	break

bool tokenize(const std::string &data, std::vector<Lexeme> &toks)
{
	int comment_block = 0; // int to handle nested comment blocks
	bool comment_line = false;

	size_t len	  = data.size();
	size_t i	  = 0;
	size_t line	  = 0;
	size_t line_start = 0;
	while(i < len) {
		if(CURR == '\n') {
			++line;
			line_start = i + 1;
		}
		if(comment_line) {
			if(CURR == '\n') comment_line = false;
			++i;
			continue;
		}
		if(isspace(CURR)) {
			++i;
			continue;
		}
		if(CURR == '*' && NEXT == '/') {
			if(!comment_block) {
				err::set(line, i - line_start, i - line_start + 2,
					 "encountered multi line comment terminator '*/' in"
					 "non comment block");
				return false;
			}
			i += 2;
			--comment_block;
			continue;
		}
		if(CURR == '/' && NEXT == '*') {
			i += 2;
			++comment_block;
			continue;
		}
		if(comment_block) {
			++i;
			continue;
		}
		if(CURR == '/' && NEXT == '/') {
			comment_line = true;
			++i;
			continue;
		}

		// strings
		if((CURR == '.' && (isalpha(NEXT) || NEXT == '_') && !isalnum(PREV) &&
		    PREV != '_' && PREV != ')' && PREV != ']' && PREV != '\'' && PREV != '"') ||
		   isalpha(CURR) || CURR == '_')
		{
			std::string str = get_name(data, i);
			// check if string is a keyword
			TokType str_class = classify_str(str);
			if(str[0] == '.') str.erase(str.begin());
			if(str_class == STR || str_class == IDEN)
			{ // place either the data itself (type = STR, IDEN)
				toks.emplace_back(line, i - line_start - str.size(), i - line_start,
						  str_class, str);
			} else { // or the type
				toks.emplace_back(line, i - line_start - str.size(), i - line_start,
						  str_class);
			}
			continue;
		}

		// numbers
		if(isdigit(CURR)) {
			TokType num_type = INT;
			int base	 = 10;
			std::string num	 = get_num(data, i, line, line_start, num_type, base);
			if(num.empty()) return false;
			if(num_type == FLT) {
				toks.emplace_back(line, i - line_start - num.size(), i - line_start,
						  (long double)std::stod(num));
				continue;
			}
			toks.emplace_back(line, i - line_start - num.size(), i - line_start,
					  (int64_t)std::stoull(num, 0, base));
			continue;
		}

		// const strings
		if(CURR == '\"' || CURR == '\'' || CURR == '`') {
			std::string str;
			char quote_type = 0;
			if(!get_const_str(data, quote_type, i, line, line_start, str)) return false;
			toks.emplace_back(line, i - line_start - str.size(), i - line_start,
					  quote_type == '\'' ? CHAR : STR, str);
			continue;
		}

		// operators
		size_t begin	= i;
		TokType op_type = get_operator(data, i, line, line_start);
		if(op_type == INVALID) return false;
		toks.emplace_back(line, begin - line_start, i - line_start, op_type);
	}
	return true;
}

static std::string get_name(const std::string &data, size_t &i)
{
	size_t len = data.size();
	std::string buf;
	buf.push_back(data[i++]);
	while(i < len) {
		if(!isalnum(CURR) && CURR != '_') break;
		buf.push_back(data[i++]);
	}
	if(i < len && CURR == '?') buf.push_back(data[i++]);

	return buf;
}

static TokType classify_str(const std::string &str)
{
	if(str == TokStrs[LET]) return LET;
	if(str == TokStrs[FN]) return FN;
	if(str == TokStrs[IF]) return IF;
	if(str == TokStrs[ELIF]) return ELIF;
	if(str == TokStrs[ELSE]) return ELSE;
	if(str == TokStrs[FOR]) return FOR;
	if(str == TokStrs[IN]) return IN;
	if(str == TokStrs[WHILE]) return WHILE;
	if(str == TokStrs[RETURN]) return RETURN;
	if(str == TokStrs[CONTINUE]) return CONTINUE;
	if(str == TokStrs[BREAK]) return BREAK;
	if(str == TokStrs[VOID]) return VOID;
	if(str == TokStrs[TRUE]) return TRUE;
	if(str == TokStrs[FALSE]) return FALSE;
	if(str == TokStrs[NIL]) return NIL;
	if(str == TokStrs[OR]) return OR;
	if(str == TokStrs[STATIC]) return STATIC;
	if(str == TokStrs[CONST]) return CONST;
	if(str == TokStrs[VOLATILE]) return VOLATILE;
	if(str == TokStrs[EXTERN]) return EXTERN;
	if(str == TokStrs[COMPTIME]) return COMPTIME;
	if(str == TokStrs[INLINE]) return INLINE;
	if(str == TokStrs[STRUCT]) return STRUCT;
	if(str == TokStrs[ENUM]) return ENUM;
	// if(str == TokStrs[I8]) return I8;
	// if(str == TokStrs[I16]) return I16;
	// if(str == TokStrs[I32]) return I32;
	// if(str == TokStrs[I64]) return I64;
	// if(str == TokStrs[I128]) return I128;
	// if(str == TokStrs[U8]) return U8;
	// if(str == TokStrs[U16]) return U16;
	// if(str == TokStrs[U32]) return U32;
	// if(str == TokStrs[U64]) return U64;
	// if(str == TokStrs[U128]) return U128;
	// if(str == TokStrs[F32]) return F32;
	// if(str == TokStrs[F64]) return F64;

	// if string begins with dot, it's an atom (str), otherwise an identifier
	return str[0] == '.' ? STR : IDEN;
}

static std::string get_num(const std::string &data, size_t &i, size_t &line, size_t &line_start,
			   TokType &num_type, int &base)
{
	size_t len = data.size();
	std::string buf;
	size_t first_digit_at = i;

	int dot_loc = -1;
	base	    = 10;

	bool read_base = false;

	while(i < len) {
		const char c	= CURR;
		const char next = NEXT;
		switch(c) {
		case 'x':
		case 'X': {
			if(read_base) {
				base	  = 16;
				read_base = false;
				break;
			}
			goto fail;
		}
		case 'f':
		case 'F':
		case 'e':
		case 'E':
		case 'd':
		case 'D':
		case 'c':
		case 'C':
		case 'b':
		case 'B':
		case 'a':
		case 'A': {
			if(base >= 16) break;
			goto fail;
		}
		case '9':
		case '8':
			if(base <= 8) base = 10;
			break;
			goto fail;
		case '7':
		case '6':
		case '5':
		case '4':
		case '3':
		case '2':
			if(base > 2) break;
			goto fail;
		case '1': read_base = false; break;
		case '0': {
			if(i == first_digit_at) {
				read_base = true;
				base	  = 8;
				break;
			}
			read_base = false;
			break;
		}
		case '.':
			if(!read_base && base != 10) {
				err::set(line, first_digit_at - line_start, i - line_start,
					 "encountered dot (.) character when base is not 10 (%d) ",
					 base);
				return "";
			} else if(dot_loc == -1) {
				if(next >= '0' && next <= '9') {
					dot_loc	 = i;
					num_type = FLT;
				} else {
					return buf;
				}
			} else {
				err::set(
				line, first_digit_at - line_start, i - line_start,
				"encountered dot (.) character "
				"when the number being retrieved (from column %zu) already had one",
				first_digit_at + 1);
				return "";
			}
			read_base = false;
			base	  = 10;
			break;
		default:
		fail:
			if(isalnum(c)) {
				err::set(line, first_digit_at - line_start, i - line_start,
					 "encountered invalid character '%c' while retrieving a "
					 "number of base %d",
					 c, base);
			} else {
				return buf;
			}
		}
		buf.push_back(c);
		++i;
	}
	return buf;
}

static bool get_const_str(const std::string &data, char &quote_type, size_t &i, size_t &line,
			  size_t &line_start, std::string &buf)
{
	size_t len = data.size();
	buf.clear();
	quote_type		    = CURR;
	int starting_at		    = i;
	size_t continuous_backslash = 0;
	// omit beginning quote
	++i;
	while(i < len) {
		if(CURR == '\n') {
			++line;
			line_start = i + 1;
		}
		if(CURR == '\\') {
			++continuous_backslash;
			buf.push_back(data[i++]);
			continue;
		}
		if(CURR == quote_type && continuous_backslash % 2 == 0) break;
		buf.push_back(data[i++]);
		if(quote_type == '\'') {
			if(CURR != quote_type) {
				err::set(line, starting_at - line_start, i - line_start,
					 "expected single quote for end of const char, found: %c",
					 CURR);
				return false;
			}
			break;
		}
		continuous_backslash = 0;
	}
	if(CURR != quote_type) {
		err::set(line, starting_at - line_start, i - line_start,
			 "no matching quote for '%c' found", quote_type);
		return false;
	}
	// omit ending quote
	++i;
	remove_back_slash(buf);
	return true;
}

static TokType get_operator(const std::string &data, size_t &i, const size_t &line,
			    const size_t &line_start)
{
	size_t len	   = data.size();
	TokType op_type	   = INVALID;
	size_t starting_at = i;
	switch(CURR) {
	case '+':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				SET_OP_TYPE_BRK(ADD_ASSN);
			}
			if(NEXT == '+') {
				++i;
				SET_OP_TYPE_BRK(XINC);
			}
		}
		SET_OP_TYPE_BRK(ADD);
	case '-':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				SET_OP_TYPE_BRK(SUB_ASSN);
			}
			if(NEXT == '-') {
				++i;
				SET_OP_TYPE_BRK(XDEC);
			}
			if(NEXT == '>') {
				++i;
				SET_OP_TYPE_BRK(ARROW);
			}
		}
		SET_OP_TYPE_BRK(SUB);
	case '*':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				if(CURR == '=') op_type = MUL_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK(MUL);
	case '/':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				if(CURR == '=') op_type = DIV_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK(DIV);
	case '%':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				SET_OP_TYPE_BRK(MOD_ASSN);
			}
		}
		SET_OP_TYPE_BRK(MOD);
	case '&':
		if(i < len - 1) {
			if(NEXT == '&' || NEXT == '=') {
				++i;
				if(CURR == '&') op_type = LAND;
				else if(CURR == '=')
					op_type = BAND_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK(BAND);
	case '|':
		if(i < len - 1) {
			if(NEXT == '|' || NEXT == '=') {
				++i;
				if(CURR == '|') op_type = LOR;
				else if(CURR == '=')
					op_type = BOR_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK(BOR);
	case '~':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				SET_OP_TYPE_BRK(BNOT_ASSN);
			}
		}
		SET_OP_TYPE_BRK(BNOT);
	case '=':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				SET_OP_TYPE_BRK(EQ);
			}
		}
		SET_OP_TYPE_BRK(ASSN);
	case '<':
		if(i < len - 1) {
			if(NEXT == '=' || NEXT == '<') {
				++i;
				if(CURR == '=') op_type = LE;
				else if(CURR == '<') {
					if(i < len - 1) {
						if(NEXT == '=') {
							++i;
							SET_OP_TYPE_BRK(LSHIFT_ASSN);
						}
					}
					op_type = LSHIFT;
				}
				break;
			}
		}
		SET_OP_TYPE_BRK(LT);
	case '>':
		if(i < len - 1) {
			if(NEXT == '=' || NEXT == '>') {
				++i;
				if(CURR == '=') op_type = GE;
				else if(CURR == '>') {
					if(i < len - 1) {
						if(NEXT == '=') {
							++i;
							SET_OP_TYPE_BRK(RSHIFT_ASSN);
						}
					}
					op_type = RSHIFT;
				}
				break;
			}
		}
		SET_OP_TYPE_BRK(GT);
	case '!':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				SET_OP_TYPE_BRK(NE);
			}
		}
		SET_OP_TYPE_BRK(LNOT);
	case '^':
		if(i < len - 1) {
			if(NEXT == '=') {
				++i;
				SET_OP_TYPE_BRK(BXOR_ASSN);
			}
		}
		SET_OP_TYPE_BRK(BXOR);
	case ' ': SET_OP_TYPE_BRK(SPC);
	case '\t': SET_OP_TYPE_BRK(TAB);
	case '\n': SET_OP_TYPE_BRK(NEWL);
	case '.':
		if(i < len - 1 && NEXT == '.') {
			++i;
			if(i < len - 1 && NEXT == '.') {
				++i;
				SET_OP_TYPE_BRK(PreVA);
			}
		}
		SET_OP_TYPE_BRK(DOT);
	case '?': SET_OP_TYPE_BRK(QUEST);
	case ':': SET_OP_TYPE_BRK(COL);
	case ',': SET_OP_TYPE_BRK(COMMA);
	case ';': SET_OP_TYPE_BRK(COLS);
	case '@': SET_OP_TYPE_BRK(AT);
	case '(': SET_OP_TYPE_BRK(LPAREN);
	case '[': SET_OP_TYPE_BRK(LBRACK);
	case '{': SET_OP_TYPE_BRK(LBRACE);
	case ')': SET_OP_TYPE_BRK(RPAREN);
	case ']': SET_OP_TYPE_BRK(RBRACK);
	case '}': SET_OP_TYPE_BRK(RBRACE);
	default:
		err::set(line, starting_at - line_start, i - line_start,
			 "unknown operator '%c' found", CURR);
		op_type = INVALID;
	}

	++i;
	return op_type;
}

static void remove_back_slash(std::string &s)
{
	for(auto it = s.begin(); it != s.end(); ++it) {
		if(*it == '\\') {
			if(it + 1 >= s.end()) continue;
			it = s.erase(it);
			if(*it == 'a') *it = '\a';
			else if(*it == 'b')
				*it = '\b';
			else if(*it == 'f')
				*it = '\f';
			else if(*it == 'n')
				*it = '\n';
			else if(*it == 'r')
				*it = '\r';
			else if(*it == 't')
				*it = '\t';
			else if(*it == 'v')
				*it = '\v';
		}
	}
}

std::string view_backslash(const std::string &data)
{
	std::string res = data;
	for(auto it = res.begin(); it != res.end(); ++it) {
		if(*it == '\a') {
			it = res.erase(it);
			res.insert(it - res.begin(), "\\a");
			continue;
		}
		if(*it == '\b') {
			it = res.erase(it);
			res.insert(it - res.begin(), "\\b");
			continue;
		}
		if(*it == '\f') {
			it = res.erase(it);
			res.insert(it - res.begin(), "\\f");
			continue;
		}
		if(*it == '\n') {
			it = res.erase(it);
			res.insert(it - res.begin(), "\\n");
			continue;
		}
		if(*it == '\r') {
			it = res.erase(it);
			res.insert(it - res.begin(), "\\r");
			continue;
		}
		if(*it == '\t') {
			it = res.erase(it);
			res.insert(it - res.begin(), "\\t");
			continue;
		}
		if(*it == '\v') {
			it = res.erase(it);
			res.insert(it - res.begin(), "\\v");
			continue;
		}
	}
	return res;
}
} // namespace lex
} // namespace sc