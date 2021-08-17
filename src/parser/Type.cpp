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

#include "parser/Type.hpp"

#include <cassert>

#include "Error.hpp"
#include "parser/Stmts.hpp"

static int64_t gen_id()
{
	static int64_t id = 0;
	return ++id; // starts at 1
}

namespace sc
{
namespace parser
{
std::unordered_map<std::string, int64_t> name_id_map;

std::vector<std::string> BooleanTypes()
{
	static std::vector<std::string> basenums = {"i1", "i8",	 "i16", "i32", "i64",
						    "u8", "u16", "u32", "u64"};
	return basenums;
}

std::vector<std::string> IntegralTypes()
{
	static std::vector<std::string> basenums = {"i8", "i16", "i32", "i64",
						    "u8", "u16", "u32", "u64"};
	return basenums;
}

Type::Type(const Types &type, Stmt *parent, const size_t &ptr, const size_t &info)
	: id(gen_id()), type(type), parent(parent), ptr(ptr), info(info)
{}
Type::Type(const int64_t &id, const Types &type, Stmt *parent, const size_t &ptr,
	   const size_t &info)
	: id(id), type(type), parent(parent), ptr(ptr), info(info)
{}
Type::~Type() {}
bool Type::compatible_base(Type *rhs, const bool &is_templ, const size_t &line, const size_t &col)
{
	const size_t &rptr  = rhs->ptr;
	const size_t &rinfo = rhs->info;
	bool num_to_ptr	    = false;
	if(ptr > 0 && rptr == 0) {
		num_to_ptr = integerCompatible();
	}
	if(!is_templ && !num_to_ptr && id != rhs->id) {
		err::set(line, col, "different type ids (LHS: %s, RHS: %s), not compatible",
			 str().c_str(), rhs->str().c_str());
		return false;
	}
	// something with REF?
	if(ptr == 0 && rptr > 0) {
		err::set(line, col, "cannot use a pointer type (RHS: %s) for non pointer (LHS: %s)",
			 rhs->str().c_str(), str().c_str());
		return false;
	}
	if(rptr == 0 && !num_to_ptr && ptr > 0) {
		err::set(line, col,
			 "non pointer type (RHS) cannot be assigned to pointer type (LHS)");
		return false;
	}
	if(rptr != ptr) {
		err::setw(line, col, "inequal pointer assignment here, continuing...");
	}
	if(rinfo & CONST && !(info & CONST)) {
		err::set(line, col, "losing constness here, cannot continue (LHS: %s, RHS: %s)",
			 str().c_str(), rhs->str().c_str());
		return false;
	}
	if(rhs->info & VARIADIC && !(info & VARIADIC)) {
		err::set(line, col,
			 "cannot assign variadic type to non variadic (LHS: %s, RHS: %s)",
			 str().c_str(), rhs->str().c_str());
		return false;
	}
	return true;
}
bool Type::booleanCompatible()
{
	for(auto &bt : BooleanTypes()) {
		if(id == name_id_map[bt]) {
			return true;
		}
	}
	err::reset();
	return false;
}
bool Type::integerCompatible()
{
	for(auto &it : IntegralTypes()) {
		if(id == name_id_map[it]) {
			return true;
		}
	}
	err::reset();
	return false;
}
std::string Type::str_base()
{
	std::string tname(ptr, '*');
	if(info & REF) tname += "&";
	if(info & STATIC) tname += "static ";
	if(info & CONST) tname += "const ";
	if(info & VOLATILE) tname += "volatile ";
	if(info & VARIADIC) tname = "..." + tname + (!tname.empty() ? " " : "");
	return tname;
}
std::string Type::mangled_name_base()
{
	std::string tname(ptr, '*');
	if(info & REF) tname += "&";
	if(info & VARIADIC) tname = "..." + tname;
	if(!tname.empty()) tname = "_" + tname;
	return tname;
}

TypeSimple::TypeSimple(Stmt *parent, const size_t &ptr, const size_t &info, const std::string &name)
	: Type(TSIMPLE, parent, ptr, info), name(name)
{
	name_id_map[name] = id;
}
TypeSimple::TypeSimple(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		       const std::string &name)
	: Type(id, TSIMPLE, parent, ptr, info), name(name)
{}
Type *TypeSimple::copy(const size_t &append_info)
{
	return new TypeSimple(id, parent, ptr, info | append_info, name);
}
Type *TypeSimple::specialize(const std::unordered_map<std::string, Type *> &templates)
{
	if(name[0] != '@') return copy();
	if(templates.empty() || templates.find(name) == templates.end()) {
		err::set(parent->line, parent->col, "could not find type '%s' in templates",
			 name.c_str());
		return nullptr;
	}
	Type *res = templates.at(name)->copy();
	res->ptr += ptr;
	res->info |= info;
	return res;
}
bool TypeSimple::compatible(Type *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, name[0] == '@' || name == "any", line, col)) return false;
	TypeSimple *r = static_cast<TypeSimple *>(rhs);
	return true;
}
bool TypeSimple::assignTemplateActuals(Type *actual,
				       std::unordered_map<std::string, Type *> &templates,
				       const size_t &line, const size_t &col)
{
	if(name[0] != '@') return true;
	auto res = templates.find(name);
	if(res != templates.end()) {
		if(!res->second->compatible(actual, line, col)) {
			err::set(line, col,
				 "In templated argument, mismatch"
				 " between template %s and actual %s",
				 res->second->str().c_str(), actual->str().c_str());
			return false;
		}
		return true;
	}
	templates[name] = actual->copy();
	return true;
}
std::string TypeSimple::str()
{
	return str_base() + name;
}
std::string TypeSimple::mangled_name()
{
	std::string tname = mangled_name_base();
	return tname.empty() ? "_" + name : tname + name;
}

