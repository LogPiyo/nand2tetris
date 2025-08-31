// assembler_hack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <direct.h>
#include "const.h"
#include "Parser.h"
#include "Code.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
		return 1;
	}

	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::cout << "Current working dir: " << buff << std::endl;
	std::cout << "Attempting to open file: " << argv[1] << std::endl;

	std::map<std::string, int> symbolTable = initialSymbolTable;

	std::vector<std::string> lines;
	std::ifstream input(argv[1]);
	std::string outputFileName = std::string(argv[1]).substr(0, std::string(argv[1]).find_last_of('.')) + ".hack";
	std::ofstream output(outputFileName);
	if (!input.is_open()) {
		std::cerr << "DEBUG: Entered the 'if (!input.is_open())' block." << std::endl;
		std::cerr << "Error: Could not open file " << argv[1] << std::endl;
		return 1;
	}

	std::cout << "DEBUG: File opened successfully. Proceeding to read." << std::endl;
	std::string line;
	int lineno = 0;

	// First pass: handle labels
	while (std::getline(input, line)) {
		Parser::advance(&line);
		if (line.empty()) continue;

		if (line[0] == '(') {
			std::string symbol = line.substr(1, line.length() - 2);
			if (!symbolTable.count(symbol)) {
				symbolTable[symbol] = lineno;
			}
			continue;
		}

		lineno++;
		lines.push_back(line);
	}

	// Second pass: handle A and C instructions
	for (auto line : lines) {
		Parser::advance(&line);

		std::string symbol;
		std::string dest;
		std::string comp;
		std::string jump;

		int instructionType = Parser::instructionType(line);

		switch (instructionType) {
		case A_INSTRUCTION:
		{
			symbol = Parser::symbol(line);
			std::cout << "DEBUG: Processing A/L-instruction, symbol: " << symbol << std::endl;

			// シンボルが数字のみで構成されているかチェック
			bool is_numeric = !symbol.empty();
			if (is_numeric) {
				for (char const& c : symbol) {
					if (std::isdigit(c) == 0) {
						is_numeric = false;
						break;
					}
				}
			}

			if (is_numeric) {
				// 数字ならバイナリに変換
				output << "0" + std::bitset<15>(std::stoi(symbol)).to_string() << '\n';
			}
			else if (symbolTable.count(symbol)) {
				output << "0" + std::bitset<15>(symbolTable[symbol]).to_string() << '\n';
			}
			else {
				std::cerr << "Error: Undefined symbol " << symbol << std::endl;
			}
			break;
		}
		case L_INSTRUCTION:
			break;
		case C_INSTRUCTION:
			dest = Parser::dest(line);
			comp = Parser::comp(line);
			jump = Parser::jump(line);
			std::cout << "DEBUG: Processing C-instruction" << std::endl;
			output << "111" + Code::comp(comp) + Code::dest(dest) + Code::jump(jump) << '\n';
			break;
		}
	}
	std::cout << std::flush;

	input.close();
	output.close();
	std::cout << "completed" << std:: endl;

	return 0;
}
