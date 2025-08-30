#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Parser.h"
#include "const.h"

void Parser::advance(std::string* line)
{
	// Remove comments
	size_t commentPos = line->find("//");
	if (commentPos != std::string::npos) {
		*line = line->substr(0, commentPos);
	}

	// Remove whitespace
	line->erase(remove_if(line->begin(), line->end(), isspace), line->end());
}

int Parser::instructionType(std::string line)
{
	if (line.empty()) {
		return -1; // No instruction
	}
	if (line[0] == '@') {
		return A_INSTRUCTION;
	}
	else if (line[0] == '(') {
		return L_INSTRUCTION;
	}
	else {
		return C_INSTRUCTION;
	}
}

std::string Parser::symbol(std::string line)
{
	if (instructionType(line) == A_INSTRUCTION) {
		return line.substr(1);
	}
	else if (instructionType(line) == L_INSTRUCTION) {
		return line.substr(1, line.length() - 2);
	}
	return "";
}

std::string Parser::dest(std::string line)
{
	std::smatch match;

	if (std::regex_match(line, match, std::regex(R"((.+)=(.+);(.+))"))) {
		return match[1].str();
	}

	if (std::regex_match(line, match, std::regex(R"((.+);(.+))"))) {
		return "";
	}

	if (std::regex_match(line, match, std::regex(R"((.+)=(.+))"))) {
		return match[1].str();
	}
	return "";
}

std::string Parser::comp(std::string line)
{
	std::smatch match;

	if (std::regex_match(line, match, std::regex(R"((.+)=(.+);(.+))"))) {
		return match[2].str();
	}

	if (std::regex_match(line, match, std::regex(R"((.+);(.+))"))) {
		return match[1].str();
	}

	if (std::regex_match(line, match, std::regex(R"((.+)=(.+))"))) {
		return match[2].str();
	}
	return "";
}

std::string	Parser::jump(std::string line)
{
	std::smatch match;

	if (std::regex_match(line, match, std::regex(R"((.+)=(.+);(.+))"))) {
		return match[3].str();
	}

	if (std::regex_match(line, match, std::regex(R"((.+);(.+))"))) {
		return match[2].str();
	}

	if (std::regex_match(line, match, std::regex(R"((.+)=(.+))"))) {
		return "";
	}
	return "";
}