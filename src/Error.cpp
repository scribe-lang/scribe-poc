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
static std::vector<size_t> _line;
static std::vector<size_t> _col_beg;
static std::vector<size_t> _col_end;
static std::vector<std::string> _e;
static std::vector<EType> _type;

void set(const size_t &line, const size_t &col_beg, const size_t &col_end, const std::string &e,
	 const EType &type)
{
	_line.insert(_line.begin(), line);
	_col_beg.insert(_col_beg.begin(), col_beg);
	_col_end.insert(_col_end.begin(), col_end);
	_e.insert(_e.begin(), e);
	_type.insert(_type.begin(), type);
}
bool present()
{
	return !_e.empty();
}
void show(FILE *out, const std::string &data, const std::string &filename)
{
	while(!_e.empty()) {
		const size_t &__line	= _line.back();
		const size_t &__col_beg = _col_beg.back();
		const size_t &__col_end = _col_end.back();
		const std::string &__e	= _e.back();
		const EType &__type	= _type.back();
		size_t line		= 0;
		size_t idx		= 0;
		bool found		= false;

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
		std::string squiggle(__col_end - __col_beg, '~');
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
		std::string spacing_squiggle(__col_beg, ' ');
		std::string spacing_caret(__col_beg /* + 1 for single character '^' */, ' ');
		while(tab_count--) {
			spacing_squiggle.pop_back();
			spacing_caret.pop_back();
			spacing_squiggle.insert(spacing_squiggle.begin(), '\t');
			spacing_caret.insert(spacing_caret.begin(), '\t');
		}

		std::string type;
		switch(__type) {
		case WARN: type = "Warning"; break;
		case FAIL: type = "Failure"; break;
		}
		fprintf(out, "%s (%zu:%zu): %s: %s\n%s\n%s%s\n%s%c\n", filename.c_str(), __line + 1,
			__col_beg + 1, type.c_str(), __e.c_str(), err_line.c_str(),
			spacing_squiggle.c_str(), squiggle.c_str(), spacing_caret.c_str(), '^');

		_line.pop_back();
		_col_beg.pop_back();
		_col_end.pop_back();
		_e.pop_back();
		_type.pop_back();
	}
}
} // namespace err
} // namespace sc