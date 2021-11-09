cmake_minimum_required(VERSION 3.20)
project(Quiver)

set(CMAKE_CXX_STANDARD 23)



add_executable(${PROJECT_NAME} src/main.cpp src/Interpretor.cpp src/Interpretor.h src/Compiler.cpp src/Compiler.h src/Quiver.cpp src/Quiver.h src/Constants.h src/Constants.cpp src/Exceptions.h src/Exceptions.cpp src/language/Float32.cpp src/language/Float32.h src/language/Integer32.cpp src/language/Integer32.h src/language/Float64.cpp src/language/Float64.h src/language/Integer64.cpp src/language/Integer64.h src/language/Boolean.cpp src/language/Boolean.h src/language/Char.cpp src/language/Char.h src/language/Variable.cpp src/language/Variable.h src/language/UnsignedInteger32.cpp src/language/UnsignedInteger32.h src/language/UnsignedInteger64.cpp src/language/UnsignedInteger64.h)

target_compile_options(${PROJECT_NAME} PRIVATE -lstdc++fs)


#add_custom_command(
#        TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${CMAKE_SOURCE_DIR}/quiv/Main.quiv
#        ${CMAKE_CURRENT_BINARY_DIR}/quiv/Main.quiv)

add_custom_target(copy_res_directory ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/quiv" "${CMAKE_BINARY_DIR}/quiv"
        COMMENT "Copy quiv directory to build tree"
        VERBATIM)