//
// Created by Seth H. on 11/8/2021.
//

#include "Char.h"

bool Char::isType(const std::string& type) const {
    if(type == "char") {
        return true;
    }
    return false;
}

bool Char::canParseData(const std::string& value) const {
    if(value.length() == 1) {
        return true;
    }
    if(value.length() <= 3 && value.substr(0, 1) == "\'" && value.substr(2, 3) == "\'") {
        return true;
    }
    return false;
}
