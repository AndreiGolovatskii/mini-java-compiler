cmake_minimum_required(VERSION 3.0)

add_library(Driver driver.cpp driver.hh)
target_link_libraries(Driver PUBLIC Grammar)
target_include_directories(Driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})