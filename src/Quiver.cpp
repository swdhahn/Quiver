//
// Created by Seth H. on 11/4/2021.
//

#include "Quiver.h"

Quiver::Quiver(const std::string& path) : m_path(path) {


}

Quiver::~Quiver() {
    for(int i = 0; i < LANGUAGE_VARIABLE_COUNT; i++) {
        delete LanguageVariables[i];
    }
}

void Quiver::compileQuivFile(const char* file) {

    Compiler c(m_path);
    c.compile(file);

}

void Quiver::executeQuivFile(const char* file) {

}
