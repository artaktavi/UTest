cmake_minimum_required(VERSION 3.10)
project(UTest VERSION 0.2.1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(SINGLE_INCLUDE "${PROJECT_SOURCE_DIR}/single-include/UTest")
set(THIRD_PARTY_DIR "${PROJECT_SOURCE_DIR}/third_party")
set(EXAMPLES_DIR "${PROJECT_SOURCE_DIR}/examples")
set(TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")
set(DEBUG_DIR "${PROJECT_SOURCE_DIR}/debug")
set(TOOLS_DIR "${PROJECT_SOURCE_DIR}/tools")

add_subdirectory(${THIRD_PARTY_DIR})
add_subdirectory(${SOURCE_DIR})

option(BUILD_TESTS "Building tests for UTest" OFF)
option(BUILD_DEBUG "Building debug main.cpp" OFF)
option(BUILD_EXAMPLES "Building examples" OFF)

find_package(Python COMPONENTS Interpreter REQUIRED)

set(FILE_INCLUDER_SCRIPT "${TOOLS_DIR}/FileIncluder.py")
set(INCLUDE_TEMPLATES_DIR "${SOURCE_DIR}/generate_include_templates/")
set(SINGLE_INCLUDE_TEMPLATE_PATH "${INCLUDE_TEMPLATES_DIR}/SingleInclude.hpp")
set(SINGLE_INCLUDE_OUTFILE_PATH "${SINGLE_INCLUDE}/UTest.hpp")
set(SINGLE_INCLUDE_SOURCES ${SOURCE_DIR} ${THIRD_PARTY_DIR})

add_custom_target(generate_single_include ALL)
add_custom_command(TARGET generate_single_include POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SINGLE_INCLUDE}
        COMMAND Python::Interpreter ${FILE_INCLUDER_SCRIPT} ${SINGLE_INCLUDE_TEMPLATE_PATH} ${SINGLE_INCLUDE_OUTFILE_PATH} ${SINGLE_INCLUDE_SOURCES}
        COMMENT "generating single-include file..."
)


if (BUILD_EXAMPLES)
    add_subdirectory(${EXAMPLES_DIR})
endif ()

if (BUILD_TESTS)
    add_subdirectory(${TESTS_DIR})
endif ()

if (BUILD_DEBUG)
    add_subdirectory(${DEBUG_DIR})
endif ()
