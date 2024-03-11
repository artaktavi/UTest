cmake_minimum_required(VERSION 3.26)
project(UnitTesterTP)

set(CMAKE_CXX_STANDARD 17)

add_library(UnitTesterTP src/library.cpp
        src/library.hpp
        src/test.hpp
)
