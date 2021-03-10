cmake_minimum_required(VERSION 3.0)

add_library(Visitors INTERFACE)
#set_target_properties(Visitors PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(
        Visitors
        INTERFACE
        yaml-cpp  # This is the "target" exposed by
        # yaml-cpp's CMakeLists.txt file
)