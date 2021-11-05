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

    std::string current = "";

    while(!feof(file)) {
        nextWord(file, current);
        //std::cout << current << std::endl;
        handleWord(file, out_file, current);
    }

    fclose(file);
    out_file.close();

}

void Compiler::handleWord(FILE* in_file, std::ofstream& out_file, std::string& current) {
    std::cout << current << std::endl;
    std::string mainWord = current;
    if(mainWord == "class") {
        nextWord(in_file, current);
        std::string name = current;
        nextWord(in_file, current); // this should be either { or :
        std::string next = current;
        if(next == "{" || next == ":") {
            if (next == "{") {
                out_file << CLASS_CREATION << SEPARATOR << name << SEPARATOR << BEGIN << SEPARATOR;
            } else {
                nextWord(in_file, current); // this should be name of inherited class
                std::string inheritedClassName = current;
                out_file << CLASS_CREATION << SEPARATOR << name << SEPARATOR << inheritedClassName << SEPARATOR << BEGIN << SEPARATOR;
            }
            // handle all words inside of class
            while(current != "}") {
                nextWord(in_file, current);
                handleWord(in_file, out_file, current);
            }

            // end class
            out_file << END << SEPARATOR;

        } else {
            std::cerr << "Class " << name << " is missing either { or : after its' definition." << std::endl;
            return;
        }
    }
    // Methods and variables
    for(int i = 0; i < LANGUAGE_TYPE_COUNT; i++) {
        // either function or variable
        if(mainWord == LanguageTypes[i]) {
            std::string type = LanguageTypes[i];
            nextWord(in_file, current);
            std::string name = current;
            nextWord(in_file, current);
            std::string next = current;
            if(name.find(";") != std::string::npos || next.find(";") != std::string::npos || name.find("=") != std::string::npos || next.find("=") != std::string::npos) {

            }
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
        if(isWhitespace(c) || c == ':' ||c == ';' || c == '=' || c == '}' || feof(file)) {
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


