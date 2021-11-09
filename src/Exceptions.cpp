//
// Created by Seth H. on 11/8/2021.
//

#include "Exceptions.h"

#include <utility>

BuildException::BuildException(std::string fileName, int line, int lineOffset) {
    m_error = std::string("Build Exception[" + fileName + ":" + std::to_string(line) + ":" + std::to_string(lineOffset) + "] ").c_str();
}

InvalidSymbol::InvalidSymbol(std::string symbol, std::string fileName, int line, int lineOffset) : BuildException(std::move(fileName), line, lineOffset) {
    m_error = std::string(BuildException::what() + std::string(" Invalid Symbol: ") + symbol);
}

InvalidName::InvalidName(std::string name, std::string fileName, int line, int lineOffset) : BuildException(std::move(fileName), line, lineOffset) {
    m_error = std::string(BuildException::what() + std::string(" Invalid Name: ") + name);
}

InvalidName::InvalidName(std::string name, std::string type, std::string fileName, int line, int lineOffset) : BuildException(std::move(fileName), line, lineOffset) {
    m_error = std::string(BuildException::what() + std::string(" Invalid " + type + " Name: ") + name);
}

InvalidAssignment::InvalidAssignment(std::string currentType, std::string assignedType, std::string fileName, int line, int lineOffset) : BuildException(std::move(fileName), line, lineOffset) {
    m_error = std::string(BuildException::what() + std::string(" Invalid Assignment of " + assignedType + " to " + currentType));
}
