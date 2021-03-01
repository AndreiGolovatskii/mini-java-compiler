cmake_minimum_required(VERSION 3.0)

add_library(LibDriver driver.cpp driver.hh)
target_link_libraries(LibDriver LibGrammar)
