project(Examples)

add_executable(example_1 example_1.cpp)
target_link_libraries(example_1 UTestLibrary)

add_executable(example_2 example_2.cpp)
target_link_libraries(example_2 UTestLibrary)
