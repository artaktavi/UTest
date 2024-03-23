project(NlohmannJsonLibrary)

add_library(NlohmannJsonLibrary SHARED ${CMAKE_CURRENT_SOURCE_DIR}/json.hpp)
set_target_properties(NlohmannJsonLibrary PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(NlohmannJsonLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
