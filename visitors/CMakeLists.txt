cmake_minimum_required(VERSION 3.10)


add_library(Visitors INTERFACE)
target_include_directories(Visitors INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Visitors INTERFACE Types)
target_link_libraries(Visitors INTERFACE SymbolTable)
target_link_libraries(
        Visitors
        INTERFACE
        yaml-cpp  # This is the "target" exposed by
        # yaml-cpp's CMakeLists.txt file
)