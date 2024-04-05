cmake_minimum_required(VERSION 3.10)
project(UTest VERSION 0.2.1)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(third_party)
add_subdirectory(src)

option(BUILD_TESTS "Building tests for UTest" OFF)
option(BUILD_DEBUG "Building debug main.cpp" OFF)
option(BUILD_EXAMPLES "Building examples" OFF)

if (BUILD_EXAMPLES)
    add_subdirectory(examples/)
endif()

if (BUILD_TESTS)
    add_subdirectory(tests/)
endif()

if (BUILD_DEBUG)
    add_subdirectory(debug/)
endif()
