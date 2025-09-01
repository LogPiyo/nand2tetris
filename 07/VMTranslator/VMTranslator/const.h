#pragma once

#include <string>
#include <set>

enum {
	C_ARITHMETIC,
	C_PUSH,
	C_POP,
	C_LABEL,
	C_GOTO,
	C_IF,
	C_FUNCTION,
	C_RETURN,
	C_CALL,
};

const std::set<std::string> arithmetic = {
	"add",
	"sub",
	"neg",
	"eq",
	"gt",
	"lt",
	"and",
	"or",
	"not",
};