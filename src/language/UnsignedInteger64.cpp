//
// Created by Seth H. on 11/8/2021.
//

#include "UnsignedInteger64.h"

bool UnsignedInteger64::isType(const std::string& type) const {
    if(type == "uint64") {
        return true;
    }
    return false;
}

bool UnsignedInteger64::canParseData(const std::string& value) const {
    try {
        std::stoull(value);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
