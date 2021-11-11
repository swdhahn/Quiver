//
// Created by Seth H. on 11/8/2021.
//

#include "Boolean.h"

bool Boolean::isType(const std::string& type) const {
    if(type == "boolean") {
        return true;
    }
    return false;
}

bool Boolean::canParseData(const std::string& value) const {
    if(value == "null" || value == "true" || value == "false" || value.substr(0, 1) == "\"" && (value.find_last_of('\"') != std::string::npos && value.find_last_of('\"') > 0)) {
        return true;
    }
    try {
        std::stof(value);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
