cmake_minimum_required(VERSION 3.0)


add_library(SymbolTable INTERFACE)

target_include_directories(SymbolTable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

