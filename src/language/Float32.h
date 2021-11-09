//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_FLOAT32_H
#define QUIVER_FLOAT32_H

#include "Variable.h"

class Float32 : public Variable {

    bool canParseData(const std::string& value) const;
    bool isType(const std::string& type) const;

};


#endif //QUIVER_FLOAT32_H
