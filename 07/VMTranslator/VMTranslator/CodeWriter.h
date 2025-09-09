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
		static void writeFunction(std::ofstream& output, std::string functionName, int nVars);
		static void writeCall(std::ofstream& output, std::string functionName, int nArgs);
		static void writeReturn(std::ofstream& output);

		static void bootStrap(std::ofstream& output);
		static void close(std::ofstream& output);
};

