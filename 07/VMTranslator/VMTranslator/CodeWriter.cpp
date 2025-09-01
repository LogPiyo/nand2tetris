#include "CodeWriter.h"

#include <iostream>
#include <fstream>

void CodeWriter::writeArithmetic(std::ofstream &output, std::string command)
{
	if (command == "add") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
        output << "D=M\n";
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
        output << "M=D+M\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}
}

void CodeWriter::writePushPop(std::ofstream &output, std::string command, std::string argument, int index)
{
	if (command == "push") {
		if (argument == "constant") {
			output << "@" << index << "\n";
			output << "D=A\n";
			output << "@SP\n";
			output << "A=M\n";
			output << "M=D\n";
			output << "@SP\n";
			output << "M=M+1\n";
		}
	}
}




