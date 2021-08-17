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

#ifndef PARSER_TYPEMGR_HPP
#define PARSER_TYPEMGR_HPP

#include <map>
#include <string>
#include <unordered_map>

#include "Type.hpp"
#include "ValueMgr.hpp"

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
class TypeMgr
{
	RAIIParser *parser;
	std::unordered_map<std::string, Type *> globals;
	std::vector<LayerTypes *> stack;
	std::vector<TypeFuncMap *> managedfnmaps;
	// current function type (for type checking return statement, checking comptime, etc.)
	std::vector<TypeFunc *> funcstack;
	std::vector<size_t> lockedlayers;
	ValueMgr vals;
	bool init_typefuncs_called; // initTypeFuncs() has been called or not

public:
	TypeMgr(RAIIParser *parser);
	~TypeMgr();
	// MUST be called after at least one src has been pushed (pushModule())
	void initTypeFuncs();
	inline bool initTypeFuncsCalled()
	{
		return init_typefuncs_called;
	}
	inline RAIIParser *getParser()
	{
		return parser;
	}
	inline void pushLayer()
	{
		stack.push_back(new LayerTypes);
	}
	inline void popLayer()
	{
		delete stack.back();
		stack.pop_back();
	}
	inline size_t getLayer()
	{
		return stack.size() - 1;
	}
	bool add(const std::string &name, Type *val, const bool &global = false);
	bool addCopy(const std::string &name, Type *val, const bool &global = false);
	bool exists(const std::string &name, const bool &top_only, const bool &with_globals);
	// if parent is nullptr, parent will not be updated and will be the same as before
	// non copy version of this function DOES NOT update the parent if the result is a variable
	// and not a function
	Type *get(const std::string &name);
	// if parent is nullptr, parent will not be updated and will be the same as before
	Type *getCopy(const std::string &name, Stmt *parent);
	void lockScopesBefore(const size_t &idx)
	{
		lockedlayers.push_back(idx);
	}
	inline void unlockScope()
	{
		lockedlayers.pop_back();
	}

	bool addFunc(const std::string &name, Type *vtyp, const bool &global = false);
	bool addFuncCopy(const std::string &name, Type *vtyp, const bool &global = false);
	// if parent is nullptr, parent will not be updated and will be the same as before
	TypeFuncMap *getFuncMap(const std::string &name, Stmt *parent);
	// if parent is nullptr, parent will not be updated and will be the same as before
	TypeFuncMap *getFuncMapCopy(const std::string &name, Stmt *parent);

	inline void pushFunc(TypeFunc *fn)
	{
		funcstack.push_back(fn);
	}
	inline void popFunc()
	{
		funcstack.pop_back();
	}
	inline TypeFunc *getFunc()
	{
		return funcstack.back();
	}
	inline bool hasFunc()
	{
		return !funcstack.empty();
	}
};
} // namespace parser
} // namespace sc

#endif // PARSER_TYPEMGR_HPP