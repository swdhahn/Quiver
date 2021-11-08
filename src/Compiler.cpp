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
    int lineNumber = 1;
    std::string fileName = path;

    try {
        while (!feof(file)) {
            Compiler::nextSymbol(file, current, nextSymbol, lineNumber);
            Compiler::handleSymbol(file, out_file, current, nextSymbol, fileName, lineNumber);
        }
    } catch(BuildException& e) {
        // I'm considering deleting defective files here, or cleaning the files that just failed to compile
        std::cerr << e.what() << std::endl;
    }

    fclose(file);
    out_file.close();

}

void Compiler::handleSymbol(FILE* in_file, std::ofstream& out_file, std::string& current, char& nSymbol, const std::string& fileName, int& lineNumber) {
    //std::cout << current << std::endl;
    std::string mainWord = current;
    if(mainWord == "class") {
        std::cout << current << std::endl;
        nextSymbol(in_file, current, nSymbol, lineNumber);
        std::string name = current;
        if(!isValidName(name)) {
            throw InvalidName(name, "Class", fileName, lineNumber);
        }
        nextSymbol(in_file, current, nSymbol, lineNumber); // this should be either { or :
        std::string next = current;
        if(next == "{" || next == ":") {
            if (next == "{") {
                out_file << (char)CLASS_BEGIN << (char)SEPARATOR << name << (char)SEPARATOR;
            } else {
                nextSymbol(in_file, current, nSymbol, lineNumber); // this should be name of inherited class
                std::string inheritedClassName = current;
                out_file << (char)CLASS_BEGIN << (char)SEPARATOR << name << (char)SEPARATOR << inheritedClassName << (char)SEPARATOR;
            }
            // handle all words inside of class
            // Should loop through all things in class, and methods should self-contain themselves so this doesn't end early
            std::cout << "We makin class: " << name << std::endl;
            while(current != "}") {
                nextSymbol(in_file, current, nSymbol, lineNumber);
                handleSymbol(in_file, out_file, current, nSymbol, fileName, lineNumber);
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
            nextSymbol(in_file, current, nSymbol, lineNumber);
            std::string name = current;
            nextSymbol(in_file, current, nSymbol, lineNumber);
            std::string next = current;

            if (next == "(") {
                if(!isValidName(name)) {
                    throw InvalidName(name, "Method", fileName, lineNumber);
                }

                // create method
                out_file << (char)METHOD_BEGIN << (char)SEPARATOR << name << (char) SEPARATOR << type << (char) SEPARATOR;

                out_file << (char)PARAMS_BEGIN << (char)SEPARATOR;


                // loop through parameters
                nextSymbol(in_file, current, nSymbol, lineNumber);
                while(current != ")") {
                    out_file << (char)PARAMS_INDEX << (char)SEPARATOR;

                    std::string name, type;
                    bool isPointer = false;

                    int i = 0;

                    while(current != ",") {
                        if(current == ")") {
                            break;
                        }
                        nextSymbol(in_file, current, nSymbol, lineNumber);
                        // IMPLEMENT PARAMETERS
                        if(i == 0 && isLanguageModifier(current)) {

                        } else if((i == 0 || i == 1) && isLanguageType(type = current)) {

                        } else if((i == 1 || i == 2) && current == "*") {
                            isPointer = true;
                        } else {// idk if it is name or not
                            if(!isValidName(name)) {
                                throw InvalidName(name, fileName, lineNumber);
                            }
                        }

                        i++;
                    }
                    nextSymbol(in_file, current, nSymbol, lineNumber);
                }
                out_file << (char)PARAMS_END << (char)SEPARATOR;

                std::cout << "Method: " << type << " " << name << std::endl;
                // CONTENT OF METHOD
                while(current != "}") {
                    nextSymbol(in_file, current, nSymbol, lineNumber);
                    handleSymbol(in_file, out_file, current, nSymbol, fileName, lineNumber);
                }

            } else if(next == ";" || next == "=" || next == "*") {
                if(!isValidName(name)) {
                    throw InvalidName(name, "Variable", fileName, lineNumber);
                }
                bool isPointer = false;
                if(next == "*") {
                    isPointer = true;
                    nextSymbol(in_file, current, nSymbol, lineNumber);
                    next = current;
                }
                if(next == ";") {

                } else if(next == "=") {

                }
                std::cout << "Variable: " << type << " " << name << "  next: " << next << "  pointer: " << isPointer << std::endl;
            } else {
                throw InvalidSymbol(next, fileName, lineNumber);
            }

    }
}

void Compiler::nextSymbol(FILE* file, std::string& current, char& nextSymbol, int& lineNumber) {
    current = "";
    char c = nextSymbol;
    nextSymbol = fgetc(file);

    // removes whitespace until the first character
    while(isWhitespace(c)) {
        if(c == '\n') {
            lineNumber ++;
        }
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
            lineNumber++;
        } else if(c == '/' && nextSymbol == '*') {
            // Removing double line comments: /* ... */
            while(!(c == '*' && nextSymbol == '/')) {
                if(c == '\n') {
                    lineNumber ++;
                }
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