TypeImport::TypeImport(Stmt *parent, const size_t &ptr, const size_t &info,
		       const std::string &mod_id)
	: Type(TIMPORT, parent, ptr, info), mod_id(mod_id)
{}
TypeImport::TypeImport(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		       const std::string &mod_id)
	: Type(TIMPORT, parent, ptr, info), mod_id(mod_id)
{}

const std::string &TypeImport::getModID()
{
	return mod_id;
}

Type *TypeImport::copy(const size_t &append_info)
{
	return new TypeImport(id, parent, ptr, info, mod_id);
}
Type *TypeImport::specialize(const std::unordered_map<std::string, Type *> &templates)
{
	return copy();
}
bool TypeImport::compatible(Type *rhs, const size_t &line, const size_t &col)
{
	return true;
}
bool TypeImport::assignTemplateActuals(Type *actual,
				       std::unordered_map<std::string, Type *> &templates,
				       const size_t &line, const size_t &col)
{
	return true;
}

std::string TypeImport::str()
{
	return "<import>(" + mod_id + ")";
}
std::string TypeImport::mangled_name()
{
	return str();
}

TypeStruct::TypeStruct(Stmt *parent, const size_t &ptr, const size_t &info, const size_t &templ,
		       const std::vector<std::string> &field_order,
		       const std::unordered_map<std::string, Type *> &fields)
	: Type(TSTRUCT, parent, ptr, info), is_decl_only(false), is_def(false), templ(templ),
	  field_order(field_order), fields(fields)
{}
TypeStruct::TypeStruct(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		       const bool &is_def, const size_t &templ,
		       const std::vector<std::string> &field_order,
		       const std::unordered_map<std::string, Type *> &fields)
	: Type(id, TSTRUCT, parent, ptr, info), is_decl_only(false), is_def(is_def), templ(templ),
	  field_order(field_order), fields(fields)
{}
TypeStruct::~TypeStruct()
{
	for(auto &f : fields) delete f.second;
}
Type *TypeStruct::copy(const size_t &append_info)
{
	std::unordered_map<std::string, Type *> newfields;
	for(auto &f : fields) {
		newfields[f.first] = f.second->copy();
	}
	return new TypeStruct(id, parent, ptr, info | append_info, is_def, templ, field_order,
			      newfields);
}
Type *TypeStruct::specialize(const std::unordered_map<std::string, Type *> &templates)
{
	std::unordered_map<std::string, Type *> newfields;
	for(auto &f : fields) {
		newfields[f.first] = f.second->specialize(templates);
	}
	return new TypeStruct(id, parent, ptr, info, is_def, templ, field_order, newfields);
}
bool TypeStruct::compatible(Type *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, false, line, col)) return false;
	TypeStruct *r = static_cast<TypeStruct *>(rhs);
	if(is_decl_only && !templ) return true;
	if(templ != r->templ) {
		err::set(line, col, "type mismatch (LHS templates: %zu, RHS templates: %zu", templ,
			 r->templ);
		return false;
	}
	if(fields.size() != r->fields.size()) {
		err::set(line, col, "type mismatch (LHS fields: %zu, RHS fields: %zu",
			 fields.size(), r->fields.size());
		return false;
	}
	for(size_t i = 0; i < fields.size(); ++i) {
		if(field_order[i] != r->field_order[i]) {
			err::set(line, col, "incompatible fields (LHS: %s, RHS: %s)",
				 field_order[i].c_str(), r->field_order[i].c_str());
			return false;
		}
		const std::string &f = field_order[i];
		if(!fields[f]->compatible(r->fields[f], line, col)) {
			err::set(line, col,
				 "incompatible field types (LHS: %s, RHS: %s) in %s and %s",
				 fields[f]->str().c_str(), r->fields[f]->str().c_str(),
				 str().c_str(), r->str().c_str());
			return false;
		}
	}
	return true;
}
TypeStruct *
TypeStruct::specialize_compatible_call(StmtFnCallInfo *callinfo,
				       std::unordered_map<std::string, Type *> &templates)
{
	templates.clear();
	if(this->templ < callinfo->templates.size()) return nullptr;
	if(this->fields.size() != callinfo->args.size()) return nullptr;
	for(size_t i = 0; i < callinfo->templates.size(); ++i) {
		templates["@" + std::to_string(i)] = callinfo->templates[i]->type->copy();
	}
	for(size_t i = 0; i < this->field_order.size(); ++i) {
		Type *&field = this->fields[field_order[i]];
		if(!field->assignTemplateActuals(callinfo->args[i]->type, templates, callinfo->line,
						 callinfo->col))
			return nullptr;
	}
	bool is_field_compatible = true;
	std::unordered_map<std::string, Type *> specializedfields;
	for(auto &f : this->fields) {
		specializedfields[f.first] = f.second->specialize(templates);
	}
	for(size_t i = 0; i < specializedfields.size(); ++i) {
		Type *ffield = specializedfields[field_order[i]];
		Stmt *fciarg = callinfo->args[i];
		if(!ffield->compatible(fciarg->type, fciarg->line, fciarg->col)) {
			is_field_compatible = false;
			break;
		}
	}
	for(auto &sf : specializedfields) delete sf.second;
	if(!is_field_compatible) {
		for(auto &t : templates) delete t.second;
		return nullptr;
	}
	TypeStruct *newst = static_cast<TypeStruct *>(specialize(templates));
	newst->is_def	  = false;
	for(auto &t : templates) delete t.second;
	return newst;
}
bool TypeStruct::assignTemplateActuals(Type *actual,
				       std::unordered_map<std::string, Type *> &templates,
				       const size_t &line, const size_t &col)
{
	if(!compatible(actual, line, col)) return false;
	TypeStruct *ast = as<TypeStruct>(actual);
	for(auto &f : field_order) {
		if(!fields[f]->assignTemplateActuals(ast->fields[f], templates, line, col))
			return false;
	}
	return true;
}
std::string TypeStruct::str()
{
	std::string tname = str_base() + "struct." + std::to_string(id);
	tname += "{";
	for(auto &f : field_order) {
		// tname += f + ", ";
		tname += f + ": " + fields[f]->str() + ", ";
	}
	if(field_order.size() > 0) {
		tname.pop_back();
		tname.pop_back();
	}
	tname += "}";
	return tname;
}
std::string TypeStruct::mangled_name()
{
	std::string tname = mangled_name_base() + "struct." + std::to_string(id);
	// tname += "{";
	// for(auto &f : field_order) {
	// 	tname += f + ": " + fields[f]->str() + ", ";
	// }
	// if(field_order.size() > 0) {
	// 	tname.pop_back();
	// 	tname.pop_back();
	// }
	// tname += "}";
	return tname;
}
bool TypeStruct::add_field(const std::string &name, Type *val)
{
	if(fields.find(name) != fields.end()) return false;
	field_order.push_back(name);
	fields[name] = val;
	return true;
}
bool TypeStruct::add_field_copy(const std::string &name, Type *val)
{
	if(fields.find(name) != fields.end()) return false;
	field_order.push_back(name);
	fields[name] = val->copy();
	return true;
}

