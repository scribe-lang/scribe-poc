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
type_base_t::type_base_t(const Types &type, const size_t &ptr, const size_t &info)
	: id(gen_id()), type(type), ptr(ptr), info(info)
{}
type_base_t::type_base_t(const int64_t &id, const Types &type, const size_t &ptr,
			 const size_t &info)
	: id(id), type(type), ptr(ptr), info(info)
{}
type_base_t::~type_base_t() {}
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

type_simple_t::type_simple_t(const size_t &ptr, const size_t &info, const std::string &name)
	: type_base_t(TSIMPLE, ptr, info), is_template(false), name(name)
{}
type_simple_t::type_simple_t(const size_t &ptr, const size_t &info, const bool &is_template,
			     const std::string &name)
	: type_base_t(TSIMPLE, ptr, info), is_template(is_template), name(name)
{}
type_simple_t::type_simple_t(const int64_t &id, const size_t &ptr, const size_t &info,
			     const bool &is_template, const std::string &name)
	: type_base_t(id, TSIMPLE, ptr, info), is_template(is_template), name(name)
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
	return new type_simple_t(id, ptr, info, is_template, name);
}

type_base_t *type_simple_t::specialize(const std::vector<type_base_t *> &templs)
{
	return nullptr;
}

type_struct_t::type_struct_t(const size_t &ptr, const size_t &info,
			     const std::vector<std::string> &templ,
			     const std::vector<std::string> &field_order,
			     const std::unordered_map<std::string, type_base_t *> &fields)
	: type_base_t(TSTRUCT, ptr, info), is_decl_only(false), templ(templ),
	  field_order(field_order), fields(fields)
{}
type_struct_t::type_struct_t(const int64_t &id, const size_t &ptr, const size_t &info,
			     const std::vector<std::string> &templ,
			     const std::vector<std::string> &field_order,
			     const std::unordered_map<std::string, type_base_t *> &fields)
	: type_base_t(id, TSTRUCT, ptr, info), is_decl_only(false), templ(templ),
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
	return new type_struct_t(id, ptr, info, templ, field_order, newfields);
}
type_base_t *type_struct_t::specialize(const std::vector<type_base_t *> &templs)
{
	return nullptr;
}
std::string type_struct_t::str()
{
	std::string tname = str_base() + "struct." + std::to_string(id);
	if(!templ.empty()) {
		tname += "<";
		for(auto &t : templ) {
			tname += t + ", ";
		}
		tname.pop_back();
		tname.pop_back();
		tname += ">";
	}
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
	fields[name] = val;
	return true;
}
bool type_struct_t::add_field_copy(const std::string &name, type_base_t *val)
{
	if(fields.find(name) != fields.end()) return false;
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

type_func_t::type_func_t(const size_t &ptr, const size_t &info,
			 const std::vector<std::string> &templ,
			 const std::vector<type_base_t *> &args, type_base_t *rettype)
	: type_base_t(TFUNC, ptr, info), templ(templ), args(args), rettype(rettype)
{}
type_func_t::type_func_t(const int64_t &id, const size_t &ptr, const size_t &info,
			 const std::vector<std::string> &templ,
			 const std::vector<type_base_t *> &args, type_base_t *rettype)
	: type_base_t(id, TFUNC, ptr, info), templ(templ), args(args), rettype(rettype)
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
	return new type_func_t(id, ptr, info, templ, newargs, rettype->copy());
}

type_base_t *type_func_t::specialize(const std::vector<type_base_t *> &templs)
{
	return nullptr;
}

std::string type_func_t::str()
{
	std::string tname = str_base() + "fn." + std::to_string(id);
	if(!templ.empty()) {
		tname += "<";
		for(auto &t : templ) {
			tname += t + ", ";
		}
		tname.pop_back();
		tname.pop_back();
		tname += ">";
	}
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

} // namespace parser
} // namespace sc