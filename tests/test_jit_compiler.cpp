#include <gtest/gtest.h>

#include <filesystem>

#include "jit_compile.hh"


class JitCompile : public testing::TestWithParam<std::filesystem::path> {
public:
    static void RunAndExpect(const std::filesystem::path& path, Status expectedResult) {
        ASSERT_EQ(JitCompileAndRunInSubprocess(path), expectedResult);
    }
};

TEST_F(JitCompile, AssertionFalse) {
    RunAndExpect("compiler_tests/assertion_false.java", Status::Fail());
}

TEST_F(JitCompile, AssertionTrue) {
    RunAndExpect("compiler_tests/assertion_true.java", Status::Ok());
}

TEST_F(JitCompile, Empty) {
    RunAndExpect("compiler_tests/empty.java", Status::Ok());
}

TEST_F(JitCompile, Arithmetic) {
    RunAndExpect("compiler_tests/assertion_arithmetic.java", Status::Ok());
}

TEST_F(JitCompile, Fibonacci) {
    RunAndExpect("compiler_tests/fibonacci.java", Status::Ok());
}

TEST_F(JitCompile, Arrays) {
    RunAndExpect("compiler_tests/arrays.java", Status::Ok());
}

TEST_F(JitCompile, TimeLimit) {
    RunAndExpect("compiler_tests/time_limit.java", Status::Fail());
}

TEST_F(JitCompile, Classes) {
    RunAndExpect("compiler_tests/classes.java", Status::Ok());
}

TEST_F(JitCompile, Primary) {
    RunAndExpect("compiler_tests/primary_numbers.java", Status::Ok());
}

TEST_F(JitCompile, Shadowing) {
    RunAndExpect("compiler_tests/shadowing.java", Status::Ok());
}