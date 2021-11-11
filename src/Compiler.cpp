//
// Created by Seth H. on 11/4/2021.
//

#include "Compiler.h"

Compiler::Compiler(const std::string &path) : m_path(path) {

}

void Compiler::compile(const char* path) {

    FILE* file;
    if(!(file = std::fopen(path, "r"))) {
        std::cout << "File does not exist: " << path << std::endl;
        return;
    }
    std::ofstream out_file (std::string(path) + std::string("_obj"));

    std::string current;
    char nextSymbol = 0;
    int lineNumber = 1;
    int lineOffset = 0;
    std::string fileName = m_path + path;

    try {
        while (!feof(file)) {
            Compiler::nextSymbol(file, current, nextSymbol, lineNumber, lineOffset);
            Compiler::handleSymbol(file, out_file, current, nextSymbol, fileName, lineNumber, lineOffset);
        }
    } catch(BuildException& e) {
        // I'm considering deleting defective files here, or cleaning the files that just failed to compile
        std::cerr << e.what() << std::endl;
        std::exit(-1);
    }

    fclose(file);
    out_file.close();

}

void Compiler::handleSymbol(FILE* in_file, std::ofstream& out_file, std::string& current, char& nSymbol, const std::string& fileName, int& lineNumber, int& lineOffset) {
    //std::cout << current << std::endl;
    bool isRecognized = false;

    std::string mainWord = current;
    if(mainWord == "class") {
        isRecognized = true;
        std::cout << current << std::endl;
        nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
        std::string name = current;
        if(!isValidName(name)) {
            throw InvalidName(name, "Class", fileName, lineNumber, lineOffset);
        }
        nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset); // this should be either { or :
        std::string next = current;
        if(next == "{" || next == ":") {
            if (next == "{") {
                out_file << (char)CLASS_BEGIN << (char)SEPARATOR << name << (char)SEPARATOR;
            } else {
                nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset); // this should be name of inherited class
                std::string inheritedClassName = current;
                out_file << (char)CLASS_BEGIN << (char)SEPARATOR << name << (char)SEPARATOR << inheritedClassName << (char)SEPARATOR;
            }
            // handle all words inside of class
            // Should loop through all things in class, and methods should self-contain themselves so this doesn't end early
            std::cout << "We makin class: " << name << std::endl;
            while(current != "}") {
                nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
                handleSymbol(in_file, out_file, current, nSymbol, fileName, lineNumber, lineOffset);
            }

            // end class
            out_file << (char)CLASS_END << (char)SEPARATOR;

        } else {
            std::cerr << "Class " << name << " is missing either { or : after its' definition." << std::endl;
            throw BuildException(fileName, lineNumber, lineOffset);
        }
    }

    if(isValidName(mainWord)) {
        nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
        std::string name = mainWord;
        std::string next = current;
        if(next == "(") {
            isRecognized = true;
            std::cout << "HEYYY, FUNCTION CALL: " << name << std::endl;

            out_file << (char) METHOD_CALL_BEGIN << (char)SEPARATOR << name << (char) SEPARATOR;

            out_file << (char)PARAMS_BEGIN << (char)SEPARATOR;

            // loop through parameters
            nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
            while(current != ")") {
                out_file << (char)PARAMS_INDEX << (char)SEPARATOR;

                std::string type, value;

                while(current != ",") {
                    if(current == ")") {
                        break;
                    }

                    value += current;

                    nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
                }

                for(int i = 0; i < LANGUAGE_VARIABLE_COUNT; i++) {
                    if(LanguageVariables[i]->canParseData(value)) {
                        type = i;
                        break;
                    }
                }

                out_file << type << (char)SEPARATOR << value << (char)SEPARATOR;
            }
            out_file << (char)PARAMS_END << (char)SEPARATOR;

        }
    }

    // Methods and variables
    std::vector<std::string> modifiers;

    while(isLanguageModifier(mainWord)) {
        //if (isLanguageModifier(mainWord)) {
            modifiers.push_back(mainWord);
            nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
            mainWord = current;
        //}
    }
    // either function or variable
        if(isLanguageType(mainWord)) {
            isRecognized = true;
            std::string type = mainWord;
            nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
            std::string name = current;
            nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
            std::string next = current;

            if (next == "(") {
                if(!isValidName(name)) {
                    throw InvalidName(name, "Method", fileName, lineNumber, lineOffset);
                }

                // create method
                out_file << (char)METHOD_BEGIN << (char)SEPARATOR << name << (char) SEPARATOR << type << (char) SEPARATOR;

                for(int i = 0; i < modifiers.size(); i++) {
                    out_file << modifiers.at(i) << (char)SEPARATOR;
                }

                out_file << (char)PARAMS_BEGIN << (char)SEPARATOR;


                // loop through parameters
                nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
                while(current != ")") {
                    out_file << (char)PARAMS_INDEX << (char)SEPARATOR;

                    std::string name, type, modifier;
                    bool isPointer = false;

                    int i = 0;

                    while(current != ",") {
                        if(current == ")") {
                            break;
                        }


                        // IMPLEMENT PARAMETERS
                        if(i == 0 && isLanguageModifier(current)) {
                            modifier = current;
                        } else if((i == 0 || i == 1) && isLanguageType(current)) {
                            type = current;
                        } else if((i == 1 || i == 2) && current == "*") {
                            isPointer = true;
                        } else { // check if we got name
                            name = current;
                            if(!isValidName(name)) {
                                throw InvalidName(name, fileName, lineNumber, lineOffset);
                            }
                        }

                        nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
                        i++;
                    }
                    //std::cout << "type: " << type << "  name: " << name << "  pointer: " << isPointer << "  modifier: " << modifier << std::endl;
                    // NEED TO ADD MODIFIER & POINTER to params in compiler
                    out_file << type << (char)SEPARATOR << name << (char)SEPARATOR;
                }
                out_file << (char)PARAMS_END << (char)SEPARATOR;

                std::cout << "Method: " << type << " " << name << std::endl;
                // CONTENT OF METHOD
                while(current != "}") {
                    nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
                    handleSymbol(in_file, out_file, current, nSymbol, fileName, lineNumber, lineOffset);
                }

                out_file << (char)METHOD_END << (char)SEPARATOR;

            } else if(next == ";" || next == "=" || next == "*") {
                if(!isValidName(name)) {
                    throw InvalidName(name, "Variable", fileName, lineNumber, lineOffset);
                }
                bool isPointer = false;
                if(next == "*") {
                    isPointer = true;
                    nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
                    next = current;
                }
                if(next == ";") {
                    out_file << (char)VARIABLE_CREATION << (char) SEPARATOR << name << (char)SEPARATOR << type << (char) SEPARATOR << 0 << (char)SEPARATOR;
                } else if(next == "=") {
                    const Variable* v = getVariableFromType(type);

                    // VARIABLES CAN ONLY HANDLE SINGLE VALUE - no mult or operators on variables
                    nextSymbol(in_file, current, nSymbol, lineNumber, lineOffset);
                    std::string data = current;

                    if(v->canParseData(data)) {
                        out_file << (char)VARIABLE_CREATION << (char) SEPARATOR << name << (char)SEPARATOR << type << (char) SEPARATOR << data << (char)SEPARATOR;
                    } else {
                        throw InvalidAssignment(type, data, fileName, lineNumber, lineOffset);
                    }
                }
                std::cout << "Variable: " << type << " " << name << "  next: " << next << "  pointer: " << isPointer << std::endl;
            } else {
                throw InvalidSymbol(next, fileName, lineNumber, lineOffset);
            }
        }

    if(!isRecognized && !containsWhitespace(mainWord)) {

        //std::cout << InvalidSymbol(mainWord, fileName, lineNumber, lineOffset).what() << std::endl;
    }
}

void Compiler::nextSymbol(FILE* file, std::string& current, char& nextSymbol, int& lineNumber, int& lineOffset) {
    current = "";
    lineOffset++;
    char c = nextSymbol;
    nextSymbol = fgetc(file);

    // removes whitespace until the first character
    while(isWhitespace(c)) {
        if(c == '\n') {
            lineNumber ++;
            lineOffset = 0;
        }
        lineOffset++;
        c = nextSymbol;
        nextSymbol = fgetc(file);
    }

    // check if the file ends prematurely
    while(1) {
        // end word
        if(c == '/' && nextSymbol == '/') {
            // Removing single line comments: //
            while(nextSymbol != '\n') {
                lineOffset++;
                c = nextSymbol;
                nextSymbol = fgetc(file);
            }
            lineNumber++;
            lineOffset = 0;
        } else if(c == '/' && nextSymbol == '*') {
            // Removing double line comments: /* ... */
            while(!(c == '*' && nextSymbol == '/')) {
                if(c == '\n') {
                    lineNumber ++;
                }
                lineOffset++;
                c = nextSymbol;
                nextSymbol = fgetc(file);
            }
            lineOffset++;
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
        lineOffset++;
        c = nextSymbol;
        nextSymbol = fgetc(file);
    }
}




