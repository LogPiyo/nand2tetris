#include "Parser.h"
#include "const.h"

#include <sstream>

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