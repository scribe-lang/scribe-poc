/*
	MIT License
	Copyright (c) 2021 Scribe Language Repositories
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#ifndef CODEGEN_BASE_HPP
#define CODEGEN_BASE_HPP

#include "Args.hpp"
#include "Parser.hpp"

namespace sc
{
namespace codegen
{
// derive from this class
class Driver
{
protected:
	parser::RAIIParser &parser;
	args::ArgParser &args;

public:
	Driver(parser::RAIIParser &parser);
	virtual ~Driver();
	virtual bool genIR()				 = 0;
	virtual void dumpIR(const bool &force)		 = 0;
	virtual bool genObjFile(const std::string &dest) = 0;
};
} // namespace codegen
} // namespace sc

#endif // CODEGEN_BASE_HPP