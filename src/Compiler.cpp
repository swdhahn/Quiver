//
// Created by Seth H. on 11/4/2021.
//

#include "Compiler.h"

void Compiler::compile(const char* path) {



    FILE* file;
    if(!(file = std::fopen(path, "r"))) {
        std::cout << "File does not exist: " << path << std::endl;
        return;
    }
    std::ofstream out_file (std::string(path) + std::string("_obj"));

    char c = 0;
    std::string current = "";

    int currentMode = -1; // -1 for nothing, 0 for class, 1 for method
    while(!feof(file)) {
        nextWord(file, current);
        std::cout << current << std::endl;
        handleWord(file, out_file, current);
    }

    fclose(file);
    out_file.close();

}

void Compiler::handleWord(FILE* in_file, std::ofstream& out_file, std::string& current) {
    std::string mainWord = current;
    if(mainWord == "class") {
        nextWord(in_file, current);
        std::string name = current;
        nextWord(in_file, current); // this should be either { or :
        std::string next = current;
        if(next == "{" || next == ":") {
            out_file << CLASS_CREATION << SEPARATOR << name << SEPARATOR << BEGIN;
        } else if(next == ":") {
            nextWord(in_file, current); // this should be name of inherited class
            std::string inheritedClassName = current;
            out_file << CLASS_CREATION << SEPARATOR << name << SEPARATOR << inheritedClassName << SEPARATOR << BEGIN;
        } else {
            std::cerr << "Class " << name << " is missing either { or : after its' definition." << std::endl;
            return;
        }
    }
}

void Compiler::nextWord(FILE* file, std::string& current) {
    current = "";
    char prev_c = 0;
    char c = fgetc(file);
    // removes whitespace until the first character
    while(isWhitespace(c)) {
        prev_c = c;
        c = fgetc(file);
    }

    // check if the file ends prematurely
    while(1) {
        // end word
        if(isWhitespace(c) || feof(file)) {
            return;
        } else if(prev_c == '/' && c == '/') {
            // Removing single line comments: //
            current.pop_back();
            while(c != '\n') {
                prev_c = c;
                c = fgetc(file);
            }
            if(current == "") {
                nextWord(file, current);
            }
        } else if(prev_c == '/' && c == '*') {
            // Removing double line comments: /* ... */
            current.pop_back();
            while(!(prev_c == '*' && c == '/')) {
                prev_c = c;
                c = fgetc(file);
            }
            if(current == "") {
                nextWord(file, current);
            }
        } else {
            current += c;
        }
        prev_c = c;
        c = fgetc(file);
    }
}

bool Compiler::isWhitespace(const char& c) {
    return (c == ' ' || c == '\n');
}


