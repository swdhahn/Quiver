//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_UNSIGNEDINTEGER32_H
#define QUIVER_UNSIGNEDINTEGER32_H

#include "Variable.h"

class UnsignedInteger32 : public Variable {

    bool canParseData(const std::string& value) const;
    bool isType(const std::string& type) const;

};


#endif //QUIVER_UNSIGNEDINTEGER32_H
