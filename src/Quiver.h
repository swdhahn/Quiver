//
// Created by Seth H. on 11/4/2021.
//

#ifndef QUIVER_QUIVER_H
#define QUIVER_QUIVER_H

#include "Compiler.h"

class Quiver {
public:
    Quiver(const std::string& path);
    ~Quiver();

    void compileQuivFile(const char* file);
    void executeQuivFile(const char* file);

private:
    const std::string& m_path;
};


#endif //QUIVER_QUIVER_H
