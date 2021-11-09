#include <iostream>
#include "Quiver.h"



int main(int argc, char* argv[]) {

    std::string path = argv[0]; // gets current directory & exe file
    int pos;
    if((pos = path.find_last_of("\\")) == std::string::npos) {
        pos = path.find_last_of("/");
    }
    path = path.substr(0, pos + 1);
    // Current path is stored in path variable now

    Quiver quiv(path);

    quiv.compileQuivFile("quiv/Main.quiv");

	return 0;
}

/**
 *
 * Function calls
 *
 * class instancing
 *
 * NEED TO ADD MODIFIER & POINTER to params in compiler
 *
 * VARIABLES CAN ONLY HANDLE SINGLE VALUE - no mult or operators on variables - maybe i build that into the actual language with the language
 *
 */
