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

#include "parser/VarMgr.hpp"

#include "parser/Stmts.hpp"

namespace sc
{
namespace parser
{
VarLayer::~VarLayer()
{
	for(auto &i : items) delete i.second;
}

VarSrc::~VarSrc()
{
	for(auto &s : stack) delete s;
}
bool VarSrc::add(const std::string &name, type_base_t *val)
{
	return stack.back()->add(name, val);
}
bool VarSrc::exists(const std::string &name, const bool &top_only)
{
	if(top_only) return stack.back()->exists(name);
	for(auto rit = stack.rbegin(); rit != stack.rend(); ++rit) {
		if((*rit)->exists(name)) return true;
	}
	return false;
}
type_base_t *VarSrc::get(const std::string &name)
{
	for(auto rit = stack.rbegin(); rit != stack.rend(); ++rit) {
		type_base_t *res = (*rit)->get(name);
		if(res) return res;
	}
	return nullptr;
}

VarMgr::VarMgr()
{
	globals["void"]	     = new type_simple_t(0, 0, "void");
	globals["i1"]	     = new type_simple_t(0, 0, "i1");
	globals["i8"]	     = new type_simple_t(0, 0, "i8");
	globals["i16"]	     = new type_simple_t(0, 0, "i16");
	globals["i32"]	     = new type_simple_t(0, 0, "i32");
	globals["i64"]	     = new type_simple_t(0, 0, "i64");
	globals["u8"]	     = new type_simple_t(0, 0, "u8");
	globals["u16"]	     = new type_simple_t(0, 0, "u16");
	globals["u32"]	     = new type_simple_t(0, 0, "u32");
	globals["u64"]	     = new type_simple_t(0, 0, "u64");
	globals["f32"]	     = new type_simple_t(0, 0, "f32");
	globals["f64"]	     = new type_simple_t(0, 0, "f64");
	globals["*const u8"] = new type_simple_t(1, TypeInfoMask::CONST, "u8"); // cstr

	// intrinsics
	type_simple_t *templ0	 = new type_simple_t(0, 0, "@0");
	type_simple_t *templ0ptr = new type_simple_t(1, 0, "@0");
	type_simple_t *templ1ptr = new type_simple_t(1, 0, "@1");
	type_base_t *cstr	 = globals["*const u8"]->copy();
	globals["import"] = new type_func_t(0, 0, {}, {cstr}, new type_struct_t(0, 0, {}, {}, {}));
	globals["as"]	  = new type_func_t(0, 0, {"@0", "@1"}, {templ1ptr}, templ0ptr);
	globals["sizeof"] = new type_func_t(0, 0, {"@0"}, {templ0}, globals["i32"]->copy());
	globals["typeid"] = new type_func_t(0, 0, {"@0"}, {templ0->copy()}, globals["i32"]->copy());
}
VarMgr::~VarMgr()
{
	for(auto &g : globals) delete g.second;
	for(auto &s : srcs) delete s.second;
}
bool VarMgr::pushsrc(const std::string &path)
{
	if(!src_exists(path)) return false;
	srcstack.push_back(srcs[path]);
	return true;
}
void VarMgr::popsrc()
{
	srcstack.pop_back();
}
bool VarMgr::add(const std::string &name, type_base_t *val, const bool &global)
{
	if(global) {
		if(globals.find(name) != globals.end()) return false;
		globals[name] = val->copy();
		return true;
	}
	return srcstack.back()->add(name, val);
}
bool VarMgr::add_copy(const std::string &name, type_base_t *val, const bool &global)
{
	type_base_t *cp = val->copy();
	if(!add(name, cp, global)) {
		delete cp;
		return false;
	}
	return true;
}
bool VarMgr::exists(const std::string &name, const bool &top_only, const bool &with_globals)
{
	if(srcstack.back()->exists(name, top_only)) return true;
	return with_globals ? globals.find(name) != globals.end() : false;
}
type_base_t *VarMgr::get(const std::string &name)
{
	type_base_t *res = srcstack.back()->get(name);
	if(res) return res;
	auto gres = globals.find(name);
	if(gres != globals.end()) return gres->second;
	return nullptr;
}
type_base_t *VarMgr::get_copy(const std::string &name)
{
	type_base_t *res = get(name);
	if(!res) return nullptr;
	return res->copy();
}
} // namespace parser
} // namespace sc