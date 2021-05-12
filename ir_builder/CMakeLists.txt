cmake_minimum_required(VERSION 3.10)


find_package(LLVM 11.0.0 REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})

add_library(IRBuilder INTERFACE)

target_include_directories(IRBuilder SYSTEM INTERFACE ${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs
        Core
        Support
        core
        support)

target_include_directories(IRBuilder SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(IRBuilder INTERFACE Visitors)
target_link_libraries(IRBuilder INTERFACE SymbolTable)
target_link_libraries(IRBuilder INTERFACE ${llvm_libs})
