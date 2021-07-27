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

#include "parser/TypeMgr.hpp"

#include "Parser.hpp"
#include "parser/Intrinsics.hpp"
#include "parser/PrimitiveFuncs.hpp"
#include "parser/Stmts.hpp"

static size_t gen_src_id()
{
	static size_t id = 0;
	return ++id;
}

namespace sc
{
namespace parser
{
LayerTypes::~LayerTypes()
{
	for(auto &i : items) delete i.second;
}

SrcTypes::~SrcTypes()
{
	for(auto &s : stack) delete s;
}
bool SrcTypes::add(const std::string &name, Type *val)
{
	return stack.back()->add(name, val);
}
bool SrcTypes::exists(const std::string &name, const size_t &locked_from, const bool &top_only)
{
	if(top_only) return stack.back()->exists(name);
	for(size_t i = 0; i < stack.size(); ++i) {
		if(i < locked_from) continue;
	}
	size_t i = stack.size() - 1;
	for(auto rit = stack.rbegin(); rit != stack.rend(); ++rit) {
		if(locked_from != size_t(-1) && i <= locked_from) break;
		if((*rit)->exists(name)) return true;
		--i;
	}
	return false;
}
Type *SrcTypes::get(const std::string &name, const size_t &locked_from)
{
	size_t i = stack.size() - 1;
	for(auto rit = stack.rbegin(); rit != stack.rend(); ++rit) {
		if(locked_from != size_t(-1) && i <= locked_from) break;
		Type *res = (*rit)->get(name);
		if(res) return res;
		--i;
	}
	return nullptr;
}

TypeMgr::TypeMgr(RAIIParser *parser) : parser(parser), vals(parser), init_typefuncs_called(false)
{
	globals["any"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "any");
	globals["void"] = new TypeSimple(nullptr, 0, 0, vals.get(VVOID), "void");
	globals["i1"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "i1");
	globals["i8"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "i8");
	globals["i16"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "i16");
	globals["i32"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "i32");
	globals["i64"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "i64");
	globals["u8"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "u8");
	globals["u16"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "u16");
	globals["u32"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "u32");
	globals["u64"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "u64");
	globals["f32"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "f32");
	globals["f64"]	= new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "f64");
	globals["*const u8"] =
	new TypeSimple(nullptr, 1, TypeInfoMask::CONST, vals.get(VUNKNOWN), "u8"); // cstr
	globals["nil"] = globals["i1"]->copy();

	// intrinsics
	TypeSimple *templ0 = new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "@0");
	TypeSimple *templ1 = new TypeSimple(nullptr, 0, 0, vals.get(VUNKNOWN), "@1");
	TypeStruct *empty_struct =
	new TypeStruct(nullptr, 0, 0, vals.get(VUNKNOWN), false, {}, {}, {});
	Type *cstr = globals["*const u8"]->copy();

	TypeFunc *importfn =
	new TypeFunc(nullptr, 0, 0, vals.get(VUNKNOWN), 0, 0, false, {cstr}, empty_struct);
	importfn->intrin_fn = intrinsic_import;
	globals["import"]   = importfn;

	TypeFunc *asfn =
	new TypeFunc(nullptr, 0, 0, vals.get(VUNKNOWN), 0, 2, false, {templ1}, templ0);
	asfn->intrin_fn = intrinsic_as;
	globals["as"]	= asfn;

	TypeFunc *szfn =
	new TypeFunc(nullptr, 0, 0, vals.get(VUNKNOWN), 0, 1, false, {}, globals["i32"]->copy());
	szfn->intrin_fn	  = intrinsic_szof;
	globals["sizeof"] = szfn;

	TypeFunc *typeidfn =
	new TypeFunc(nullptr, 0, 0, vals.get(VUNKNOWN), 0, 1, false, {}, globals["i32"]->copy());
	typeidfn->intrin_fn = intrinsic_typid;
	globals["typeid"]   = typeidfn;

