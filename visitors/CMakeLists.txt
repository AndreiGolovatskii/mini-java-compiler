cmake_minimum_required(VERSION 3.0)

SET(SOURCES i_visitor.hh yaml_visitor.hh naive_interpreter.hh)

add_library(Visitors INTERFACE)
target_include_directories(Visitors INTERFACE ${SOURCES})
#set_target_properties(Visitors PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(
        Visitors
        INTERFACE
        yaml-cpp  # This is the "target" exposed by
        # yaml-cpp's CMakeLists.txt file
)