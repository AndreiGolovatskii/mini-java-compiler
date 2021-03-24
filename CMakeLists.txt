cmake_minimum_required(VERSION 3.10)

add_subdirectory(third-party/yaml-cpp EXCLUDE_FROM_ALL)
add_subdirectory(third-party/googletest EXCLUDE_FROM_ALL)

project(compiler)


set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*,-warnings-as-errors=*)

set(CMAKE_CXX_STANDARD 20)
set(COMPILE_FLAGS -Wall -Wextra -pedantic -Werror)

add_subdirectory(driver)
add_subdirectory(ast_components)
add_subdirectory(visitors)
add_subdirectory(symbol_table)
add_subdirectory(scope_table)
add_subdirectory(types)


add_library(
        Compiler
        INTERFACE
)

target_link_libraries(Compiler INTERFACE Driver Visitors SymbolTable ScopeTable Types)

add_executable(
        CompilerExe
        main.cpp
)

target_link_libraries(CompilerExe Compiler)


enable_testing()
add_subdirectory(tests)