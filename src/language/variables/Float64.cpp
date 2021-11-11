//
// Created by Seth H. on 11/8/2021.
//

#include "Float64.h"

bool Float64::isType(const std::string& type) const {
    if(type == "float64") {
        return true;
    }
    return false;
}

bool Float64::canParseData(const std::string& value) const {
    try {
        std::stod(value);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
