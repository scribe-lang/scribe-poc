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

namespace sc
{
namespace err
{
static size_t _line    = 0;
static size_t _col_beg = 0;
static size_t _col_end = 0;
static std::string _e  = "";
static int _type       = E_FAIL;

void set(const size_t &line, const size_t &col_beg, const size_t &col_end, const std::string &e,
	 const int &type)
{
	_line	 = line;
	_col_beg = col_beg;
	_col_end = col_end;
	_e	 = e;
	_type	 = E_FAIL;
}
bool present()
{
	return !_e.empty();
}
void show(FILE *out, const std::string &data, const std::string &filename)
{
	size_t line = 0;
	size_t idx  = 0;
	bool found  = false;
	for(size_t i = 0; i < data.size(); ++i) {
		if(line == _line) {
			found = true;
			idx   = i;
			break;
		}
		if(data[i] == '\n') {
			++line;
			continue;
		}
	}
	std::string squiggle('~', _col_end - _col_beg);
	std::string err_line = "<not found>";
	if(found) {
		size_t count = data.find('\n', idx);
		if(count != std::string::npos) count -= idx;
		err_line = data.substr(idx, count);
	}
	fprintf(out, "%s (%zu:%zu): Error: %s\n%s\n%*s\n%*c", filename.c_str(), _line + 1, _col_beg,
		_e.c_str(), err_line.c_str(), (int)_col_beg - 1, squiggle.c_str(),
		(int)_col_beg - 1, '^');
}
} // namespace err
} // namespace sc