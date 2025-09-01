#pragma once

#include <string>

class CodeWriter
{
	public:
		static void writeArithmetic(std::ofstream &output, std::string command);
		static void writePushPop(std::ofstream &output, std::string command, std::string argument, int index);
};

