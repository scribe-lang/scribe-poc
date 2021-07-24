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
class RAIIParser;

class LayerTypes
{
	std::unordered_map<std::string, Type *> items;

public:
	~LayerTypes();
	inline bool add(const std::string &name, Type *val)
	{
		if(exists(name)) return false;
		items[name] = val;
		return true;
	}
	inline bool exists(const std::string &name)
	{
		return items.find(name) != items.end();
	}
	inline Type *get(const std::string &name)
	{
		return items.find(name) == items.end() ? nullptr : items[name];
	}
	inline std::unordered_map<std::string, Type *> &get_items()
	{
		return items;
	}
};
class SrcTypes
{
	std::vector<LayerTypes *> stack;

public:
	~SrcTypes();
	inline void pushlayer()
	{
		stack.push_back(new LayerTypes);
	};
	inline void poplayer()
	{
		delete stack.back();
		stack.pop_back();
	}
	bool add(const std::string &name, Type *val);
	bool exists(const std::string &name, const size_t &locked_from, const bool &top_only);
	Type *get(const std::string &name, const size_t &locked_from);
	inline LayerTypes *get_top()
	{
		return stack.empty() ? nullptr : stack.back();
	}

	inline std::vector<LayerTypes *> &get_layers()
	{
		return stack;
	}
};
class TypeMgr
{
	RAIIParser *parser;
	std::unordered_map<std::string, Type *> globals;
	std::unordered_map<size_t, SrcTypes *> srcs;
	std::vector<SrcTypes *> srcstack;
	std::vector<size_t> srcidstack;
	std::vector<TypeFuncMap *> managedfnmaps;
	// types that function returns (for type checking return statement)
	std::vector<Type *> funcreturns;
	std::vector<size_t> lockedlayers;
	bool init_typefuncs_called; // init_typefns() has been called or not

public:
	TypeMgr(RAIIParser *parser);
	~TypeMgr();
	// MUST be called after at least one src has been pushed (pushsrc())
	void init_typefns();
	inline bool init_typefns_called()
	{
		return init_typefuncs_called;
	}
	inline RAIIParser *get_parser()
	{
		return parser;
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
		srcs[src_id] = new SrcTypes;
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
	inline SrcTypes *get_src(const size_t &src_id)
	{
		return srcs[src_id];
	}
	bool add(const std::string &name, Type *val, const bool &global = false);
	bool add_copy(const std::string &name, Type *val, const bool &global = false);
	bool exists(const std::string &name, const bool &top_only, const bool &with_globals);
	Type *get(const std::string &name, Stmt *parent);
	Type *get_copy(const std::string &name, Stmt *parent);
	void lock_scopes_before(const size_t &idx)
	{
		lockedlayers.push_back(idx);
	}
	inline void unlock_scope()
	{
		lockedlayers.pop_back();
	}

	bool add_func(const std::string &name, Type *vtyp, const bool &global = false);
	bool add_func_copy(const std::string &name, Type *vtyp, const bool &global = false);
	TypeFuncMap *get_funcmap(const std::string &name, Stmt *parent);
	TypeFuncMap *get_funcmap_copy(const std::string &name, Stmt *parent);

	inline void pushfret(Type *fnret)
	{
		funcreturns.push_back(fnret);
	}
	inline void popfret()
	{
		funcreturns.pop_back();
	}
	inline Type *getfret()
	{
		return funcreturns.back();
	}
	inline bool hasfret()
	{
		return !funcreturns.empty();
	}
};
} // namespace parser
} // namespace sc

#endif // PARSER_VAR_MGR_HPP