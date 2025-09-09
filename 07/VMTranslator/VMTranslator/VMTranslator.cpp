// VMTranslator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Parser.h"
#include "CodeWriter.h"
#include "const.h"

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "invalid" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Failed to open!" << std::endl;
        return 1;
    }

    std::string fileName = std::string(argv[1]).substr(0, std::string(argv[1]).find_last_of('.'));
    std::string outputFile = fileName + ".asm";
    std::ofstream output(outputFile);

    std::string line;

    CodeWriter::bootStrap(output);

    while (std::getline(input, line)) {
        Parser::advance(&line);

        int commandType = Parser::commandType(line);

        switch (commandType) {
            case C_ARITHMETIC:
            {
                std::string arg1 = Parser::arg1(line);
                CodeWriter::writeArithmetic(output, arg1, fileName);
                break;
            }
            case C_POP:
            case C_PUSH:
            {
                std::string arg1 = Parser::arg1(line);
                std::string arg2 = Parser::arg2(line);
				CodeWriter::writePushPop(output, commandType == C_PUSH ? "push" : "pop", arg1, std::stoi(arg2), fileName);
                break;
            }
            case C_LABEL:
            {
                std::string arg1 = Parser::arg1(line);
                CodeWriter::writeLabel(output, arg1);
                break;
            }
            case C_GOTO:
            {
                std::string arg1 = Parser::arg1(line);
                CodeWriter::writeGoto(output, arg1);
                break;
            }
            case C_IF:
            {
                std::string arg1 = Parser::arg1(line);
                CodeWriter::writeIf(output, arg1);
                break;
            }
            case C_FUNCTION:
            {
                std::string arg1 = Parser::arg1(line);
                std::string arg2 = Parser::arg2(line);
                CodeWriter::writeFunction(output, arg1, std::stoi(arg2));
                break;
            }
            case C_CALL:
            {
                std::string arg1 = Parser::arg1(line);
                std::string arg2 = Parser::arg2(line);
                CodeWriter::writeCall(output, arg1, std::stoi(arg2));
                break;
            }
            case C_RETURN:
            {
                CodeWriter::writeReturn(output);
                break;
            }
            default:
                continue;
        }
    }

    CodeWriter::close(output);
}

