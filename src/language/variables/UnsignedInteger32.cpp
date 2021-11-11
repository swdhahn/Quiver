//
// Created by Seth H. on 11/8/2021.
//

#include "UnsignedInteger32.h"

bool UnsignedInteger32::isType(const std::string& type) const {
    if(type == "uint32") {
        return true;
    }
    return false;
}

bool UnsignedInteger32::canParseData(const std::string& value) const {
    try {
        std::stoul(value);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