void TypeStruct::set_fields(const std::vector<std::string> &order,
			    const std::unordered_map<std::string, Type *> &vals)
{
	for(auto &f : fields) {
		delete f.second;
	}
	field_order = order;
	fields	    = vals;
}
void TypeStruct::set_fields_copy(const std::vector<std::string> &order,
				 const std::unordered_map<std::string, Type *> &vals)
{
	for(auto &f : fields) {
		delete f.second;
	}
	fields.clear();
	field_order = order;
	for(auto &v : vals) {
		fields[v.first] = v.second->copy();
	}
}
Type *TypeStruct::get_field(const std::string &name)
{
	auto res = fields.find(name);
	if(res != fields.end()) return res->second;
	std::unordered_map<std::string, TypeFunc *> funcs;
	for(auto &f : fields) {
		if(startswith(f.first, name + "_fn") && f.second->type == TFUNC) {
			funcs[f.first] = as<TypeFunc>(f.second);
		}
	}
	return funcs.size() > 0 ? new TypeFuncMap(parent, 0, 0, funcs) : nullptr;
}
int32_t TypeStruct::getFieldIndex(const std::string &name)
{
	for(size_t i = 0; i < field_order.size(); ++i) {
		if(field_order[i] == name) return i;
	}
	return -1;
}

