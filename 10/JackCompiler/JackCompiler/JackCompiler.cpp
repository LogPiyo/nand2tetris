// JackCompiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "JackTokenizer.h"
#include "CompilationEngine.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return EXIT_FAILURE;
	}

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Could not open the file - '" << argv[1] << "'" << std::endl;
        return EXIT_FAILURE;
	}
    
    std::string fileContent((std::istreambuf_iterator<char>(input)),
    std::istreambuf_iterator<char>());
  
    Token* head = JackTokenizer::tokenize(&fileContent[0]);

	std::string inputFileName = argv[1];
	size_t dotPos = inputFileName.find_last_of('.');
	std::string outputFileName = (dotPos == std::string::npos)
		? inputFileName + ".xml"
		: inputFileName.substr(0, dotPos) + ".xml";
	std::ofstream output(outputFileName);

    if (!output.is_open()) {
        std::cerr << "Could not open the file - '" << argv[1] << "'" << std::endl;
        return EXIT_FAILURE;
    }

    JackTokenizer::compile(output, head);

    return EXIT_SUCCESS;
}
