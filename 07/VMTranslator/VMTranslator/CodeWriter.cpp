#include "CodeWriter.h"

#include <iostream>
#include <fstream>

static void helperWriteArithmetic(std::ofstream &output, std::string command);
static int labelCounter = 0;

void CodeWriter::writeArithmetic(std::ofstream &output, std::string command)
{
	std::string trueLabel = "TRUE_" + std::to_string(labelCounter);
	std::string falseLabel = "FALSE_" + std::to_string(labelCounter);

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

	if (command == "and") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M\n";
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "M=D&M\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	if (command == "sub") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M\n";
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "M=M-D\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	if (command == "eq") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M\n";
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M-D\n";
		output << "M=0\n";
		output << "@" << trueLabel << '\n';
		output << "D;JEQ\n";
		output << "@" << falseLabel << '\n';
		output << "0;JMP\n";
		output << "(" << trueLabel << ")\n";
		output << "@SP\n";
		output << "A=M\n";
		output << "M=-1\n";
		output << "(" << falseLabel << ")\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	if (command == "lt") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M\n";
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M-D\n";
		output << "M=0\n";
		output << "@" << trueLabel << '\n';
		output << "D;JLT\n";
		output << "@" << falseLabel << '\n';
		output << "0;JMP\n";
		output << "(" << trueLabel << ")\n";
		output << "@SP\n";
		output << "A=M\n";
		output << "M=-1\n";
		output << "(" << falseLabel << ")\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	if (command == "gt") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M\n";
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M-D\n";
		output << "M=0\n";
		output << "@" << trueLabel << '\n';
		output << "D;JGT\n";
		output << "@" << falseLabel << '\n';
		output << "0;JMP\n";
		output << "(" << trueLabel << ")\n";
		output << "@SP\n";
		output << "A=M\n";
		output << "M=-1\n";
		output << "(" << falseLabel << ")\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	if (command == "or") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "D=M\n";
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "M=D|M\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	if (command == "not") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "M=!M\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	if (command == "neg") {
		output << "@SP\n";
		output << "M=M-1\n";
		output << "A=M\n";
		output << "M=-M\n";
		output << "@SP\n";
		output << "M=M+1\n";
	}

	labelCounter++;
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

static void helperWriteArithmetic(std::ofstream &output, std::string command) {
	std::string outputString = "";
	if (command == "add") {
		outputString = "M=D+M";
	}
	else if (command == "sub") {
		outputString = "M=M-D";
	}
	else if (command == "and") {
		outputString = "M=D&M";
	}
}


