project(UTestLibrary)

set(SOURCE_DIRS asserts/ expects/ ./)

add_library(UTestLibrary SHARED TestDefine.hpp)
set_target_properties(UTestLibrary PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(UTestLibrary PUBLIC ${SOURCE_DIRS})

target_link_libraries(UTestLibrary NlohmannJsonLibrary)
