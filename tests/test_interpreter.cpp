#include <gtest/gtest.h>

#include <filesystem>
#include <strstream>

#include "driver.hh"
#include "naive_interpreter.hh"


int RunInterpreter(std::ostream& out, const std::filesystem::path& file) {
    TDriver driver;
    driver.parse(file);

    TNaiveInterpreter interpreter{out};
    driver.Program_->Accept(&interpreter);
    return interpreter.ExitCode();
}


TEST(NaiveInterpreter, ArithmeticAssertion) {
    std::ostringstream programOut;
    int exitCode = RunInterpreter(programOut, "./interpreter_tests/arithmetic.java");
    ASSERT_EQ(exitCode, 0);
}


TEST(NaiveInterpreter, AssertionWorks) {
    std::ostringstream programOut;
    EXPECT_THROW(RunInterpreter(programOut, "./interpreter_tests/assertion_works.java"), std::runtime_error);
}


TEST(NaiveInterpreter, Stdout) {
    std::ostringstream programOut;
    int exitCode = RunInterpreter(programOut, "./interpreter_tests/stdout.java");
    ASSERT_EQ(exitCode, 0);
    ASSERT_EQ(programOut.str(), "42\n-42\n");
}

TEST(NaiveInterpreter, Factorize) {
    std::ostringstream programOut;
    int exitCode = RunInterpreter(programOut, "./interpreter_tests/factorize.java");
    ASSERT_EQ(exitCode, 0);
    ASSERT_EQ(programOut.str(), "11\n29\n317\n");
}