TypeFunc::TypeFunc(Stmt *parent, const size_t &ptr, const size_t &info, const size_t &scope,
		   const size_t &templ, const bool &has_va, const std::vector<Type *> &args,
		   Type *rettype)
	: Type(TFUNC, parent, ptr, info), scope(scope), templ(templ), has_va(has_va), args(args),
	  rettype(rettype), intrin_fn(nullptr), intrin_fn_type(INONE)
{}
TypeFunc::TypeFunc(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
		   const size_t &scope, const size_t &templ, const bool &has_va,
		   const std::vector<Type *> &args, Type *rettype, intrinsic_fn_t intrin_fn,
		   const IntrinFuncType &intrin_fn_type)
	: Type(id, TFUNC, parent, ptr, info), scope(scope), templ(templ), has_va(has_va),
	  args(args), rettype(rettype), intrin_fn(intrin_fn), intrin_fn_type(intrin_fn_type)
{}
TypeFunc::~TypeFunc()
{
	for(auto &a : args) delete a;
	delete rettype;
}
Type *TypeFunc::copy(const size_t &append_info)
{
	std::vector<Type *> newargs;
	for(auto &a : args) {
		newargs.push_back(a->copy());
	}
	return new TypeFunc(id, parent, ptr, info | append_info, scope, templ, has_va, newargs,
			    rettype->copy(), intrin_fn, intrin_fn_type);
}
Type *TypeFunc::specialize(const std::unordered_map<std::string, Type *> &templates)
{
	std::vector<Type *> newargs;
	Type *newret = rettype->specialize(templates);
	for(auto &a : args) {
		newargs.push_back(a->specialize(templates));
	}
	return new TypeFunc(id, parent, ptr, info, scope, templ, has_va, newargs, newret, intrin_fn,
			    intrin_fn_type);
}
bool TypeFunc::compatible(Type *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, false, line, col)) return false;
	TypeFunc *r = static_cast<TypeFunc *>(rhs);
	if(templ != r->templ) {
		err::set(line, col, "type mismatch (LHS templates: %zu, RHS templates: %zu", templ,
			 r->templ);
		return false;
	}
	if(args.size() != r->args.size()) {
		err::set(line, col, "type mismatch (LHS args: %zu, RHS args: %zu", args.size(),
			 r->args.size());
		return false;
	}
	for(size_t i = 0; i < args.size(); ++i) {
		if(!args[i]->compatible(r->args[i], line, col)) {
			err::set(line, col, "incompatible field types (LHS: %s, RHS: %s)",
				 args[i]->str().c_str(), r->args[i]->str().c_str());
			return false;
		}
	}
	if(!rettype->compatible(r->rettype, line, col)) {
		err::set(line, col, "incompatible return types (LHS: %s, RHS: %s)",
			 rettype->str().c_str(), r->rettype->str().c_str());
		return false;
	}
	return true;
}
TypeFunc *TypeFunc::specialize_compatible_call(StmtFnCallInfo *callinfo,
					       std::unordered_map<std::string, Type *> &templates)
{
	templates.clear();
	if(this->templ < callinfo->templates.size()) return nullptr;
	if(this->args.size() > 0 && (this->args.back()->info & TypeInfoMask::VARIADIC)) {
		if(this->args.size() - 1 > callinfo->args.size()) return nullptr;
	} else if(this->args.size() != callinfo->args.size()) {
		return nullptr;
	}
	for(size_t i = 0; i < callinfo->templates.size(); ++i) {
		templates["@" + std::to_string(i)] = callinfo->templates[i]->type->copy();
	}
	for(size_t i = 0; i < this->args.size() && i < callinfo->args.size(); ++i) {
		if(!this->args[i]->assignTemplateActuals(callinfo->args[i]->type, templates,
							 callinfo->line, callinfo->col))
			return nullptr;
	}
	bool is_arg_compatible = true;
	std::vector<Type *> variadics;
	std::vector<Type *> specializedargs;
	for(auto &a : this->args) {
		specializedargs.push_back(a->specialize(templates));
	}
	for(size_t i = 0, j = 0; i < specializedargs.size() && j < callinfo->args.size(); ++i, ++j)
	{
		Type *farg    = specializedargs[i];
		bool variadic = false;
		if(farg->info & VARIADIC) {
			variadic = true;
			--i;
		}
		Stmt *fciarg = callinfo->args[j];
		if(!farg->compatible(fciarg->type, fciarg->line, fciarg->col)) {
			is_arg_compatible = false;
			break;
		}
		if(variadic) variadics.push_back(fciarg->type);
	}
	for(auto &sa : specializedargs) delete sa;
	if(!is_arg_compatible) {
		for(auto &t : templates) delete t.second;
		return nullptr;
	}
	size_t val_len = this->args.size();
	TypeFunc *tmp  = static_cast<TypeFunc *>(this->copy());
	if(tmp->args.size() > 0 && tmp->args.back()->info & VARIADIC) --val_len;
	if(has_va) {
		delete tmp->args.back();
		tmp->args.pop_back();
		TypeVariadic *va = new TypeVariadic(nullptr, 0, 0, {});
		for(auto &vtmp : variadics) {
			Type *v = vtmp->copy();
			v->info &= ~VARIADIC;
			va->args.push_back(v);
		}
		tmp->args.push_back(va);
	}
	TypeFunc *res = static_cast<TypeFunc *>(tmp->specialize(templates));
	// no templates delete here because it is done in InitTemplateFn
	// (by adding to types directly instead of by copying)
	delete tmp;
	return res;
}
bool TypeFunc::assignTemplateActuals(Type *actual,
				     std::unordered_map<std::string, Type *> &templates,
				     const size_t &line, const size_t &col)
{
	if(!compatible(actual, line, col)) return false;
	TypeFunc *afn = as<TypeFunc>(actual);
	for(size_t i = 0; i < args.size(); ++i) {
		if(!args[i]->assignTemplateActuals(afn->args[i], templates, line, col))
			return false;
	}
	return true;
}
std::string TypeFunc::str()
{
	std::string tname = str_base() + "fn." + std::to_string(id);
	tname += "(";
	for(auto &a : args) {
		tname += a->str() + ", ";
	}
	if(args.size() > 0) {
		tname.pop_back();
		tname.pop_back();
	}
	tname += "): " + rettype->str();
	return tname;
}
std::string TypeFunc::mangled_name()
{
	std::string tname = mangled_name_base() + "fn";
	for(auto &a : args) {
		tname += a->mangled_name();
	}
	return tname;
}

