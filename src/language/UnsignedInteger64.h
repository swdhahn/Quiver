//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_UNSIGNEDINTEGER64_H
#define QUIVER_UNSIGNEDINTEGER64_H

#include "Variable.h"


class UnsignedInteger64 : public Variable {

    bool canParseData(const std::string& value) const;
    bool isType(const std::string& type) const;

};


#endif //QUIVER_UNSIGNEDINTEGER64_H
