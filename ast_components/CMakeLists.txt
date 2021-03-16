cmake_minimum_required(VERSION 3.10)

add_library(AstComponents INTERFACE)
target_include_directories(AstComponents INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AstComponents INTERFACE Visitors)