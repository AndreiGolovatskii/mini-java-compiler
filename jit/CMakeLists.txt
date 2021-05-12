cmake_minimum_required(VERSION 3.10)

find_package(LLVM 11.0.0 REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})

add_library(JIT INTERFACE)

target_include_directories(JIT SYSTEM INTERFACE ${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs
        Core
        ExecutionEngine
        Interpreter
        MC
        MCJIT
        Support
        nativecodegen
        native
        )

target_include_directories(JIT SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(JIT INTERFACE ${llvm_libs})
target_link_libraries(JIT INTERFACE IRBuilder)
target_link_libraries(JIT INTERFACE Driver)