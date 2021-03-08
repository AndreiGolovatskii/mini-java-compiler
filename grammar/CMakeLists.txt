cmake_minimum_required(VERSION 3.0)

find_package(BISON 3.5 REQUIRED)
BISON_TARGET(
        MyParser
        parser.y
        ${compiler_SOURCE_DIR}/grammar/parser.cpp
        DEFINES_FILE ${compiler_SOURCE_DIR}/grammar/parser.hh
)

find_package(FLEX 2.6 REQUIRED)
FLEX_TARGET(
        MyScanner
        scanner.l
        ${compiler_SOURCE_DIR}/grammar/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_library(
        LibGrammar
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)
