#include "CodeWriter.h"

#include <iostream>
#include <fstream>

// Arithmetic helpers
static void writeArithmeticAddSubAndOr(std::ofstream& output, std::string insertedString);
static void writeArithmeticNotNeg(std::ofstream& output, std::string insertedString);
static void writeArithmeticEqLtGt(std::ofstream& output, std::string insertedString, std::string trueLabel, std::string falseLabel);

// Push/Pop helpers
static void writePushLocalLike(std::ofstream& output, std::string insertedString, int index);
static void writePopLocalLike(std::ofstream& output, std::string insertedString, int index);
static void writePushPointer(std::ofstream& output, int index);
static void writePopPointer(std::ofstream& output, int index);
static void writePushConstant(std::ofstream& output, int index);
static void writePushTemp(std::ofstream& output, int index);
static void writePushStatic(std::ofstream& output, std::string fileName, int index);
static void writePopConstant(std::ofstream& output);
static void writePopTemp(std::ofstream& output, int index);
static void writePopStatic(std::ofstream& output, std::string fileName, int index);

static int labelCounter = 0;

void CodeWriter::writeArithmetic(std::ofstream &output, std::string command, std::string fileName)
{
	std::string trueLabel = "TRUE_" + std::to_string(labelCounter);
	std::string falseLabel = "FALSE_" + std::to_string(labelCounter);

	if (command == "add") {
		writeArithmeticAddSubAndOr(output, "M=D+M");
	}

	if (command == "sub") {
		writeArithmeticAddSubAndOr(output, "M=M-D");
	}

	if (command == "and") {
		writeArithmeticAddSubAndOr(output, "M=D&M");
	}

	if (command == "or") {
		writeArithmeticAddSubAndOr(output, "M=D|M");
	}

	if (command == "eq") {
		writeArithmeticEqLtGt(output, "JEQ", trueLabel, falseLabel);
	}

	if (command == "lt") {
		writeArithmeticEqLtGt(output, "JLT", trueLabel, falseLabel);
	}

	if (command == "gt") {
		writeArithmeticEqLtGt(output, "JGT", trueLabel, falseLabel);
	}

	if (command == "not") {
		writeArithmeticNotNeg(output, "M=!M");
	}

	if (command == "neg") {
		writeArithmeticNotNeg(output, "M=-M");
	}

	labelCounter++;
}

void CodeWriter::writePushPop(std::ofstream &output, std::string command, std::string argument, int index, std::string fileName)
{
	if (command == "push") {
		if (argument == "constant") {
			writePushConstant(output, index);
		}

		if (argument == "local") {
			writePushLocalLike(output, "LCL", index);
		}

		if (argument == "argument") {
			writePushLocalLike(output, "ARG", index);
		}

		if (argument == "this") {
			writePushLocalLike(output, "THIS", index);
		}

		if (argument == "that") {
			writePushLocalLike(output, "THAT", index);
		}

		if (argument == "temp") {
			writePushTemp(output, index);
		}

		if (argument == "pointer") {
			writePushPointer(output, index);
		}

		if (argument == "static") {
			writePushStatic(output, fileName, index);
		}
	}

	if (command == "pop") {
		if (argument == "constant") {
			writePopConstant(output);
		}

		if (argument == "local") {
			writePopLocalLike(output, "LCL", index);
		}

		if (argument == "argument") {
			writePopLocalLike(output, "ARG", index);
		}

		if (argument == "this") {
			writePopLocalLike(output, "THIS", index);
		}

		if (argument == "that") {
			writePopLocalLike(output, "THAT", index);
		}

		if (argument == "temp") {
			writePopTemp(output, index);
		}

		if (argument == "pointer") {
			writePopPointer(output, index);
		}

		if (argument == "static") {
			writePopStatic(output, fileName, index);
		}
	}
}

void CodeWriter::writeLabel(std::ofstream& output, std::string label) {
	output << "(" << label << ")\n";
}

void CodeWriter::writeGoto(std::ofstream& output, std::string label) {
	output << "@" << label << "\n";
	output << "0;JMP\n";
}

