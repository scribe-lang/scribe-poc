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
	inline std::unordered_map<std::string, type_base_t *> &get_items()
	{
		return items;
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
	inline VarLayer *get_top()
	{
		return stack.empty() ? nullptr : stack.back();
	}
};
class VarMgr
{
	std::unordered_map<std::string, type_base_t *> globals;
	std::unordered_map<std::string, VarSrc *> srcs;
	// amalgamated ids as string -> function name -> function type
	std::unordered_map<std::string, std::unordered_map<std::string, type_func_t *>> typefns;
	std::vector<VarSrc *> srcstack;

public:
	VarMgr();
	~VarMgr();
	// MUST be called after at least one src has been pushed (pushsrc())
	void init_typefns();
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
	inline VarSrc *get_src(const std::string &src_path)
	{
		return srcs[src_path];
	}
	bool add(const std::string &name, type_base_t *val, const bool &global = false);
	bool add_copy(const std::string &name, type_base_t *val, const bool &global = false);
	bool exists(const std::string &name, const bool &top_only, const bool &with_globals);
	type_base_t *get(const std::string &name);
	type_base_t *get_copy(const std::string &name);

	bool add_type_func(const std::vector<int64_t> &argtypeids, const std::string &name,
			   type_func_t *val);
	bool add_type_func_copy(const std::vector<int64_t> &argtypeids, const std::string &name,
				type_func_t *val);
	type_func_t *get_type_func(const std::vector<int64_t> &argtypeids, const std::string &name);
	bool has_type_func(const std::vector<int64_t> &argtypeids, const std::string &name);

	std::string get_func_type_id(const std::vector<int64_t> &argtypeids);
};
} // namespace parser
} // namespace sc

#endif // PARSER_VAR_MGR_HPP