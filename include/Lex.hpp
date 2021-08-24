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

	CHAR,
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
	INLINE,
	STRUCT,
	ENUM,

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
	UAND, // address of
	UMUL, // dereference
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

	SUBS,

	FNCALL,

	// Empty operator - used in expr to show only LHS (no RHS)
	EMPTY,

	// Varargs
	PreVA,
	PostVA,

	// Separators
	DOT,
	QUEST,
	COL,
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
	inline bool isData() const
	{
		return val == INT || val == FLT || val == CHAR || val == STR || val == IDEN ||
		       val == TRUE || val == FALSE || val == NIL;
	}

	/**
	 * \brief Check if the token is an operator
	 *
	 * \return true If the type is one of possible operators, false if it isn't
	 */
	inline bool isOper() const
	{
		return val >= ASSN && val <= RBRACK;
	}

	/**
	 * \brief Check if the token is a unary pre operator
	 *
	 * \return true If the type is one of possible unary pre operators, false if it isn't
	 */
	inline bool isUnaryPre() const
	{
		return val == UADD || val == USUB || val == UAND || val == UMUL || val == INCX ||
		       val == DECX;
	}

	/**
	 * \brief Check if the token is a unary post operator
	 *
	 * \return true If the type is one of possible unary post operators, false if it isn't
	 */
	inline bool isUnaryPost() const
	{
		return val == XINC || val == XDEC;
	}

	/**
	 * \brief Check if the token is an assignment operator
	 *
	 * \return true If the type is one of possible assignment operators, false if it isn't
	 */
	inline bool isAssign() const
	{
		return (val == ASSN || val == ADD_ASSN || val == SUB_ASSN || val == MUL_ASSN ||
			val == DIV_ASSN || val == MOD_ASSN || val == BAND_ASSN || val == BOR_ASSN ||
			val == BNOT_ASSN || val == BXOR_ASSN || val == LSHIFT_ASSN ||
			val == RSHIFT_ASSN);
	}

	/**
	 * \brief Check if the token is valid
	 *
	 * \return true If valid, false if not
	 */
	inline bool isValid() const
	{
		return val != INVALID && val != FEOF;
	}

	/**
	 * \brief Get c-string representation of the token
	 *
	 * \return const char* of the token
	 */
	inline const char *cstr() const
	{
		return TokStrs[val];
	}
	/**
	 * \brief Get string representation of the token
	 *
	 * \return std::string of the token
	 */
	inline std::string str() const
	{
		return TokStrs[val];
	}

	/**
	 * \brief Get string (identifier) representation of an operator
	 *
	 * \return const char * of the operator
	 */
	const char *getOperCStr() const;

	/**
	 * \brief Get the non character containing representation of the unary operator
	 *        For example: instead of '++x' or 'x++, '++' will be returned
	 *
	 * \return true If the type is one of possible unary post operators, false if it isn't
	 */
	const char *getUnaryNoCharCStr() const;

	inline bool operator==(Tok &other) const
	{
		return val == other.val;
	}
};

struct Data
{
	std::string s;
	int64_t i;
	long double f;

	bool cmp(Data &other, TokType type);
};

/**
 * \brief Describes line number, column number,
 * 	  token type, and string data of a token
 */
struct Lexeme
{
	size_t line;
	size_t col_beg;
	size_t col_end;
	Tok tok;
	Data data;

	Lexeme();
	explicit Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
			const TokType &type);
	explicit Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
			const TokType &type, const std::string &_data);
	explicit Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
			const int64_t &_data);
	explicit Lexeme(const size_t &line, const size_t &col_beg, const size_t &col_end,
			const long double &_data);

	std::string str(const int64_t &pad = 10);

	inline bool operator==(Lexeme &other)
	{
		return tok == other.tok && data.cmp(other.data, tok.val);
	}
	inline bool operator!=(Lexeme &other)
	{
		return *this == other ? false : true;
	}
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