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

const char *TypeStrs[] = {
"simple",
"struct",
};

static int64_t gen_id()
{
	static int64_t id = 0;
	return ++id; // starts at 1
}

namespace sc
{
namespace parser
{
type_base_t::type_base_t(const Types &type, stmt_base_t *parent, const size_t &ptr,
			 const size_t &info)
	: id(gen_id()), type(type), parent(parent), ptr(ptr), info(info), intrin_fn(nullptr)
{}
type_base_t::type_base_t(const int64_t &id, const Types &type, stmt_base_t *parent,
			 const size_t &ptr, const size_t &info, intrinsic_fn_t intrin_fn)
	: id(id), type(type), parent(parent), ptr(ptr), info(info), intrin_fn(intrin_fn)
{}
type_base_t::~type_base_t() {}
bool type_base_t::compatible_base(type_base_t *rhs, const size_t &line, const size_t &col)
{
	size_t rptr  = rhs->ptr;
	size_t rinfo = rhs->info;
	if(id != rhs->id) {
		err::set(line, col, "different type ids, not compatible");
		return false;
	}
	if(rinfo & REF) {
		rinfo &= ~REF;
		++rptr;
	}
	if(ptr == 0) {
		if(rptr > 0) {
			err::set(line, col,
				 "cannot use a pointer type (RHS) for non pointer (LHS)");
			return false;
		}
	}
	if(rptr == 0) {
		if(ptr > 0) {
			err::set(line, col,
				 "non pointer type (RHS) cannot be assigned to pointer type (LHS)");
			return false;
		}
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

// std::string type_base_t::mangled_name_base()
// {
// 	std::string tname(ptr, '*');
// 	if(info & REF) tname += "&";
// 	if(info & VARIADIC) tname = "..." + tname;
// 	if(!tname.empty()) tname = "_" + tname;
// 	return tname;
// }
// std::string type_base_t::mangled_name()
// {
// 	return "";
// }

type_simple_t::type_simple_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
			     const std::string &name)
	: type_base_t(TSIMPLE, parent, ptr, info), name(name)
{}
type_simple_t::type_simple_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
			     const size_t &info, intrinsic_fn_t intrin_fn, const std::string &name)
	: type_base_t(id, TSIMPLE, parent, ptr, info, intrin_fn), name(name)
{}
std::string type_simple_t::str()
{
	return str_base() + name;
}
// std::string type_simple_t::mangled_name()
// {
// 	std::string tname = mangled_name_base();
// 	return tname.empty() ? "_" + name : tname + name;
// }
type_base_t *type_simple_t::copy()
{
	return new type_simple_t(id, parent, ptr, info, intrin_fn, name);
}
bool type_simple_t::compatible(type_base_t *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, line, col)) return false;
	type_simple_t *r = static_cast<type_simple_t *>(rhs);
	if(name != r->name) {
		err::set(line, col, "invalid types (LHS: %s, RHS: %s)", str().c_str(),
			 rhs->str().c_str());
		return false;
	}
	return true;
}

