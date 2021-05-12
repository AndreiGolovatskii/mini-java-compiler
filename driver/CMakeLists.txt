cmake_minimum_required(VERSION 3.10)


find_package(BISON 3.5 REQUIRED)
BISON_TARGET(
        Parser
        parser.y
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
        DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/parser.hh
)

find_package(FLEX 2.6 REQUIRED)
FLEX_TARGET(
        Scanner
        scanner.l
        ${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_library(
        Driver
        driver.cpp
        driver.hh
        scanner.hh
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)

set_target_properties(
        Driver
        PROPERTIES
        CXX_CLANG_TIDY ""
        COMPILE_FLAGS ""
)


target_include_directories(Driver SYSTEM PUBLIC ${FLEX_INCLUDE_DIRS})
target_link_libraries(Driver PUBLIC AstComponents)
target_include_directories(Driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})