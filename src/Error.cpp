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

#include <cstring>

namespace sc
{
namespace err
{
static std::vector<parser::Module *> currmod;
static std::vector<parser::Module *> _mod;
static std::vector<size_t> _line;
static std::vector<size_t> _col_beg;
static std::vector<size_t> _col_end;
static std::vector<std::string> _e;
static std::vector<bool> _warn;

void pushModule(parser::Module *mod)
{
	currmod.push_back(mod);
}
void popModule()
{
	currmod.pop_back();
}
void set(parser::Stmt *stmt, const char *e, ...)
{
	va_list args;
	va_start(args, e);
	set(stmt->mod, stmt->line, stmt->col, stmt->col, e, args);
	va_end(args);
}
void set(const lex::Lexeme &tok, const char *e, ...)
{
	va_list args;
	va_start(args, e);
	set(nullptr, tok.line, tok.col_beg, tok.col_end, e, args);
	va_end(args);
}
void set(const size_t &line, const size_t &col_beg, const size_t &col_end, const char *e, ...)
{
	va_list args;
	va_start(args, e);
	set(nullptr, line, col_beg, col_end, e, args);
	va_end(args);
}
void set(parser::Module *mod, const size_t &line, const size_t &col_beg, const size_t &col_end,
	 const char *e, va_list args)
{
	_mod.insert(_mod.begin(), mod == nullptr ? currmod.back() : mod);
	_line.insert(_line.begin(), line);
	_col_beg.insert(_col_beg.begin(), col_beg);
	_col_end.insert(_col_end.begin(), col_end);
	_warn.insert(_warn.begin(), false);

	static char msg[4096];
	std::memset(msg, 0, 4096);
	vsprintf(msg, e, args);
	_e.insert(_e.begin(), msg);
}

// equivalent to set(), but for warnings
void setw(parser::Stmt *stmt, const char *e, ...)
{
	va_list args;
	va_start(args, e);
	setw(stmt->mod, stmt->line, stmt->col, stmt->col, e, args);
	va_end(args);
}
void setw(const lex::Lexeme &tok, const char *e, ...)
{
	va_list args;
	va_start(args, e);
	setw(nullptr, tok.line, tok.col_beg, tok.col_end, e, args);
	va_end(args);
}
void setw(const size_t &line, const size_t &col_beg, const size_t &col_end, const char *e, ...)
{
	va_list args;
	va_start(args, e);
	setw(nullptr, line, col_beg, col_end, e, args);
	va_end(args);
}
void setw(parser::Module *mod, const size_t &line, const size_t &col_beg, const size_t &col_end,
	  const char *e, va_list args)
{
	_mod.insert(_mod.begin(), mod == nullptr ? currmod.back() : mod);
	_line.insert(_line.begin(), line);
	_col_beg.insert(_col_beg.begin(), col_beg);
	_col_end.insert(_col_end.begin(), col_end);
	_warn.insert(_warn.begin(), true);

	static char msg[4096];
	std::memset(msg, 0, 4096);
	vsprintf(msg, e, args);
	_e.insert(_e.begin(), msg);
}

bool present()
{
	return !_e.empty();
}
void show(FILE *out)
{
	while(!_e.empty()) {
		parser::Module *__mod	= _mod.back();
		const size_t &__line	= _line.back();
		const size_t &__col_beg = _col_beg.back();
		const size_t &__col_end = _col_end.back();
		const bool &__warn	= _warn.back();
		const std::string &__e	= _e.back();
		size_t line		= 0;
		size_t idx		= 0;
		bool found		= false;

		const std::string &data	    = __mod->getCode();
		const std::string &filename = __mod->getPath();

		for(size_t i = 0; i < data.size(); ++i) {
			if(line == __line) {
				found = true;
				idx   = i;
				break;
			}
			if(data[i] == '\n') {
				++line;
				continue;
			}
		}
		std::string err_line = "<not found>";
		if(found) {
			size_t count = data.find('\n', idx);
			if(count != std::string::npos) count -= idx;
			err_line = data.substr(idx, count);
		}

		size_t tab_count = 0;
		for(auto &c : err_line) {
			if(c == '\t') ++tab_count;
		}
		std::string spacing_caret(__col_beg /* + 1 for single character '^' */, ' ');
		while(tab_count--) {
			spacing_caret.pop_back();
			spacing_caret.insert(spacing_caret.begin(), '\t');
		}

		fprintf(out, "%s (%zu:%zu): %s: %s\n%s\n%s%c\n", filename.c_str(), __line + 1,
			__col_beg + 1, __warn ? "Warning" : "Failure", __e.c_str(),
			err_line.c_str(), spacing_caret.c_str(), '^');

		_mod.pop_back();
		_line.pop_back();
		_col_beg.pop_back();
		_col_end.pop_back();
		_e.pop_back();
	}
}
void reset()
{
	_mod.clear();
	_line.clear();
	_col_beg.clear();
	_col_end.clear();
	_e.clear();
	_warn.clear();
}
} // namespace err
} // namespace sc