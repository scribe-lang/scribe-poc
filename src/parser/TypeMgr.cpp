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

TypeMgr::TypeMgr(RAIIParser *parser) : parser(parser), vals(parser), init_typefuncs_called(false)
{
	globals["any"]	= new TypeSimple(nullptr, 0, 0, "any");
	globals["void"] = new TypeSimple(nullptr, 0, 0, "void");
	globals["i1"]	= new TypeSimple(nullptr, 0, 0, "i1");
	globals["i8"]	= new TypeSimple(nullptr, 0, 0, "i8");
	globals["i16"]	= new TypeSimple(nullptr, 0, 0, "i16");
	globals["i32"]	= new TypeSimple(nullptr, 0, 0, "i32");
	globals["i64"]	= new TypeSimple(nullptr, 0, 0, "i64");
	globals["u8"]	= new TypeSimple(nullptr, 0, 0, "u8");
	globals["u16"]	= new TypeSimple(nullptr, 0, 0, "u16");
	globals["u32"]	= new TypeSimple(nullptr, 0, 0, "u32");
	globals["u64"]	= new TypeSimple(nullptr, 0, 0, "u64");
	globals["f32"]	= new TypeSimple(nullptr, 0, 0, "f32");
	globals["f64"]	= new TypeSimple(nullptr, 0, 0, "f64");
	globals["nil"]	= globals["i1"]->copy();
	globals["bool"] = globals["i1"]->copy();
	// cstr
	TypeSimple *cstr = static_cast<TypeSimple *>(globals["u8"]->copy());
	cstr->ptr	 = 1;
	cstr->info |= CONST;

	// intrinsics
	TypeSimple *templ0    = new TypeSimple(nullptr, 0, 0, "@0");
	TypeSimple *templ1    = new TypeSimple(nullptr, 0, 0, "@1");
	TypeSimple *templ0va  = new TypeSimple(nullptr, 0, VARIADIC, "@0");
	TypeSimple *templ0ptr = new TypeSimple(nullptr, 1, 0, "@0");
	TypeImport *importty  = new TypeImport(nullptr, 0, 0, "");

	TypeFunc *importfn = new TypeFunc(nullptr, 0, 0, 0, 0, false, {cstr}, importty);
	importfn->setIntrinsicFunc(intrinsic_import, IPARSE);
	globals["import"] = importfn;

	TypeFunc *asfn = new TypeFunc(nullptr, 0, 0, 0, 2, false, {templ1}, templ0);
	asfn->setIntrinsicFunc(intrinsic_as, IPARSE);
	globals["as"] = asfn;

	TypeFunc *szfn = new TypeFunc(nullptr, 0, 0, 0, 1, false, {}, globals["i32"]->copy());
	szfn->setIntrinsicFunc(intrinsic_szof, IVALUE);
	globals["sizeof"] = szfn;

	TypeFunc *typeidfn = new TypeFunc(nullptr, 0, 0, 0, 1, false, {}, globals["i32"]->copy());
	typeidfn->setIntrinsicFunc(intrinsic_typid, IVALUE);
	globals["typeid"] = typeidfn;

	TypeFunc *valenfn = new TypeFunc(nullptr, 0, 0, 0, 0, false, {}, globals["i32"]->copy());
	valenfn->setIntrinsicFunc(intrinsic_va_len, IVALUE);
	globals["va_len"] = valenfn;

	TypeFunc *arrayfn = new TypeFunc(nullptr, 0, 0, 0, 1, false, {templ0va}, templ0ptr);
	arrayfn->setIntrinsicFunc(intrinsic_array, IVALUE);
	globals["array"] = arrayfn;

	TypeFunc *comp_strlenfn =
	new TypeFunc(nullptr, 0, 0, 0, 0, true, {cstr->copy()}, globals["u64"]->copy());
	comp_strlenfn->setIntrinsicFunc(intrinsic_comptime_strlen, IVALUE);
	globals["comp_strlen"] = comp_strlenfn;

	TypeFunc *ptr_subscrfn =
	new TypeFunc(nullptr, 0, 0, 0, 1, false, {templ0->copy(CONST, 1), globals["i32"]->copy()},
		     templ0->copy());
	ptr_subscrfn->setIntrinsicFunc(intrinsic_subscr, IVALUE);
	addFunc("[]", ptr_subscrfn, true);
}
TypeMgr::~TypeMgr()
{
	for(auto &g : globals) delete g.second;
	for(auto &s : stack) delete s;
	for(auto &mfn : managedfnmaps) delete mfn;
}
void TypeMgr::initTypeFuncs()
{
	add_primitive_integer_funcs(*this);

	init_typefuncs_called = true;
}
bool TypeMgr::add(const std::string &name, Type *val, const bool &global)
{
	if(global) {
		if(globals.find(name) != globals.end()) return false;
		globals[name] = val;
		return true;
	}
	return stack.back()->add(name, val);
}
bool TypeMgr::addCopy(const std::string &name, Type *val, const bool &global)
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
	if(top_only) return stack.back()->exists(name);
	size_t i = stack.size() - 1;
	for(auto rit = stack.rbegin(); rit != stack.rend(); ++rit) {
		if(lock_from != size_t(-1) && i <= lock_from) break;
		if((*rit)->exists(name)) return true;
		--i;
	}
	return with_globals ? globals.find(name) != globals.end() : false;
}
Type *TypeMgr::get(const std::string &name)
{
	size_t lock_from = lockedlayers.size() > 0 ? lockedlayers.back() : size_t(-1);
	size_t i	 = stack.size() - 1;
	for(auto rit = stack.rbegin(); rit != stack.rend(); ++rit) {
		if(lock_from != size_t(-1) && i <= lock_from) break;
		Type *res = (*rit)->get(name);
		if(res) return res;
		--i;
	}
	auto gres = globals.find(name);
	if(gres != globals.end()) return gres->second;
	return getFuncMap(name, nullptr);
}
Type *TypeMgr::getCopy(const std::string &name, Stmt *parent)
{
	Type *res = get(name);
	if(!res) return nullptr;
	res = res->copy();
	if(parent && res->type == TFUNCMAP) res->parent = parent;
	return res;
}
bool TypeMgr::addFunc(const std::string &name, Type *vtyp, const bool &global)
{
	std::string fullname = name + "_" + vtyp->mangled_name();
	return add(fullname, vtyp, global);
}
bool TypeMgr::addFuncCopy(const std::string &name, Type *vtyp, const bool &global)
{
	std::string fullname = name + "_" + vtyp->mangled_name();
	return addCopy(fullname, vtyp, global);
}
TypeFuncMap *TypeMgr::getFuncMap(const std::string &name, Stmt *parent)
{
	TypeFuncMap *res = getFuncMapCopy(name, parent);
	if(!res) return nullptr;
	managedfnmaps.push_back(res);
	return res;
}
TypeFuncMap *TypeMgr::getFuncMapCopy(const std::string &name, Stmt *parent)
{
	std::unordered_map<std::string, TypeFunc *> funcs;
	for(auto li = stack.rbegin(); li != stack.rend(); ++li) {
		LayerTypes *l				       = *li;
		std::unordered_map<std::string, Type *> &items = l->get_items();
		for(auto &i : items) {
			if(startswith(i.first, name + "_fn") && i.second->type == TFUNC) {
				if(funcs.find(i.first) != funcs.end()) continue;
				funcs[i.first] = static_cast<TypeFunc *>(i.second);
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
	return new TypeFuncMap(parent, 0, 0, funcs);
}
} // namespace parser
} // namespace sc