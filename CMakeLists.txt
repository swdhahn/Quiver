cmake_minimum_required(VERSION 3.20)
project(Quiver)

set(CMAKE_CXX_STANDARD 23)



add_executable(${PROJECT_NAME} src/main.cpp src/Interpretor.cpp src/Interpretor.h src/Compiler.cpp src/Compiler.h src/Quiver.cpp src/Quiver.h src/Constants.h src/Constants.cpp src/Exceptions.h src/Exceptions.cpp src/language/variables/Float32.cpp src/language/variables/Float32.h src/language/variables/Integer32.cpp src/language/variables/Integer32.h src/language/variables/Float64.cpp src/language/variables/Float64.h src/language/variables/Integer64.cpp src/language/variables/Integer64.h src/language/variables/Boolean.cpp src/language/variables/Boolean.h src/language/variables/Char.cpp src/language/variables/Char.h src/language/variables/Variable.cpp src/language/variables/Variable.h src/language/variables/UnsignedInteger32.cpp src/language/variables/UnsignedInteger32.h src/language/variables/UnsignedInteger64.cpp src/language/variables/UnsignedInteger64.h)

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