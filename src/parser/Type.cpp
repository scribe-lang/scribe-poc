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

std::vector<std::string> basenumtypes()
{
	static std::vector<std::string> basenums = {"i1", "i8",	 "i16", "i32", "i64",
						    "u8", "u16", "u32", "u64"};
	return basenums;
}

type_base_t::type_base_t(const Types &type, stmt_base_t *parent, const size_t &ptr,
			 const size_t &info)
	: id(gen_id()), type(type), parent(parent), ptr(ptr), info(info), intrin_fn(nullptr)
{}
type_base_t::type_base_t(const int64_t &id, const Types &type, stmt_base_t *parent,
			 const size_t &ptr, const size_t &info, intrinsic_fn_t intrin_fn)
	: id(id), type(type), parent(parent), ptr(ptr), info(info), intrin_fn(intrin_fn)
{}
type_base_t::~type_base_t() {}
bool type_base_t::compatible_base(type_base_t *rhs, const bool &is_templ, const size_t &line,
				  const size_t &col)
{
	const size_t &rptr  = rhs->ptr;
	const size_t &rinfo = rhs->info;
	bool num_to_ptr	    = false;
	if(ptr > 0 && rptr == 0) {
		for(auto &bn : basenumtypes()) {
			if(rhs->id == name_id_map[bn]) {
				num_to_ptr = true;
			}
		}
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
	// TODO variadic
	return true;
}
std::string type_base_t::str_base()
{
	std::string tname(ptr, '*');
	if(info & REF) tname += "&";
	if(info & STATIC) tname += "static ";
	if(info & CONST) tname += "const ";
	if(info & VOLATILE) tname += "volatile ";
	if(info & VARIADIC) tname = "..." + tname + " ";
	return tname;
}
std::string type_base_t::mangled_name_base()
{
	std::string tname(ptr, '*');
	if(info & REF) tname += "&";
	if(info & VARIADIC) tname = "..." + tname;
	if(!tname.empty()) tname = "_" + tname;
	return tname;
}

type_simple_t::type_simple_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
			     const std::string &name)
	: type_base_t(TSIMPLE, parent, ptr, info), name(name)
{
	name_id_map[name] = id;
}
type_simple_t::type_simple_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
			     const size_t &info, intrinsic_fn_t intrin_fn, const std::string &name)
	: type_base_t(id, TSIMPLE, parent, ptr, info, intrin_fn), name(name)
{}
type_base_t *type_simple_t::copy()
{
	return new type_simple_t(id, parent, ptr, info, intrin_fn, name);
}
type_base_t *type_simple_t::specialize(const std::vector<type_base_t *> &templates)
{
	if(name[0] != '@') return copy();
	return templates[std::stoi(name.substr(1))]->copy();
}
bool type_simple_t::compatible(type_base_t *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, name[0] == '@', line, col)) return false;
	type_simple_t *r = static_cast<type_simple_t *>(rhs);
	return true;
}
std::string type_simple_t::str()
{
	return str_base() + name;
}
std::string type_simple_t::mangled_name()
{
	std::string tname = mangled_name_base();
	return tname.empty() ? "_" + name : tname + name;
}

