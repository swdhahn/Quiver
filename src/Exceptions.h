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
    BuildException(std::string fileName, int line);
    virtual const char* what() const throw() {
        return m_error.c_str();
    }
private:
    std::string m_error;
};

class InvalidSymbol: public BuildException {
public:
    InvalidSymbol(std::string symbol, std::string fileName, int line);
    virtual const char* what() const throw() {
        return m_error.c_str();
    }
private:
    std::string m_error;
};

class InvalidName: public BuildException {
public:
    InvalidName(std::string name, std::string fileName, int line);
    InvalidName(std::string name, std::string type, std::string fileName, int line);
    virtual const char* what() const throw() {
        return m_error.c_str();
    }
private:
    std::string m_error;
};

#endif //QUIVER_EXCEPTIONS_H
