//
// Created by Seth H. on 11/8/2021.
//

#ifndef QUIVER_EXCEPTIONS_H
#define QUIVER_EXCEPTIONS_H

#include <string>
#include <exception>
#include <iostream>

class BuildException : public std::exception {
public:
    BuildException(std::string fileName, int line, int lineOffset);
    BuildException(std::string fileName);
    virtual const char* what() const throw() {
        return m_error.c_str();
    }
private:
    std::string m_error;
};

class InvalidSymbol: public BuildException {
public:
    InvalidSymbol(std::string symbol, std::string fileName, int line, int lineOffset);
    virtual const char* what() const throw() {
        return m_error.c_str();
    }
private:
    std::string m_error;
};

class InvalidName: public BuildException {
public:
    InvalidName(std::string name, std::string fileName, int line, int lineOffset);
    InvalidName(std::string name, std::string type, std::string fileName, int line, int lineOffset);
    virtual const char* what() const throw() {
        return m_error.c_str();
    }
private:
    std::string m_error;
};

class InvalidAssignment: public BuildException {
public:
    InvalidAssignment(std::string currentType, std::string assignedType, std::string fileName, int line, int lineOffset);
    virtual const char* what() const throw() {
        return m_error.c_str();
    }
private:
    std::string m_error;
};

#endif //QUIVER_EXCEPTIONS_H
