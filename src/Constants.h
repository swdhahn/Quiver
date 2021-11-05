//
// Created by Seth H. on 11/4/2021.
//

#ifndef QUIVER_CONSTANTS_H
#define QUIVER_CONSTANTS_H
#include <string>


// Language Specifics:

enum Language {
    SEPARATOR, // - Separates values
    BEGIN, // - begins class
    END, // - ends class

    CLASS_CREATION, // class-id inherited-class-id variable-def ... func-def ...
    CLASS_DESTRUCTION, // class-id
    METHOD_BEGIN, // method-id
    METHOD_END, //
    METHOD_CALL, // method-id [params: variable-id] ...
    VARIABLE_CREATION, // variable-id type value
    VARIABLE_DESTRUCTION, // variable-id

};

const std::string LanguageTypes[] = {"int", "int32", "int64", "float", "float32", "float64", "boolean", "char"};
const std::string LanguageModifiers[] = {"const", "static"};

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

#endif //QUIVER_CONSTANTS_H
