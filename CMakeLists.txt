cmake_minimum_required(VERSION 3.0)

add_subdirectory(third-party/yaml-cpp EXCLUDE_FROM_ALL)

project(compiler)


set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*,-warnings-as-errors=*)

set(CMAKE_CXX_STANDARD 20)
set(COMPILE_FLAGS -Wall -Wextra -pedantic -Werror)

include_directories(driver grammar ast_components visitors)

add_subdirectory(grammar)
add_subdirectory(driver)
add_subdirectory(ast_components)
add_subdirectory(visitors)


add_library(
        LibCompiler
        INTERFACE
)

target_link_libraries(LibCompiler INTERFACE LibDriver LibGrammar Visitors)

add_executable(
        Compiler
        main.cpp
        ${HEADERS}
)

target_link_libraries(Compiler LibCompiler)

enable_testing()
set(TEST_SOURCES ${compiler_SOURCE_DIR}/tests/test_main.cpp)
add_executable(Tests ${TEST_SOURCES})
target_include_directories(Tests PRIVATE ${compiler_SOURCE_DIR})
target_link_libraries(Tests LibCompiler)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(Tests ${GTEST_BOTH_LIBRARIES} ${GTEST_LIBRARIES} Threads::Threads)