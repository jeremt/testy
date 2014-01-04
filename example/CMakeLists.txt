cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++0x")
include_directories(..)
add_executable(test test.cpp Calculator.cpp)
