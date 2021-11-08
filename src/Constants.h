//
// Created by Seth H. on 11/4/2021.
//

#ifndef QUIVER_CONSTANTS_H
#define QUIVER_CONSTANTS_H
#include <string>
#include <iostream>
#include "Exceptions.h"


// Language Specifics:

const std::string LanguageWords[] = {"class", "new", "delete", "throw", "#"};
const std::string LanguageTypes[] = {"int", "int32", "int64", "uint", "uint32", "uint64", "float", "float32", "float64", "boolean", "char"};
const std::string LanguageModifiers[] = {"const", "static", "public", "private", "protected"};
const std::string LanguageSymbols = ":;'\"{}[]<>+-*/%=(),.";

#define LANGUAGE_TYPE_COUNT 11
#define LANGUAGE_MODIFIER_COUNT 5
#define LANGUAGE_WORD_COUNT 5

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

bool isLanguageType(const std::string& type);

bool isLanguageModifier(const std::string& modifier);

bool isLanguageWord(const std::string& word);

bool isWhitespace(const char& c);

bool hasSymbol(const std::string& name);

bool isSymbol(const char& c);

bool containsWhitespace(const std::string& name);

bool isValidName(const std::string& name);



#endif //QUIVER_CONSTANTS_H
