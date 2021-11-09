//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_BOOLEAN_H
#define QUIVER_BOOLEAN_H

#include "Variable.h"

class Boolean : public Variable {

    bool canParseData(const std::string& value) const;
    bool isType(const std::string& type) const;

};


#endif //QUIVER_BOOLEAN_H
