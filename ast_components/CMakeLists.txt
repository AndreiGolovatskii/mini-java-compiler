cmake_minimum_required(VERSION 3.0)

SET(SOURCES ${SOURCES} ast_components.hh)

add_library(LibASTComponents ${SOURCES})
set_target_properties(LibASTComponents PROPERTIES LINKER_LANGUAGE CXX)