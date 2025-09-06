#pragma once

#include <string>

class CodeWriter
{
	public:
		static void writeArithmetic(std::ofstream &output, std::string command, std::string fileName);
		static void writePushPop(std::ofstream &output, std::string command, std::string argument, int index, std::string fileName);
		static void writeLabel(std::ofstream& output, std::string label);
		static void writeGoto(std::ofstream& output, std::string label);
		static void writeIf(std::ofstream& output, std::string label);
};

