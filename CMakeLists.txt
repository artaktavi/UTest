cmake_minimum_required(VERSION 3.10)
project(UTest VERSION 0.2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_DIRS src/asserts src/expects src/)
set(NLOHMANN_JSON_LIBRARY_SOURCE third_party/json.hpp)

add_library(UTestLibrary ${SOURCE_DIRS})
set_target_properties(UTestLibrary PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(UTestLibrary PUBLIC ${SOURCE_DIRS})

add_library(NlohmannJsonLibrary ${NLOHMANN_JSON_LIBRARY_SOURCE})
set_target_properties(NlohmannJsonLibrary PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(NlohmannJsonLibrary PUBLIC third_party/)

add_executable(debug tmp/main.cpp)

target_link_libraries(UTestLibrary NlohmannJsonLibrary)
target_link_libraries(debug UTestLibrary)
