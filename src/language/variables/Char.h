//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_CHAR_H
#define QUIVER_CHAR_H

#include "Variable.h"

class Char : public Variable {

    bool canParseData(const std::string& value) const;
    bool isType(const std::string& type) const;

};


#endif //QUIVER_CHAR_H
