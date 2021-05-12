cmake_minimum_required(VERSION 3.10)


find_package(LLVM 12.0.0 REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})

add_library(IRBuilder INTERFACE)
target_include_directories(IRBuilder INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(IRBuilder INTERFACE ${LLVM_INCLUDE_DIRS})

llvm_map_components_to_libnames(llvm_libs
        Core
        Support
        core
        support)

target_link_libraries(IRBuilder INTERFACE ${llvm_libs})
target_link_libraries(IRBuilder INTERFACE Visitors)
target_link_libraries(IRBuilder INTERFACE SymbolTable)
