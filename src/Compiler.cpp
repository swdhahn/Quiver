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
    char nextSymbol = 0;

    while(!feof(file)) {
        Compiler::nextSymbol(file, current, nextSymbol);
        Compiler::handleSymbol(file, out_file, current, nextSymbol);
    }

    fclose(file);
    out_file.close();

}

void Compiler::handleSymbol(FILE* in_file, std::ofstream& out_file, std::string& current, char& nSymbol) {
    //std::cout << current << std::endl;
    std::string mainWord = current;
    if(mainWord == "class") {
        std::cout << current << std::endl;
        nextSymbol(in_file, current, nSymbol);
        std::string name = current;
        nextSymbol(in_file, current, nSymbol); // this should be either { or :
        std::string next = current;
        if(next == "{" || next == ":") {
            if (next == "{") {
                out_file << (char)CLASS_BEGIN << (char)SEPARATOR << name << (char)SEPARATOR;
            } else {
                nextSymbol(in_file, current, nSymbol); // this should be name of inherited class
                std::string inheritedClassName = current;
                out_file << (char)CLASS_BEGIN << (char)SEPARATOR << name << (char)SEPARATOR << inheritedClassName << (char)SEPARATOR;
            }
            // handle all words inside of class
            // Should loop through all things in class, and methods should self-contain themselves so this doesn't end early
            std::cout << "We makin class: " << name << std::endl;
            while(current != "}") {
                nextSymbol(in_file, current, nSymbol);
                handleSymbol(in_file, out_file, current, nSymbol);
            }

            // end class
            out_file << (char)CLASS_END << (char)SEPARATOR;

        } else {
            std::cerr << "Class " << name << " is missing either { or : after its' definition." << std::endl;
            return;
        }
    }
    // Methods and variables

        // either function or variable
        if(isLanguageType(mainWord)) {
            std::string type = mainWord;
            nextSymbol(in_file, current, nSymbol);
            std::string name = current;
            nextSymbol(in_file, current, nSymbol);
            std::string next = current;

            if (next == "(") {
                // create method
                out_file << (char)METHOD_BEGIN << (char)SEPARATOR << name << (char) SEPARATOR << type << (char) SEPARATOR;

                out_file << (char)PARAMS_BEGIN << (char)SEPARATOR;


                // loop through parameters
                nextSymbol(in_file, current, nSymbol);
                while(current != ")") {
                    out_file << (char)PARAMS_INDEX << (char)SEPARATOR;

                    std::string name, type;
                    bool isPointer = false;

                    int i = 0;

                    while(current != ",") {
                        if(current == ")") {
                            break;
                        }
                        nextSymbol(in_file, current, nSymbol);
                        // IMPLEMENT PARAMETERS
                        if(i == 0 && isLanguageModifier(current)) {

                        } else if((i == 0 || i == 1) && isLanguageType(type = current)) {

                        } else if((i == 1 || i == 2) && current == "*") {
                            isPointer = true;
                        }

                        i++;
                    }
                    nextSymbol(in_file, current, nSymbol);
                }
                out_file << (char)PARAMS_END << (char)SEPARATOR;

                std::cout << "Method: " << type << " " << name << std::endl;
                // CONTENT OF METHOD
                while(current != "}") {
                    nextSymbol(in_file, current, nSymbol);
                    handleSymbol(in_file, out_file, current, nSymbol);
                }

            } else if(next == ";" || next == "=" || next == "*") {
                bool isPointer = false;
                if(next == "*") {
                    isPointer = true;
                    nextSymbol(in_file, current, nSymbol);
                    next = current;
                }
                if(next == ";") {

                } else if(next == "=") {

                }
                std::cout << "Variable: " << type << " " << name << "  next: " << next << "  pointer: " << isPointer << std::endl;
            } else {
                std::cerr << "Unknown symbol: " << next << std::endl;
            }

    }
}

void Compiler::nextSymbol(FILE* file, std::string& current, char& nextSymbol) {
    current = "";
    char c = nextSymbol;
    nextSymbol = fgetc(file);

    // removes whitespace until the first character
    while(isWhitespace(c)) {
        c = nextSymbol;
        nextSymbol = fgetc(file);
    }

    // check if the file ends prematurely
    while(1) {
        // end word
        if(c == '/' && nextSymbol == '/') {
            // Removing single line comments: //
            while(nextSymbol != '\n') {
                c = nextSymbol;
                nextSymbol = fgetc(file);
            }
        } else if(c == '/' && nextSymbol == '*') {
            // Removing double line comments: /* ... */
            while(!(c == '*' && nextSymbol == '/')) {
                c = nextSymbol;
                nextSymbol = fgetc(file);
            }
            c = nextSymbol;
            nextSymbol = fgetc(file);
        } else if(isWhitespace(nextSymbol) || isSymbol(nextSymbol) || isSymbol(c) || feof(file)) {
            // ends symbol
            current += c;
            return;
        } else {
            // moves onto next character of symbol
            current += c;
        }
        c = nextSymbol;
        nextSymbol = fgetc(file);
    }
}




