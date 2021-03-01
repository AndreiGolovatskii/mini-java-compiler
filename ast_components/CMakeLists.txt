cmake_minimum_required(VERSION 3.0)

SET(SOURCES class_declaration.hh method_declaration.hh variable_declaration.hh)
SET(SOURCES ${SOURCES} statement.hh expression.hh declaration.hh program.hh type.hh)
SET(SOURCES ${SOURCES} lvalue.hh invocation.hh expression_base.hh)

add_library(LibASTComponents ${SOURCES})
set_target_properties(LibASTComponents PROPERTIES LINKER_LANGUAGE CXX)