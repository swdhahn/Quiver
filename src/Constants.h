//
// Created by Seth H. on 11/4/2021.
//

#ifndef QUIVER_CONSTANTS_H
#define QUIVER_CONSTANTS_H
#include <string>


// Language Specifics:

const std::string LanguageTypes[] = {"int", "int32", "int64", "float", "float32", "float64", "boolean", "char"};
const std::string LanguageModifiers[] = {"const", "static"};
const std::string LanguageSymbols = ":;'\"{}[]<>+-*/%=(),.";

#define LANGUAGE_TYPE_COUNT 8
#define LANGUAGE_MODIFIER_COUNT 2

/*
 * Simple program layout
 *
 * CLASS_CREATION SEPARATOR BEGIN SEPARATOR
 * VARIABLE_CREATION SEPARATOR
 * METHOD_BEGIN SEPARATOR
 * METHOD_BEGIN SEPARATOR
 * END
 *
 */

// ids are names for now
enum Language {
    SEPARATOR = -127, // - Separates values
    BEGIN = 26, // - begins class
    END, // - ends class

    CLASS_BEGIN, // CLASS_BEGIN class-id inherited-class-id variable-def ... func-def ... CLASS_END
    CLASS_END,
    METHOD_BEGIN, // method-id type PARAMS_BEGIN ... PARAMS_END
    METHOD_END, //
    PARAMS_BEGIN, // PARAMS_INDEX 0 type name PARAMS_INDEX 1 type name ... PARAMS_END
    PARAMS_INDEX,
    PARAMS_END,
    CONDITION_BEGIN, //
    CONDITION_END,
    METHOD_CALL, // method-id [params: variable-id] ...
    VARIABLE_CREATION, // variable-id type value
    VARIABLE_DESTRUCTION, // variable-id

};

bool isLanguageType(const std::string& type) {
    for(int i = 0; i < LANGUAGE_TYPE_COUNT; i++) {
        if(type == LanguageTypes[i]) {
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
    if(isLanguageModifier(name) || isLanguageType(name) || hasSymbol(name) || containsWhitespace(name)) {
        std::cerr << "Invalid name: " << name << std::endl;
        return false;
    }
    return true;
}



#endif //QUIVER_CONSTANTS_H
