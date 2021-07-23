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

#include <map>
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
	bool exists(const std::string &name, const size_t &locked_from, const bool &top_only);
	type_base_t *get(const std::string &name, const size_t &locked_from);
	inline VarLayer *get_top()
	{
		return stack.empty() ? nullptr : stack.back();
	}

	inline std::vector<VarLayer *> &get_layers()
	{
		return stack;
	}
};
class VarMgr
{
	std::unordered_map<std::string, size_t> srcids;
	std::unordered_map<size_t, std::string> srcfiles;
	std::unordered_map<std::string, type_base_t *> globals;
	std::unordered_map<size_t, VarSrc *> srcs;
	std::map<size_t, stmt_base_t *> managedptrees;
	std::vector<VarSrc *> srcstack;
	std::vector<size_t> srcidstack;
	std::vector<type_funcmap_t *> managedfnmaps;
	// types that function returns (for type checking return statement)
	std::vector<type_base_t *> funcreturns;
	std::vector<size_t> lockedlayers;
	bool init_typefuncs_called; // init_typefns() has been called or not

public:
	VarMgr();
	~VarMgr();
	// MUST be called after at least one src has been pushed (pushsrc())
	void init_typefns();
	inline bool init_typefns_called()
	{
		return init_typefuncs_called;
	}
	inline void pushlayer()
	{
		srcstack.back()->pushlayer();
	}
	inline void poplayer()
	{
		srcstack.back()->poplayer();
	}
	inline size_t getlayer()
	{
		return srcstack.back()->get_layers().size() - 1;
	}
	inline void addsrc(const size_t &src_id)
	{
		srcs[src_id] = new VarSrc;
	}
	bool pushsrc(const size_t &src_id);
	void popsrc();
	inline size_t current_src()
	{
		return srcidstack.back();
	}
	inline bool src_exists(const size_t &src_id)
	{
		return srcs.find(src_id) != srcs.end();
	}
	inline VarSrc *get_src(const size_t &src_id)
	{
		return srcs[src_id];
	}
	bool add(const std::string &name, type_base_t *val, const bool &global = false);
	bool add_copy(const std::string &name, type_base_t *val, const bool &global = false);
	bool exists(const std::string &name, const bool &top_only, const bool &with_globals);
	type_base_t *get(const std::string &name, stmt_base_t *parent);
	type_base_t *get_copy(const std::string &name, stmt_base_t *parent);
	void lock_scopes_before(const size_t &idx)
	{
		lockedlayers.push_back(idx);
	}
	inline void unlock_scope()
	{
		lockedlayers.pop_back();
	}

	bool add_func(const std::string &name, type_base_t *vtyp, const bool &global = false);
	bool add_func_copy(const std::string &name, type_base_t *vtyp, const bool &global = false);
	type_funcmap_t *get_funcmap(const std::string &name, stmt_base_t *parent);
	type_funcmap_t *get_funcmap_copy(const std::string &name, stmt_base_t *parent);

	inline void pushfret(type_base_t *fnret)
	{
		funcreturns.push_back(fnret);
	}
	inline void popfret()
	{
		funcreturns.pop_back();
	}
	inline type_base_t *getfret()
	{
		return funcreturns.back();
	}
	inline bool hasfret()
	{
		return !funcreturns.empty();
	}

	inline void manage_ptree(const size_t &src_id, stmt_base_t *tree)
	{
		managedptrees[src_id] = tree;
	}
	inline std::map<size_t, stmt_base_t *> &get_managed_ptrees()
	{
		return managedptrees;
	}
	inline stmt_base_t *get_managed_ptree(const size_t &src_id)
	{
		if(managedptrees.find(src_id) == managedptrees.end()) return nullptr;
		return managedptrees[src_id];
	}

	size_t get_src_id(const std::string &src_path);
	std::string get_src_path(const size_t &src_id);
};
} // namespace parser
} // namespace sc

#endif // PARSER_VAR_MGR_HPP