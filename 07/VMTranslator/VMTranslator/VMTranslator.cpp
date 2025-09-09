// VMTranslator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Parser.h"
#include "CodeWriter.h"
#include "const.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "invalid" << std::endl;
        return 1;
    }

    fs::path inputPath(argv[1]);
    std::vector<fs::path> vmFiles;
    fs::path outputPath;

    if (fs::is_directory(inputPath)) {
        outputPath = inputPath / (inputPath.filename().string() + ".asm");
        for (const auto& entry : fs::directory_iterator(inputPath)) {
            if (entry.path().extension() == ".vm") {
                vmFiles.push_back(entry.path());
            }
        }
    }
    else {
        vmFiles.push_back(inputPath);
        std::string fileName = inputPath.stem().string();
        outputPath = inputPath.parent_path() / (fileName + ".asm");
    }

    std::ofstream output(outputPath);
    if (!output) {
        std::cerr << "Failed to open!" << std::endl;
        return 1;
    }

    CodeWriter::bootStrap(output);

    for (const auto& vmPath : vmFiles) {
        std::ifstream input(vmPath);
        if (!input) {
            std::cerr << "Failed to open!" << std::endl;
            continue;
        }

        std::string fileName = vmPath.stem().string();
        std::string line;

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
    }

    CodeWriter::close(output);

    return 0;
}

