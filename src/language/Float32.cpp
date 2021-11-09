//
// Created by Seth H. on 11/8/2021.
//

#include "Float32.h"

bool Float32::isType(const std::string& type) const {
    if(type == "float" || type == "float32") {
        return true;
    }
    return false;
}

bool Float32::canParseData(const std::string& value) const {
    try {
        std::stof(value);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
