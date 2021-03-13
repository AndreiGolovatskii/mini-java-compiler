cmake_minimum_required(VERSION 3.0)


if (${APPLE})
    set(ENV{CMAKE_INCLUDE_PATH} "/usr/local/opt/flex/include:ENV{CMAKE_INCLUDE_PATH}")
    set(ENV{CMAKE_LIBRARY_PATH} "/usr/local/opt/flex/lib;/usr/local/opt/bison/lib:ENV{CMAKE_LIBRARY_PATH}")
    set(ENV{PATH} "/usr/local/opt/flex/bin:/usr/local/opt/bison/bin:ENV{PATH}")
endif ()

find_package(BISON 3.5 REQUIRED)
BISON_TARGET(
        MyParser
        parser.y
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
        DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/parser.hh
)

find_package(FLEX 2.6 REQUIRED)
FLEX_TARGET(
        MyScanner
        scanner.l
        ${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_library(
        Grammar
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)

set_target_properties(
        Grammar
        PROPERTIES
        CXX_CLANG_TIDY ""
        COMPILE_FLAGS ""
)


target_include_directories(Grammar SYSTEM PUBLIC ${FLEX_INCLUDE_DIRS})
target_include_directories(Grammar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Grammar PUBLIC AstComponents)
target_link_libraries(Grammar PUBLIC Driver)