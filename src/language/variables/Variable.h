//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_VARIABLE_H
#define QUIVER_VARIABLE_H

#include <string>



class Variable {
public:



    virtual bool canParseData(const std::string& value) const = 0;
    virtual bool isType(const std::string& type) const = 0;
};


#endif //QUIVER_VARIABLE_H
