cmake_minimum_required(VERSION 3.16)
project(eCompiler)

set(CMAKE_CXX_STANDARD 14)

file(GLOB INCLUDE_FILES
    "include/*.hpp"
)

file(GLOB SRC_FILES
    "src/*.cpp"
)

include_directories(${INCLUDE_DIRECTORIES})

add_executable(eCompiler ${SRC_FILES})