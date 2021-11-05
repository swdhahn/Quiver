//
// Created by Seth H. on 11/4/2021.
//

#ifndef QUIVER_COMPILER_H
#define QUIVER_COMPILER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Constants.h"

class Compiler {
public:
    void compile(const char* file);

private:
    // gets the next word, skips over whitespace
    void nextWord(FILE* file, std::string& currentWord);

    // checks if character is whitespace
    bool isWhitespace(const char& c);

    // writes words and meanings to compiled file
    void handleWord(FILE* in_file, std::ofstream& out_file, std::string& current);

};


#endif //QUIVER_COMPILER_H