type_struct_t::type_struct_t(stmt_base_t *parent, const size_t &ptr, const size_t &info,
			     const std::vector<std::string> &templ,
			     const std::vector<std::string> &field_order,
			     const std::unordered_map<std::string, type_base_t *> &fields)
	: type_base_t(TSTRUCT, parent, ptr, info), is_decl_only(false), templ(templ),
	  field_order(field_order), fields(fields)
{}
type_struct_t::type_struct_t(const int64_t &id, stmt_base_t *parent, const size_t &ptr,
			     const size_t &info, intrinsic_fn_t intrin_fn,
			     const std::vector<std::string> &templ,
			     const std::vector<std::string> &field_order,
			     const std::unordered_map<std::string, type_base_t *> &fields)
	: type_base_t(id, TSTRUCT, parent, ptr, info, intrin_fn), is_decl_only(false), templ(templ),
	  field_order(field_order), fields(fields)
{}
type_struct_t::~type_struct_t()
{
	for(auto &f : fields) delete f.second;
}
type_base_t *type_struct_t::copy()
{
	std::unordered_map<std::string, type_base_t *> newfields;
	for(auto &f : fields) {
		newfields[f.first] = f.second->copy();
	}
	return new type_struct_t(id, parent, ptr, info, intrin_fn, templ, field_order, newfields);
}
bool type_struct_t::compatible(type_base_t *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, line, col)) return false;
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
std::string type_struct_t::str()
{
	std::string tname = str_base() + "struct." + std::to_string(id);
	tname += "{";
	for(auto &f : field_order) {
		tname += fields[f]->str() + ", ";
	}
	if(field_order.size() > 0) {
		tname.pop_back();
		tname.pop_back();
	}
	tname += "}";
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
	if(res == fields.end()) return nullptr;
	return res->second;
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
bool type_func_t::compatible(type_base_t *rhs, const size_t &line, const size_t &col)
{
	if(!compatible_base(rhs, line, col)) return false;
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
// std::string type_func_t::mangled_name()
// {
// 	std::string tname = mangled_name_base();
// 	for(auto &a : args) {
// 		std::string mn = a->mangled_name();
// 		if(mn.empty()) continue;
// 		tname += mn;
// 	}
// 	return tname;
// }

bool type_func_t::add_arg(type_base_t *arg)
{
	args.push_back(arg);
	return true;
}
bool type_func_t::add_arg_copy(type_base_t *arg)
{
	args.push_back(arg->copy());
	return true;
}

void type_func_t::set_args(const std::vector<type_base_t *> &args)
{
	for(auto &a : this->args) {
		delete a;
	}
	this->args = args;
}
void type_func_t::set_args_copy(const std::vector<type_base_t *> &args)
{
	for(auto &a : this->args) {
		delete a;
	}
	this->args.clear();
	for(auto &a : args) {
		this->args.push_back(a->copy());
	}
}

type_base_t *type_func_t::get_arg(const size_t &index)
{
	return args[index];
}

bool update_fncall_types(type_func_t *ft, stmt_base_t *fc, stmt_fncallinfo_t *fci,
			 stmt_fndef_t *&specializedfn)
{
	stmt_fndef_t *fn = nullptr;
	if(ft->parent && ft->parent->type == FNDEF) {
		fn = static_cast<stmt_fndef_t *>(ft->parent);
	}
	if(ft->templ.size() < fci->templates.size()) {
		err::set(fci->line, fci->col,
			 "function call contains more templates than exist in definition");
		return false;
	}
	if(ft->args.size() != fci->args.size()) {
		err::set(fci->line, fci->col, "function call has %zu args, expected: %zu",
			 fci->args.size(), ft->args.size());
		return false;
	}
	std::vector<type_base_t *> templates;
	for(auto &t : fci->templates) {
		templates.push_back(t->vtyp->copy());
	}
	size_t inferred_templates = ft->templ.size() - templates.size();
	if(fci->args.size() < inferred_templates) {
		err::set(fci->line, fci->col, "expected template count: %zu, found: %zu",
			 ft->templ.size(), fci->templates.size() + fci->args.size());
		goto fail;
	}
	for(size_t i = 0; i < inferred_templates; ++i) {
		templates.push_back(fci->args[i]->vtyp->copy());
	}
	if(!fci->specialize(templates)) {
		err::set(fci->line, fci->col, "failed to specialize function call info");
		return false;
	}
	if(fc && !fc->specialize(templates)) {
		err::set(fci->line, fci->col, "failed to specialize function call");
		return false;
	}
	// TODO: copy function before specialization (original must never be specialized)
	if(fn && !fn->specialize(templates)) {
		err::set(fn->line, fn->col, "failed to specialize function");
		return false;
	}
	if(fn) fn->disp(false);
done:
	for(auto &t : templates) delete t;
	return true;
fail:
	for(auto &t : templates) delete t;
	return false;
}
} // namespace parser
} // namespace sc