cmake_minimum_required(VERSION 3.16)
project(eCompiler)

set(CMAKE_CXX_STANDARD 14)

file(GLOB INCLUDE_FILES
    "include/Core/*.h"
    "src/Interpreter/*.h"
    "include/IO/*.h"
    "include/Lexer/*.h"
    "src/SymbolTable/*.h"
    "include/*.hpp"
)

file(GLOB SRC_FILES
    "src/Core/*.cpp"
    "src/Interpreter/*.cpp"
    "src/IO/*.cpp"
    "src/Lexer/*.cpp"
    "src/SymbolTable/*.cpp"
    "src/*.cpp"
)

include_directories(${INCLUDE_DIRECTORIES})

add_executable(eCompiler ${SRC_FILES} include/IO/Logger.h src/IO/Logger.cpp include/Core/Core.h src/Core/Core.cpp include/Interpreter/Arithmetic.h src/Interpreter/Arithmetic.cpp include/Interpreter/Unary.h src/Interpreter/Unary.cpp)