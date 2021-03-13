cmake_minimum_required(VERSION 3.0)

enable_testing()
set(TEST_SOURCES test_main.cpp test_interpreter.cpp test_symbol_table.cpp)
add_executable(Tests ${TEST_SOURCES})
target_link_libraries(Tests Compiler)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(Tests ${GTEST_BOTH_LIBRARIES} ${GTEST_LIBRARIES} Threads::Threads)