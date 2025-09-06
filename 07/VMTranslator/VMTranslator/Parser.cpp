#include "Parser.h"
#include "const.h"

#include <sstream>

void Parser::advance(std::string* line)
{
    // Remove comments
    size_t commentPos = line->find("//");
    if (commentPos != std::string::npos) {
        *line = line->substr(0, commentPos);
    }
    
    // Trim leading and trailing whitespace, but keep internal spaces.
    const std::string whitespace = " \t\n\r\f\v";
    size_t first = line->find_first_not_of(whitespace);
    if (std::string::npos == first) {
        *line = "";
        return;
    }
    size_t last = line->find_last_not_of(whitespace);
    *line = line->substr(first, (last - first + 1));
}

int Parser::commandType(std::string line)
{
    std::istringstream iss(line);
    std::string first;
    iss >> first;
    
    if (arithmetic.count(first)) {
        return C_ARITHMETIC;
    }
    else if (first == "push") {
        return C_PUSH;
    }
    else if (first == "pop") {
        return C_POP;
    }
    else if (first == "label") {
        return C_LABEL;
    }
    else if (first == "goto") {
        return C_GOTO;
    }
    else if (first == "if-goto") {
        return C_IF;
    }
    else {
        return -1;
    }
}

std::string Parser::arg1(std::string line)
{
    std::istringstream iss(line);

    switch (Parser::commandType(line)) {
        case C_ARITHMETIC:
        {
            std::string first;
            iss >> first;
            return first;
        }
        case C_PUSH:
        case C_POP:
        case C_LABEL:
        case C_GOTO:
        case C_IF:
        {
			std::string first;
            std::string second;
            iss >> first >> second;
            return second;
        }
        default:
            return "";
    }
}

std::string Parser::arg2(std::string line)
{
    std::istringstream iss(line);
    std::string first;
	std::string second;
	std::string third;
    iss >> first >> second >> third;
    return third;
}