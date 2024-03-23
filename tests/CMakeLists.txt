project(Tests)

add_executable(tests tests.cpp)
set(TESTS_SOURCE_DIRS assert_tests/)
target_include_directories(tests PUBLIC ${TESTS_SOURCE_DIRS})
target_link_libraries(tests UTestLibrary)
