cmake_minimum_required(VERSION 3.26)
project(cs-105-ch4a-curtis-et-al)

set(CMAKE_CXX_STANDARD 17)
add_executable(tokki main.cpp
        Lexer.cpp
        Lexer.h
        Parser.cpp
        Parser.h)

