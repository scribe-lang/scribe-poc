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

#ifndef PARSER_VAR_MGR_HPP
#define PARSER_VAR_MGR_HPP

#include <string>
#include <unordered_map>

#include "Type.hpp"

namespace sc
{
namespace parser
{
class VarLayer
{
	std::unordered_map<std::string, type_base_t *> items;

public:
	~VarLayer();
	inline bool add(const std::string &name, type_base_t *val)
	{
		if(exists(name)) return false;
		items[name] = val;
		return true;
	}
	inline bool exists(const std::string &name)
	{
		return items.find(name) != items.end();
	}
	inline type_base_t *get(const std::string &name)
	{
		return items.find(name) == items.end() ? nullptr : items[name];
	}
};
class VarSrc
{
	std::vector<VarLayer *> stack;

public:
	~VarSrc();
	inline void pushlayer()
	{
		stack.push_back(new VarLayer);
	};
	inline void poplayer()
	{
		delete stack.back();
		stack.pop_back();
	}
	bool add(const std::string &name, type_base_t *val);
	bool exists(const std::string &name, const bool &top_only);
	type_base_t *get(const std::string &name);
};
class VarMgr
{
	std::unordered_map<std::string, type_base_t *> globals;
	std::unordered_map<std::string, VarSrc *> srcs;
	std::vector<VarSrc *> srcstack;

public:
	VarMgr();
	~VarMgr();
	inline void pushlayer()
	{
		srcstack.back()->pushlayer();
	}
	inline void poplayer()
	{
		srcstack.back()->poplayer();
	}
	inline void addsrc(const std::string &src_path)
	{
		srcs[src_path] = new VarSrc;
	}
	bool pushsrc(const std::string &path);
	void popsrc();
	inline bool src_exists(const std::string &src_path)
	{
		return srcs.find(src_path) != srcs.end();
	}
	// creates a copy of val
	bool add(const std::string &name, type_base_t *val, const bool &global = false);
	bool add_copy(const std::string &name, type_base_t *val, const bool &global = false);
	bool exists(const std::string &name, const bool &top_only, const bool &with_globals);
	type_base_t *get(const std::string &name);
	type_base_t *get_copy(const std::string &name);
};
} // namespace parser
} // namespace sc

#endif // PARSER_VAR_MGR_HPP