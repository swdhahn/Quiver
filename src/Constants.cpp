//
// Created by Seth H. on 11/8/2021.
//

#include "Constants.h"

Variable* LanguageVariables[] = {new Boolean(), new Char(), new Float32(), new Float64(), new Integer32(), new Integer64(), new UnsignedInteger32(), new UnsignedInteger64()};

bool isLanguageType(const std::string& type) {
    for(int i = 0; i < LANGUAGE_VARIABLE_COUNT; i++) {
        if(LanguageVariables[i]->isType(type)) {
            return true;
        }
    }
    return false;
}

bool isLanguageModifier(const std::string& modifier) {
    for(int i = 0; i < LANGUAGE_MODIFIER_COUNT; i++) {
        if(modifier == LanguageModifiers[i]) {
            return true;
        }
    }
    return false;
}

bool isLanguageWord(const std::string& word) {
    for(int i = 0; i < LANGUAGE_WORD_COUNT; i++) {
        if(word == LanguageWords[i]) {
            return true;
        }
    }
    return false;
}

bool isWhitespace(const char& c) {
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
}

bool hasSymbol(const std::string& name) {
    for(int i = 0; i < name.length(); i++) {
        if(LanguageSymbols.find(name[i]) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool isSymbol(const char& c) {
    if(LanguageSymbols.find(c) != std::string::npos) {
        return true;
    }

    return false;
}

bool containsWhitespace(const std::string& name) {
    for(int i = 0; i < name.length(); i++) {
        if(isWhitespace(name[i])) {
            return true;
        }
    }
    return false;
}

bool isValidName(const std::string& name) {
    if(isLanguageModifier(name) || isLanguageWord(name) || isLanguageType(name) || hasSymbol(name) || containsWhitespace(name)) {
        return false;
    }
    return true;
}

const Variable* getVariableFromType(const std::string& type) {
    for(int i = 0; i < LANGUAGE_VARIABLE_COUNT; i++) {
        if(LanguageVariables[i]->isType(type)) {
            return LanguageVariables[i];
        }
    }
    std::cerr << "Something went terribly wrong, variable with type " << type << " does not exist." << std::endl;
    throw std::exception();
}
