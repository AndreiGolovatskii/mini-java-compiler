cmake_minimum_required(VERSION 3.0)


add_library(ScopeTable INTERFACE)

target_include_directories(ScopeTable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ScopeTable INTERFACE AstComponents)
target_link_libraries(ScopeTable INTERFACE Types)

