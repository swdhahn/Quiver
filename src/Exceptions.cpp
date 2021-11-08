//
// Created by Seth H. on 11/8/2021.
//

#include "Exceptions.h"

#include <utility>

BuildException::BuildException(std::string fileName, int line) {
    m_error = std::string("Build Exception[" + fileName + ":" + std::to_string(line) + "] ").c_str();
}

InvalidSymbol::InvalidSymbol(std::string symbol, std::string fileName, int line) : BuildException(std::move(fileName), line) {
    m_error = std::string(BuildException::what() + std::string(" Invalid Symbol: ") + symbol);
}

InvalidName::InvalidName(std::string name, std::string fileName, int line) : BuildException(std::move(fileName), line) {
    m_error = std::string(BuildException::what() + std::string(" Invalid Name: ") + name);
}

InvalidName::InvalidName(std::string name, std::string type, std::string fileName, int line) : BuildException(std::move(fileName), line) {
    m_error = std::string(BuildException::what() + std::string(" Invalid " + type + " Name: ") + name);
}
