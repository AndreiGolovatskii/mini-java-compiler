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

# NOTE: Resetting a global CMAKE_CXX_CLANG_TIDY and COMPILE_OPTIONS
set_target_properties(
        LibGrammar
        PROPERTIES
        CXX_CLANG_TIDY ""
        COMPILE_FLAGS ""
)


target_include_directories(LibGrammar PUBLIC ${FLEX_INCLUDE_DIRS})
