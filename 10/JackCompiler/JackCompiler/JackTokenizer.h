#pragma once

#include <string>
#include "const.h"

class JackTokenizer
{
	public:
		static Token* tokenize(char* p);
		static void compile(std::ofstream& output, Token* head);
		static std::string getToken(Token* token);
};

