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

#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace sc
{
enum Types
{
	SIMPLE,
	// ENUM,
	STRUCT,
	FUNC,
	EXTERN,
};

struct type_base_t
{
	Types type;
	int64_t id;
	size_t ptr;
	size_t info;
	bool is_templ;
	std::vector<type_base_t *> counts; // for arrays

	type_base_t(const Types &type, const size_t &ptr, const size_t &info, const bool &is_templ);
	type_base_t(const int64_t &id, const Types &type, const size_t &ptr, const size_t &info,
		    const bool &is_templ);
	virtual ~type_base_t();

	inline void add_count(type_base_t *count)
	{
		counts.push_back(count);
	}
};

struct type_simple_t : public type_base_t
{
	std::string name;

	type_simple_t(const size_t &ptr, const size_t &info, const bool &is_templ,
		      const std::string &name);
	type_simple_t(const int64_t &id, const size_t &ptr, const size_t &info,
		      const bool &is_templ, const std::string &name);
};

struct type_struct_t : public type_base_t
{
	bool is_instance;
	std::vector<std::string> templates;
	std::vector<std::string> order;
	std::unordered_map<std::string, type_base_t *> fields;

	type_struct_t(const size_t &ptr, const size_t &info, const bool &is_templ,
		      const std::vector<std::string> &templs, const std::vector<std::string> &order,
		      const std::unordered_map<std::string, type_base_t *> &fields);
	type_struct_t(const int64_t &id, const size_t &ptr, const size_t &info,
		      const bool &is_templ, const std::vector<std::string> &templs,
		      const std::vector<std::string> &order,
		      const std::unordered_map<std::string, type_base_t *> &fields);
};

struct type_func_t : public type_base_t
{
	std::string name;

	type_func_t(const size_t &ptr, const size_t &info, const bool &is_templ,
		    const std::string &name);
	type_func_t(const int64_t &id, const size_t &ptr, const size_t &info, const bool &is_templ,
		    const std::string &name);
};
} // namespace sc

#endif // TYPES_HPP