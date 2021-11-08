//
// Created by Seth H. on 11/4/2021.
//

#ifndef QUIVER_COMPILER_H
#define QUIVER_COMPILER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Constants.h"

class Compiler {
public:
    void compile(const char* file);

private:
    // gets the next word, skips over whitespace
    void nextSymbol(FILE* file, std::string& currentWord, char& nextSymbol, int& lineNumber);

    // writes words and meanings to compiled file
    void handleSymbol(FILE* in_file, std::ofstream& out_file, std::string& current, char& nextSymbol, const std::string& fileName, int& lineNumber);

};


#endif //QUIVER_COMPILER_H
