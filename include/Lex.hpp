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

#ifndef LEX_HPP
#define LEX_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace sc
{
namespace lex
{
/**
 * \brief All valid lexical tokens in the language
 */
enum TokType
{
	INT,
	FLT,

	STR,
	IDEN,

	// Keywords
	LET,
	FN,
	IF,
	ELIF,
	ELSE,
	FOR,
	IN,
	WHILE,
	RETURN,
	CONTINUE,
	BREAK,
	TRUE,
	FALSE,
	NIL,
	OR,
	STATIC,
	CONST,
	VOLATILE,
	EXTERN,
	COMPTIME,
	SELF,
	I8,
	I16,
	I32,
	I64,
	I128,
	U8,
	U16,
	U32,
	U64,
	U128,
	F32,
	F64,

	// Operators
	ASSN,
	// Arithmetic
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	ADD_ASSN,
	SUB_ASSN,
	MUL_ASSN,
	DIV_ASSN,
	MOD_ASSN,
	// Post/Pre Inc/Dec
	XINC,
	INCX,
	XDEC,
	DECX,
	// Unary
	UADD,
	USUB,
	// Logic
	LAND,
	LOR,
	LNOT,
	// Comparison
	EQ,
	LT,
	GT,
	LE,
	GE,
	NE,
	// Bitwise
	BAND,
	BOR,
	BNOT,
	BXOR,
	BAND_ASSN,
	BOR_ASSN,
	BNOT_ASSN,
	BXOR_ASSN,
	// Others
	LSHIFT,
	RSHIFT,
	LSHIFT_ASSN,
	RSHIFT_ASSN,

	// Functions
	OPER_FN,
	OPER_MEM_FN,

	// Subscript
	OPER_SUBS,

	// Varargs
	PreVA,
	PostVA,

	// Separators
	DOT,
	SCOPE,
	COMMA,
	AT,
	SPC,
	TAB,
	NEWL,
	COLS, // Semi colon
	ARROW,
	// Parenthesis, Braces, Brackets
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	LBRACK,
	RBRACK,

	FEOF,
	INVALID,

	_LAST,
};

/**
 * \brief String value of each of the lexical tokens
 */
extern const char *TokStrs[_LAST];

struct Tok
{
	TokType val;

	Tok(const int &tok);

	/**
	 * \brief Check if the token is a variable data
	 *
	 * A 'variable data' consists of ints, floats, const strings, and identifiers
	 *
	 * \return true If the type is one of variable data tokens, false if it isn't
	 */
	inline bool is_data()
	{
		return val == INT || val == FLT || val == STR || val == IDEN || val == TRUE ||
		       val == FALSE || val == NIL || val == PreVA || val == PostVA;
	}

	/**
	 * \brief Check if the token is an operator
	 *
	 * \return true If the type is one of possible operators, false if it isn't
	 */
	inline bool is_oper()
	{
		return val >= ASSN && val <= RBRACK;
	}

	/**
	 * \brief Check if the token is an assignment operator
	 *
	 * \return true If the type is one of possible assignment operators, false if it isn't
	 */
	inline bool is_assign()
	{
		return (val == ASSN || val == ADD_ASSN || val == SUB_ASSN || val == MUL_ASSN ||
			val == DIV_ASSN || val == MOD_ASSN || val == BAND_ASSN || val == BOR_ASSN ||
			val == BNOT_ASSN || val == BXOR_ASSN || val == LSHIFT_ASSN ||
			val == RSHIFT_ASSN);
	}

	/**
	 * \brief Get c-string representation of the token
	 *
	 * \return const char* of the token
	 */
	inline const char *str()
	{
		return TokStrs[val];
	}
};

union Data
{
	struct S
	{
		int type;
		std::string v;
	} s;
	struct I
	{
		int type;
		uint64_t v;
	} i;
	struct F
	{
		int type;
		long double v;
	} f;

	Data(const std::string &v);
	Data(const uint64_t &v);
	Data(const long double &v);
	Data(const Data &data);
	~Data();
};

/**
 * \brief Describes line number, column number,
 * 	  token type, and string data of a token
 */
struct Lexeme
{
	size_t pos;
	Tok tok;
	Data data;

	Lexeme(const size_t &_pos, const TokType &type);
	Lexeme(const size_t &_pos, const std::string &_data);
	Lexeme(const size_t &_pos, const uint64_t &_data);
	Lexeme(const size_t &_pos, const long double &_data);

	std::string str(const size_t &pad = 10);
};

/**
 * \brief Tokenize a given string
 *
 * \param data source string
 * \param toks destination list of tokens to append to
 *
 * \return true if tokenization succeeded, false if failed; sc::err::show() can be used to display
 * 	   errors
 */
bool tokenize(const std::string &data, std::vector<Lexeme> &toks);
} // namespace lex
} // namespace sc

#endif // LEX_HPP