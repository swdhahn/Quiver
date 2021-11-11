//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_INTEGER64_H
#define QUIVER_INTEGER64_H

#include "Variable.h"

class Integer64 : public Variable {

    bool canParseData(const std::string& value) const;
    bool isType(const std::string& type) const;

};


#endif //QUIVER_INTEGER64_H
