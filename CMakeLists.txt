cmake_minimum_required(VERSION 3.10)
project(UTest VERSION 0.2.0)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_DIRS src/asserts src/expects src/ single-include/)
set(NLOHMANN_JSON_LIBRARY_SOURCE_DIR third_party/)

add_library(UTestLibrary single-include/UTest.hpp)
set_target_properties(UTestLibrary PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(UTestLibrary PUBLIC ${SOURCE_DIRS})

add_library(NlohmannJsonLibrary ${NLOHMANN_JSON_LIBRARY_SOURCE_DIR}/json.hpp)
set_target_properties(NlohmannJsonLibrary PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(NlohmannJsonLibrary PUBLIC ${NLOHMANN_JSON_LIBRARY_SOURCE_DIR})

target_link_libraries(UTestLibrary NlohmannJsonLibrary)

option(BUILD_TESTS "Running tests for UTest" OFF)
option(BUILD_DEBUG "Running debug main.cpp" OFF)

if (BUILD_TESTS)
    add_executable(tests tests/tests.cpp)
    set(TESTS_SOURCE_DIRS tests/ tests/assert_tests/)
    target_include_directories(tests PUBLIC ${TESTS_SOURCE_DIRS})
    target_link_libraries(tests UTestLibrary)
endif()

if (BUILD_DEBUG)
    add_executable(debug tmp/main.cpp)
    target_link_libraries(debug UTestLibrary)
endif()
