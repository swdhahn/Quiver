cmake_minimum_required(VERSION 3.20)
project(Quiver)

set(CMAKE_CXX_STANDARD 23)


add_executable(${PROJECT_NAME} src/main.cpp src/Interpretor.cpp src/Interpretor.h src/Compiler.cpp src/Compiler.h src/Quiver.cpp src/Quiver.h src/Constants.h)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/quiv/Main.quiv
        ${CMAKE_CURRENT_BINARY_DIR}/quiv/Main.quiv)