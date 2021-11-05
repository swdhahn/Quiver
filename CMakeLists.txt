cmake_minimum_required(VERSION 3.20)
project(Quiver)

set(CMAKE_CXX_STANDARD 23)

add_executable(Quiver src/main.cpp src/Interpretor.cpp src/Interpretor.h src/Compiler.cpp src/Compiler.h)
