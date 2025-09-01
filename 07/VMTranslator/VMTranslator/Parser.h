#pragma once

#include <string>

class Parser
{
	public:
		static int commandType(std::string line);
		static std::string arg1(std::string line);
		static std::string arg2(std::string line);
};