type_struct_t::type_struct_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
			     const bool &is_ref, const std::vector<std::string> &templ,
			     const std::vector<std::string> &field_order,
			     const std::unordered_map<std::string, type_base_t *> &fields)
	: type_base_t(TSTRUCT, parent, ptr, info), is_decl_only(false), is_ref(is_ref),
	  is_def(true), templ(templ), field_order(field_order), fields(fields)
{}
type_struct_t::type_struct_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
			     const size_t &info, const bool &is_ref, const bool &is_def,
			     intrinsic_fn_t intrin_fn, const std::vector<std::string> &templ,
			     const std::vector<std::string> &field_order,
			     const std::unordered_map<std::string, type_base_t *> &fields)
	: type_base_t(id, TSTRUCT, parent, ptr, info, intrin_fn), is_decl_only(false),
	  is_ref(is_ref), is_def(is_def), templ(templ), field_order(field_order), fields(fields)
{}
type_struct_t::~type_struct_t()
{
	if(!is_ref) {
		for(auto &f : fields) delete f.second;
	}
}
type_base_t *type_struct_t::copy()
{
	std::unordered_map<std::string, type_base_t *> newfields;
	for(auto &f : fields) {
		newfields[f.first] = is_ref ? f.second : f.second->copy();
	}
	return new type_struct_t(id, parent, ptr, info, is_ref, is_def, intrin_fn, templ,
				 field_order, newfields);
}
type_base_t *type_struct_t::specialize(const std::vector<type_base_t *> &templates)
{
	std::unordered_map<std::string, type_base_t *> newfields;
	for(auto &f : fields) {
		newfields[f.first] = f.second->specialize(templates);
	}
	return new type_struct_t(id, parent, ptr, info, is_ref, is_def, intrin_fn, templ,
				 field_order, newfields);
}
bool type_struct_t::compatible(type_base_t *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, false, line, col)) return false;
	type_struct_t *r = static_cast<type_struct_t *>(rhs);
	if(is_decl_only && templ.empty()) return true;
	if(templ.size() != r->templ.size()) {
		err::set(line, col, "type mismatch (LHS templates: %zu, RHS templates: %zu",
			 templ.size(), r->templ.size());
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
			err::set(line, col, "incompatible field types (LHS: %s, RHS: %s)",
				 fields[f]->str().c_str(), r->fields[f]->str().c_str());
			return false;
		}
	}
	return true;
}
type_struct_t *type_struct_t::specialize_compatible_call(stmt_fncallinfo_t *callinfo,
							 std::vector<type_base_t *> &templates)
{
	if(this->templ.size() < callinfo->templates.size()) return nullptr;
	if(this->fields.size() != callinfo->args.size()) return nullptr;
	for(auto &t : callinfo->templates) {
		templates.push_back(t->vtyp);
	}
	size_t inferred_templates = this->templ.size() - templates.size();
	if(callinfo->args.size() < inferred_templates) return nullptr;
	for(size_t i = 0; i < inferred_templates; ++i) {
		templates.push_back(callinfo->args[i]->vtyp);
	}
	bool is_field_compatible = true;
	for(size_t i = 0; i < this->fields.size(); ++i) {
		type_base_t *ffield = this->fields[field_order[i]];
		stmt_base_t *fciarg = callinfo->args[i];
		if(ffield->type == TSIMPLE) {
			type_simple_t *fargsim = static_cast<type_simple_t *>(ffield);
			if(fargsim->name[0] == '@') {
				std::string idstr = fargsim->name.substr(1);
				ffield		  = templates[std::stoi(idstr)]->copy();
				ffield->ptr += fargsim->ptr;
				ffield->info |= fargsim->info;
			} else {
				ffield = ffield->copy();
			}
		} else {
			ffield = ffield->copy();
		}
		if(!ffield->compatible(fciarg->vtyp, fciarg->line, fciarg->col)) {
			is_field_compatible = false;
			delete ffield;
			break;
		}
		if(ffield) delete ffield;
	}
	if(!is_field_compatible) return nullptr;
	type_struct_t *newst = static_cast<type_struct_t *>(specialize(templates));
	newst->is_def	     = false;
	return newst;
}
std::string type_struct_t::str()
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
std::string type_struct_t::mangled_name()
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
bool type_struct_t::add_field(const std::string &name, type_base_t *val)
{
	if(fields.find(name) != fields.end()) return false;
	field_order.push_back(name);
	fields[name] = val;
	return true;
}
bool type_struct_t::add_field_copy(const std::string &name, type_base_t *val)
{
	if(fields.find(name) != fields.end()) return false;
	field_order.push_back(name);
	fields[name] = val->copy();
	return true;
}

void type_struct_t::set_fields(const std::vector<std::string> &order,
			       const std::unordered_map<std::string, type_base_t *> &vals)
{
	for(auto &f : fields) {
		delete f.second;
	}
	field_order = order;
	fields	    = vals;
}
void type_struct_t::set_fields_copy(const std::vector<std::string> &order,
				    const std::unordered_map<std::string, type_base_t *> &vals)
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
type_base_t *type_struct_t::get_field(const std::string &name)
{
	auto res = fields.find(name);
	if(res != fields.end()) return res->second->copy();
	std::unordered_map<std::string, type_func_t *> funcs;
	for(auto &f : fields) {
		if(startswith(f.first, name + "_fn") && f.second->type == TFUNC) {
			funcs[f.first] = static_cast<type_func_t *>(f.second);
		}
	}
	return funcs.size() > 0 ? new type_funcmap_t(parent, 0, 0, funcs) : nullptr;
}

