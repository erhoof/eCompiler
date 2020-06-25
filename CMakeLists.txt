cmake_minimum_required(VERSION 3.16)
project(eCompiler)

set(CMAKE_CXX_STANDARD 14)

file(GLOB INCLUDE_FILES
    "include/Core/*.h"
    "src/Interpreter/*.h"
    "src/Interpreter/Constructions/*.h"
    "include/IO/*.h"
    "include/Lexer/*.h"
    "src/SymbolTable/*.h"
    "include/*.hpp"
)

file(GLOB SRC_FILES
    "src/Core/*.cpp"
    "src/Interpreter/*.cpp"
    "src/Interpreter/Constructions/*.cpp"
    "src/IO/*.cpp"
    "src/Lexer/*.cpp"
    "src/SymbolTable/*.cpp"
    "src/*.cpp"
)

include_directories(${INCLUDE_DIRECTORIES})

add_executable(eCompiler ${SRC_FILES} include/Interpreter/Constructions/Statement.h src/Interpreter/Constructions/Statement.cpp include/Interpreter/Constructions/If.h src/Interpreter/Constructions/If.cpp)