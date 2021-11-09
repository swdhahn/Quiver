//
// Created by Seth H. on 11/8/2021.
//

#include "Integer64.h"

bool Integer64::isType(const std::string& type) const {
    if(type == "int64") {
        return true;
    }
    return false;
}

bool Integer64::canParseData(const std::string& value) const {
    try {
        std::stol(value);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