type_func_t::type_func_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
			 const std::vector<std::string> &templ,
			 const std::vector<type_base_t *> &args, type_base_t *rettype)
	: type_base_t(TFUNC, parent, ptr, info), templ(templ), args(args), rettype(rettype)
{}
type_func_t::type_func_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
			 const size_t &info, intrinsic_fn_t intrin_fn,
			 const std::vector<std::string> &templ,
			 const std::vector<type_base_t *> &args, type_base_t *rettype)
	: type_base_t(id, TFUNC, parent, ptr, info, intrin_fn), templ(templ), args(args),
	  rettype(rettype)
{}
type_func_t::~type_func_t()
{
	for(auto &a : args) delete a;
	delete rettype;
}
type_base_t *type_func_t::copy()
{
	std::vector<type_base_t *> newargs;
	for(auto &a : args) {
		newargs.push_back(a->copy());
	}
	return new type_func_t(id, parent, ptr, info, intrin_fn, templ, newargs, rettype->copy());
}
type_base_t *type_func_t::specialize(const std::vector<type_base_t *> &templates)
{
	std::vector<type_base_t *> newargs;
	type_base_t *newret = rettype->specialize(templates);
	for(auto &a : args) {
		newargs.push_back(a->specialize(templates));
	}
	return new type_func_t(id, parent, ptr, info, intrin_fn, templ, newargs, newret);
}
bool type_func_t::compatible(type_base_t *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, false, line, col)) return false;
	type_func_t *r = static_cast<type_func_t *>(rhs);
	if(templ.size() != r->templ.size()) {
		err::set(line, col, "type mismatch (LHS templates: %zu, RHS templates: %zu",
			 templ.size(), r->templ.size());
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
type_func_t *type_func_t::specialize_compatible_call(stmt_fncallinfo_t *callinfo,
						     std::vector<type_base_t *> &templates)
{
	if(this->templ.size() < callinfo->templates.size()) return nullptr;
	if(this->args.size() != callinfo->args.size()) return nullptr;
	for(auto &t : callinfo->templates) {
		templates.push_back(t->vtyp);
	}
	size_t inferred_templates = this->templ.size() - templates.size();
	if(callinfo->args.size() < inferred_templates) return nullptr;
	for(size_t i = 0; i < inferred_templates; ++i) {
		templates.push_back(callinfo->args[i]->vtyp);
	}
	bool is_arg_compatible = true;
	for(size_t i = 0; i < this->args.size(); ++i) {
		type_base_t *farg   = this->args[i];
		stmt_base_t *fciarg = callinfo->args[i];
		if(farg->type == TSIMPLE) {
			type_simple_t *fargsim = static_cast<type_simple_t *>(farg);
			if(fargsim->name[0] == '@') {
				std::string idstr = fargsim->name.substr(1);
				farg		  = templates[std::stoi(idstr)]->copy();
				farg->ptr += fargsim->ptr;
				farg->info |= fargsim->info;
			} else {
				farg = farg->copy();
			}
		} else {
			farg = farg->copy();
		}
		if(!farg->compatible(fciarg->vtyp, fciarg->line, fciarg->col)) {
			is_arg_compatible = false;
			delete farg;
			break;
		}
		if(farg) delete farg;
	}
	if(!is_arg_compatible) return nullptr;
	return static_cast<type_func_t *>(specialize(templates));
}
std::string type_func_t::str()
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
std::string type_func_t::mangled_name()
{
	std::string tname = mangled_name_base() + "fn";
	for(auto &a : args) {
		std::string mn = a->mangled_name();
		if(mn.empty()) continue;
		tname += mn;
	}
	return tname;
}

type_funcmap_t::type_funcmap_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
			       const std::unordered_map<std::string, type_func_t *> &funcs)
	: type_base_t(TFUNCMAP, parent, ptr, info), funcs(funcs)
{}
type_funcmap_t::type_funcmap_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
			       const size_t &info,
			       const std::unordered_map<std::string, type_func_t *> &funcs)
	: type_base_t(id, TFUNCMAP, parent, ptr, info, nullptr), funcs(funcs)
{}
type_base_t *type_funcmap_t::copy()
{
	return new type_funcmap_t(id, parent, ptr, info, funcs);
}
type_base_t *type_funcmap_t::specialize(const std::vector<type_base_t *> &templates)
{
	return copy();
}
bool type_funcmap_t::compatible(type_base_t *rhs, const size_t &line, const size_t &col)
{
	return false;
}
std::string type_funcmap_t::str()
{
	return "<function map (" + std::to_string(funcs.size()) + ")>";
}
std::string type_funcmap_t::mangled_name()
{
	return "<function map>";
}
type_func_t *type_funcmap_t::decide_func(stmt_fncallinfo_t *callinfo,
					 std::vector<type_base_t *> &templates)
{
	for(auto &fn : funcs) {
		templates.clear();
		printf("option: %s -> %s\n", fn.first.c_str(), fn.second->str().c_str());
		type_func_t *f = fn.second;
		err::reset();
		if(!(f = f->specialize_compatible_call(callinfo, templates))) continue;
		printf("matched: %s -> %s\n", fn.first.c_str(), f->str().c_str());
		return f;
	}
	return nullptr;
}
type_func_t *type_funcmap_t::decide_func(type_base_t *vartype)
{
	return nullptr;
}
} // namespace parser
} // namespace sc