TypeFuncMap::TypeFuncMap(Stmt *parent, const size_t &ptr, const size_t &info,
			 const std::unordered_map<std::string, TypeFunc *> &funcs)
	: Type(TFUNCMAP, parent, ptr, info), funcs(funcs), self(nullptr)
{}
TypeFuncMap::TypeFuncMap(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
			 const std::unordered_map<std::string, TypeFunc *> &funcs, Type *self)
	: Type(id, TFUNCMAP, parent, ptr, info), funcs(funcs), self(self)
{}
TypeFuncMap::~TypeFuncMap()
{
	if(self) delete self;
}
Type *TypeFuncMap::copy(const size_t &append_info)
{
	return new TypeFuncMap(id, parent, ptr, info | append_info, funcs,
			       self ? self->copy() : nullptr);
}
Type *TypeFuncMap::specialize(const std::unordered_map<std::string, Type *> &templates)
{
	return copy();
}
bool TypeFuncMap::compatible(Type *rhs, const size_t &line, const size_t &col)
{
	return false;
}
bool TypeFuncMap::assignTemplateActuals(Type *actual,
					std::unordered_map<std::string, Type *> &templates,
					const size_t &line, const size_t &col)
{
	return false;
}
void TypeFuncMap::setSelf(Type *s)
{
	self = s;
}
Type *&TypeFuncMap::getSelf()
{
	return self;
}
std::string TypeFuncMap::str()
{
	return str_base() + "<function map (" + std::to_string(funcs.size()) + ")>";
}
std::string TypeFuncMap::mangled_name()
{
	return "<function map>";
}
TypeFunc *TypeFuncMap::decide_func(StmtFnCallInfo *callinfo,
				   std::unordered_map<std::string, Type *> &templates)
{
	if(self) {
		Module *mod	   = callinfo->mod;
		const size_t &line = callinfo->line;
		const size_t &col  = callinfo->col;
		lex::Lexeme selfeme(line, col, col, lex::IDEN, "self");
		StmtSimple *stmtself = new StmtSimple(mod, line, col, selfeme);
		stmtself->type	     = self->copy();
		callinfo->args.insert(callinfo->args.begin(), stmtself);
	}
	for(auto &fn : funcs) {
		err::reset();
		// printf("option: %s -> %s\n", fn.first.c_str(), fn.second->str().c_str());
		TypeFunc *f = fn.second;
		if(!(f = f->specialize_compatible_call(callinfo, templates))) continue;
		// printf("matched: %s -> %s\n", fn.first.c_str(), f->str().c_str());
		err::reset();
		if(self) {
			delete callinfo->args[0];
			callinfo->args.erase(callinfo->args.begin());
		}
		return f;
	}
	if(self) {
		delete callinfo->args[0];
		callinfo->args.erase(callinfo->args.begin());
	}
	return nullptr;
}
TypeFunc *TypeFuncMap::decide_func(Type *vartype)
{
	return nullptr;
}

