cmake_minimum_required(VERSION 3.10)


add_library(Types INTERFACE)
target_include_directories(Types INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Types INTERFACE AstComponents)
