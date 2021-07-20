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

#include "parser/Intrinsics.hpp"
#include "parser/PrimitiveFuncs.hpp"
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
	globals["void"]	     = new type_simple_t(nullptr, 0, 0, "void");
	globals["nil"]	     = new type_simple_t(nullptr, 0, 0, "i1");
	globals["i1"]	     = new type_simple_t(nullptr, 0, 0, "i1");
	globals["i8"]	     = new type_simple_t(nullptr, 0, 0, "i8");
	globals["i16"]	     = new type_simple_t(nullptr, 0, 0, "i16");
	globals["i32"]	     = new type_simple_t(nullptr, 0, 0, "i32");
	globals["i64"]	     = new type_simple_t(nullptr, 0, 0, "i64");
	globals["u8"]	     = new type_simple_t(nullptr, 0, 0, "u8");
	globals["u16"]	     = new type_simple_t(nullptr, 0, 0, "u16");
	globals["u32"]	     = new type_simple_t(nullptr, 0, 0, "u32");
	globals["u64"]	     = new type_simple_t(nullptr, 0, 0, "u64");
	globals["f32"]	     = new type_simple_t(nullptr, 0, 0, "f32");
	globals["f64"]	     = new type_simple_t(nullptr, 0, 0, "f64");
	globals["*const u8"] = new type_simple_t(nullptr, 1, TypeInfoMask::CONST, "u8"); // cstr

	// intrinsics
	type_simple_t *templ0ptr    = new type_simple_t(nullptr, 1, 0, "@0");
	type_simple_t *templ1ptr    = new type_simple_t(nullptr, 1, 0, "@1");
	type_struct_t *empty_struct = new type_struct_t(nullptr, 0, 0, {}, {}, {});
	type_base_t *cstr	    = globals["*const u8"]->copy();

	type_func_t *importfn = new type_func_t(nullptr, 0, 0, {}, {cstr}, empty_struct);
	importfn->intrin_fn   = intrinsic_import;
	globals["import"]     = importfn;

	type_func_t *asfn = new type_func_t(nullptr, 0, 0, {"@0", "@1"}, {templ1ptr}, templ0ptr);
	asfn->intrin_fn	  = intrinsic_as;
	globals["as"]	  = asfn;

	type_func_t *szfn = new type_func_t(nullptr, 0, 0, {"@0"}, {}, globals["i32"]->copy());
	szfn->intrin_fn	  = intrinsic_szof;
	globals["sizeof"] = szfn;

	type_func_t *typeidfn = new type_func_t(nullptr, 0, 0, {"@0"}, {}, globals["i32"]->copy());
	typeidfn->intrin_fn   = intrinsic_typid;
	globals["typeid"]     = typeidfn;
}
VarMgr::~VarMgr()
{
	for(auto &g : globals) delete g.second;
	for(auto &s : srcs) delete s.second;
	for(auto &tf : typefns) {
		for(auto &f : tf.second) delete f.second;
	}
}
void VarMgr::init_typefns()
{
	add_primitive_integer_funcs("i1", *this);
	add_primitive_integer_funcs("i8", *this);
	add_primitive_integer_funcs("i16", *this);
	add_primitive_integer_funcs("i32", *this);
	add_primitive_integer_funcs("i64", *this);
	add_primitive_integer_funcs("u8", *this);
	add_primitive_integer_funcs("u16", *this);
	add_primitive_integer_funcs("u32", *this);
	add_primitive_integer_funcs("u64", *this);
	add_primitive_integer_funcs("f32", *this);
	add_primitive_integer_funcs("f64", *this);
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

bool VarMgr::add_type_func(const std::vector<int64_t> &argtypeids, const std::string &name,
			   type_func_t *val)
{
	std::string id = get_func_type_id(argtypeids);
	if(typefns[id].find(name) != typefns[id].end()) {
		return false;
	}
	typefns[id][name] = val;
	return true;
}
bool VarMgr::add_type_func_copy(const std::vector<int64_t> &argtypeids, const std::string &name,
				type_func_t *val)
{
	std::string id = get_func_type_id(argtypeids);
	if(typefns[id].find(name) != typefns[id].end()) return false;
	typefns[id][name] = static_cast<type_func_t *>(val->copy());
	return true;
}
type_func_t *VarMgr::get_type_func(const std::vector<int64_t> &argtypeids, const std::string &name)
{
	std::string id = get_func_type_id(argtypeids);
	auto res       = typefns[id].find(name);
	if(res == typefns[id].end()) return nullptr;
	return res->second;
}
bool VarMgr::has_type_func(const std::vector<int64_t> &argtypeids, const std::string &name)
{
	std::string id = get_func_type_id(argtypeids);
	return typefns.find(id) != typefns.end() && typefns[id].find(name) != typefns[id].end();
}

std::string VarMgr::get_func_type_id(const std::vector<int64_t> &argtypeids)
{
	std::string res;
	for(auto &i : argtypeids) {
		res += std::to_string(i);
	}
	return res;
}
} // namespace parser
} // namespace sc