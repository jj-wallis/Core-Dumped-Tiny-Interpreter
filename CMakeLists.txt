cmake_minimum_required(VERSION 3.10)
project(TinyInterpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tiny_interpreter main.cpp lexer.cpp expression.cpp parser.cpp)