	TypeFunc *valenfn =
	new TypeFunc(nullptr, 0, 0, vals.get(VUNKNOWN), 0, 0, false, {}, globals["i32"]->copy());
	valenfn->intrin_fn = intrinsic_va_len;
	globals["va_len"]  = valenfn;
}
TypeMgr::~TypeMgr()
{
	for(auto &g : globals) delete g.second;
	for(auto &s : srcs) delete s.second;
	for(auto &mfn : managedfnmaps) delete mfn;
}
void TypeMgr::init_typefns()
{
	add_primitive_integer_funcs(*this);

	init_typefuncs_called = true;
}
bool TypeMgr::pushsrc(const size_t &src_id)
{
	if(!src_exists(src_id)) return false;
	srcstack.push_back(srcs[src_id]);
	srcidstack.push_back(src_id);
	return true;
}
void TypeMgr::popsrc()
{
	srcstack.pop_back();
	srcidstack.pop_back();
}
bool TypeMgr::add(const std::string &name, Type *val, const bool &global)
{
	if(global) {
		if(globals.find(name) != globals.end()) return false;
		globals[name] = val;
		return true;
	}
	return srcstack.back()->add(name, val);
}
bool TypeMgr::add_copy(const std::string &name, Type *val, const bool &global)
{
	Type *cp = val->copy();
	if(!add(name, cp, global)) {
		delete cp;
		return false;
	}
	return true;
}
bool TypeMgr::exists(const std::string &name, const bool &top_only, const bool &with_globals)
{
	size_t lock_from = lockedlayers.size() > 0 ? lockedlayers.back() : size_t(-1);
	if(srcstack.back()->exists(name, lock_from, top_only)) return true;
	return with_globals ? globals.find(name) != globals.end() : false;
}
Type *TypeMgr::get(const std::string &name, Stmt *parent)
{
	size_t lock_from = lockedlayers.size() > 0 ? lockedlayers.back() : size_t(-1);
	Type *res	 = srcstack.back()->get(name, lock_from);
	if(res) return res;
	auto gres = globals.find(name);
	if(gres != globals.end()) return gres->second;
	return get_funcmap(name, parent);
}
Type *TypeMgr::get_copy(const std::string &name, Stmt *parent)
{
	Type *res = get(name, parent);
	if(!res) return nullptr;
	return res->copy();
}
bool TypeMgr::add_func(const std::string &name, Type *vtyp, const bool &global)
{
	std::string fullname = name + "_" + vtyp->mangled_name();
	return add(fullname, vtyp, global);
}
bool TypeMgr::add_func_copy(const std::string &name, Type *vtyp, const bool &global)
{
	std::string fullname = name + "_" + vtyp->mangled_name();
	return add_copy(fullname, vtyp, global);
}
TypeFuncMap *TypeMgr::get_funcmap(const std::string &name, Stmt *parent)
{
	TypeFuncMap *res = get_funcmap_copy(name, parent);
	if(!res) return nullptr;
	managedfnmaps.push_back(res);
	return res;
}
TypeFuncMap *TypeMgr::get_funcmap_copy(const std::string &name, Stmt *parent)
{
	std::unordered_map<std::string, TypeFunc *> funcs;
	for(auto si = srcstack.rbegin(); si != srcstack.rend(); ++si) {
		SrcTypes *s			  = *si;
		std::vector<LayerTypes *> &layers = s->get_layers();
		for(auto li = layers.rbegin(); li != layers.rend(); ++li) {
			LayerTypes *l				       = *li;
			std::unordered_map<std::string, Type *> &items = l->get_items();
			for(auto &i : items) {
				if(startswith(i.first, name + "_fn") && i.second->type == TFUNC) {
					if(funcs.find(i.first) != funcs.end()) continue;
					funcs[i.first] = static_cast<TypeFunc *>(i.second);
				}
			}
		}
	}
	for(auto &i : globals) {
		if(startswith(i.first, name + "_fn") && i.second->type == TFUNC) {
			if(funcs.find(i.first) != funcs.end()) continue;
			funcs[i.first] = static_cast<TypeFunc *>(i.second);
		}
	}
	if(funcs.empty()) return nullptr;
	return new TypeFuncMap(parent, 0, 0, nullptr, funcs);
}
} // namespace parser
} // namespace sc