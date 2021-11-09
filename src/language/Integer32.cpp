//
// Created by Seth H. on 11/8/2021.
//

#include "Integer32.h"

bool Integer32::isType(const std::string& type) const {
    if(type == "int" || type == "int32") {
        return true;
    }
    return false;
}

bool Integer32::canParseData(const std::string& value) const {
    try {
        std::stoi(value);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
