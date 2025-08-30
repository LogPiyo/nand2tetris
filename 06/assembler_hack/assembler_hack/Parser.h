#pragma once

class Parser
{
	public:
		static void advance(std::string*);
		static int instructionType(std::string line);
		static std::string symbol(std::string line);
		static std::string dest(std::string);
		static std::string comp(std::string);
		static std::string jump(std::string);
};

