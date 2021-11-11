//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_INTEGER32_H
#define QUIVER_INTEGER32_H

#include "Variable.h"

class Integer32 : public Variable {

    bool canParseData(const std::string& value) const;
    bool isType(const std::string& type) const;

};


#endif //QUIVER_INTEGER32_H
