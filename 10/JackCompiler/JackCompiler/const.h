#pragma once

#include <string>
#include <vector>
#include <set>

typedef enum
{
	KEYWORD,
	SYMBOL,
	IDENTIFIER,
	INT_CONST,
	STRING_CONST,
	TK_EOF,
} TokenType;

typedef struct Token
{
	TokenType type;
	Token* next;
	int value;
	std::string str;
	std::string symbol;
	std::string keyword;
	std::string identifier;

	Token() {
		this->next = nullptr;
	}

	Token(TokenType type, Token* next, std::string token) {
		this->type = type;
		this->next = next;

		switch (this->type) {
		case KEYWORD:
			this->keyword = token;
			break;
		case SYMBOL:
			this->symbol = token;
			break;
		case IDENTIFIER:
			this->identifier = token;
			break;
		case INT_CONST:
			this->value = stoi(token);
			break;
		case STRING_CONST:
			this->str = token;
			break;
		}
	}
} Token;

enum keyWord
{
	CLASS,
	METHOD,
	FUNCTION,
	CONSTRUCTOR,
	INT,
	BOOLEAN,
	CHAR,
	VOID,
	VAR,
	STATIC,
	FIELD,
	LET,
	DO,
	IF,
	ELSE,
	WHILE,
	RETURN,
	TRUE,
	FALSE,
	NULL_,
	THIS
};

const std::set<std::string> keywords = {
	"class",
	"method",
	"function",
	"constructor",
	"int",
	"boolean",
	"char",
	"void",
	"var",
	"static",
	"field",
	"let",
	"do",
	"if",
	"else",
	"while",
	"return",
	"true",
	"false",
	"null",
	"this",
};

const std::set<char> symbols = {
	'+',
	'-',
	'*',
	'/',
	'&',
	'|',
	'<',
	'>',
	'=',
	'~',
	'(',
	')',
	'{',
	'}',
	'[',
	']',
	'.',
	',',
	';',
};

const std::vector<std::string> types = {
	"keyword",
	"symbol",
	"identifier",
	"integerConstant",
	"stringConstant",
};