void CodeWriter::writeIf(std::ofstream& output, std::string label) {
	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << "D=M\n";
	output << "@" << label << "\n";
	output << "D;JNE\n";
}

static void writeArithmeticAddSubAndOr(std::ofstream &output, std::string insertedString) {
	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << "D=M\n";
	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << insertedString << "\n";
	output << "@SP\n";
	output << "M=M+1\n";
}

static void writeArithmeticNotNeg(std::ofstream& output, std::string insertedString) {
	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << insertedString << "\n";
	output << "@SP\n";
	output << "M=M+1\n";
}

static void writeArithmeticEqLtGt(std::ofstream& output, std::string insertedString, std::string trueLabel, std::string falseLabel) {
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
	output << "D;" << insertedString << "\n";
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

static void writePushLocalLike(std::ofstream& output, std::string insertedString, int index) {
	output << "@" << index << "\n";
	output << "D=A\n";
	output << "@" << insertedString << "\n";
	output << "A=D+M\n";
	output << "D=M\n";
	output << "@SP\n";
	output << "A=M\n";
	output << "M=D\n";
	output << "@SP\n";
	output << "M=M+1\n";
}

static void writePopLocalLike(std::ofstream& output, std::string insertedString, int index) {
	output << "@" << insertedString << "\n";
	output << "D=M\n";
	output << "@" << index << "\n";
	output << "D=D+A\n";
	output << "@R13\n";
	output << "M=D\n";
	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << "D=M\n";
	output << "@R13\n";
	output << "A=M\n";
	output << "M=D\n";
}

static void writePushPointer(std::ofstream& output, int index) {
	std::string insertedString = "";

	switch (index) {
	case 0:
		insertedString = "THIS";
		break;
	case 1:
		insertedString = "THAT";
		break;
	default:
		throw "Invaild argument in writePopPointer function";
	}

	output << "@" << insertedString << "\n";
	output << "D=M\n";
	output << "@SP\n";
	output << "A=M\n";
	output << "M=D\n";
	output << "@SP\n";
	output << "M=M+1\n";
}

static void writePopPointer(std::ofstream& output, int index) {
	std::string insertedString = "";

	switch (index) {
		case 0:
			insertedString = "THIS";
			break;
		case 1:
			insertedString = "THAT";
			break;
		default:
			throw "Invaild argument in writePopPointer function";
	}

	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << "D=M\n";
	output << "@" << insertedString << "\n";
	output << "M=D\n";
}

static void writePushConstant(std::ofstream& output, int index) {
	output << "@" << index << "\n";
	output << "D=A\n";
	output << "@SP\n";
	output << "A=M\n";
	output << "M=D\n";
	output << "@SP\n";
	output << "M=M+1\n";
}

static void writePushTemp(std::ofstream& output, int index) {
	output << "@" << 5 + index << "\n";
	output << "D=M\n";
	output << "@SP\n";
	output << "A=M\n";
	output << "M=D\n";
	output << "@SP\n";
	output << "M=M+1\n";
}

static void writePushStatic(std::ofstream& output, std::string fileName, int index) {
	output << "@" << fileName << "." << index << "\n";
	output << "D=M\n";
	output << "@SP\n";
	output << "A=M\n";
	output << "M=D\n";
	output << "@SP\n";
	output << "M=M+1\n";
}

static void writePopConstant(std::ofstream& output) {
	output << "@SP\n";
	output << "M=M-1\n";
}

static void writePopTemp(std::ofstream& output, int index) {
	output << "@" << 5 + index << "\n";
	output << "D=A\n";
	output << "@R13\n";
	output << "M=D\n";
	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << "D=M\n";
	output << "@R13\n";
	output << "A=M\n";
	output << "M=D\n";
}

static void writePopStatic(std::ofstream& output, std::string fileName, int index) {
	output << "@SP\n";
	output << "M=M-1\n";
	output << "A=M\n";
	output << "D=M\n";
	output << "@" << fileName << "." << index << "\n";
	output << "M=D\n";
}