TypeVariadic::TypeVariadic(Stmt *parent, const size_t &ptr, const size_t &info,
			   const std::vector<Type *> &args)
	: Type(TVARIADIC, parent, ptr, info), args(args)
{}
TypeVariadic::TypeVariadic(const int64_t &id, Stmt *parent, const size_t &ptr, const size_t &info,
			   const std::vector<Type *> &args)
	: Type(id, TVARIADIC, parent, ptr, info), args(args)
{}
TypeVariadic::~TypeVariadic()
{
	for(auto &a : args) delete a;
}

Type *TypeVariadic::copy(const size_t &append_info)
{
	std::vector<Type *> newargs;
	for(auto &a : args) newargs.push_back(a->copy());
	return new TypeVariadic(id, parent, ptr, info | append_info, newargs);
}
Type *TypeVariadic::specialize(const std::unordered_map<std::string, Type *> &templates)
{
	std::vector<Type *> newargs;
	for(auto &a : args) newargs.push_back(a->specialize(templates));
	return new TypeVariadic(id, parent, ptr, info, newargs);
}
bool TypeVariadic::compatible(Type *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, false, line, col)) return false;
	TypeVariadic *r = static_cast<TypeVariadic *>(rhs);
	if(args.size() != r->args.size()) {
		err::set(line, col, "type mismatch (LHS args: %zu, RHS args: %zu", args.size(),
			 r->args.size());
		return false;
	}
	for(size_t i = 0; i < args.size(); ++i) {
		if(!args[i]->compatible(r->args[i], line, col)) {
			err::set(line, col, "incompatible field types (LHS: %s, RHS: %s)",
				 args[i]->str().c_str(), r->args[i]->str().c_str());
			return false;
		}
	}
	return true;
}
bool TypeVariadic::assignTemplateActuals(Type *actual,
					 std::unordered_map<std::string, Type *> &templates,
					 const size_t &line, const size_t &col)
{
	if(!compatible(actual, line, col)) return false;
	TypeVariadic *ava = as<TypeVariadic>(actual);
	for(size_t i = 0; i < args.size(); ++i) {
		if(!args[i]->assignTemplateActuals(ava->args[i], templates, line, col))
			return false;
	}
	return true;
}
void TypeVariadic::setIndexed(const bool &indexed)
{
	is_indexed = indexed;
}
bool TypeVariadic::isIndexed()
{
	return is_indexed;
}
std::string TypeVariadic::str()
{
	std::string tname = str_base() + "<variadic(" + std::to_string(args.size()) + ")>{";
	for(auto &a : args) {
		tname += a->str() + ", ";
	}
	if(args.size() > 0) {
		tname.pop_back();
		tname.pop_back();
	}
	tname += "}";
	return tname;
}
std::string TypeVariadic::mangled_name()
{
	std::string tname = mangled_name_base();
	for(auto &a : args) {
		tname += a->mangled_name();
	}
	return tname;
}
Type *TypeVariadic::get_arg(const size_t &idx)
{
	return args[idx]->copy();
}
} // namespace parser
} // namespace sc