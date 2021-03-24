#include <gtest/gtest.h>

#include <filesystem>

#include "driver.hh"
#include "naive_interpreter.hh"
#include "template_visitor.hh"


void RunInterpreter(std::ostream& out, const std::filesystem::path& file) {
    TDriver driver;
    driver.parse(file);

    TNaiveInterpreter interpreter{out};
    driver.Program_->Accept(&interpreter);
}


TEST(NaiveInterpreter, ArithmeticAssertion) {
    std::ostringstream programOut;
    RunInterpreter(programOut, "./interpreter_tests/arithmetic.java");
}


TEST(NaiveInterpreter, AssertionWorks) {
    std::ostringstream programOut;
    EXPECT_THROW(RunInterpreter(programOut, "./interpreter_tests/assertion_works.java"), std::runtime_error);
}


TEST(NaiveInterpreter, Stdout) {
    std::ostringstream programOut;
    RunInterpreter(programOut, "./interpreter_tests/stdout.java");
    ASSERT_EQ(programOut.str(), "42\n-42\n");
}

TEST(NaiveInterpreter, Factorize) {
    std::ostringstream programOut;
    RunInterpreter(programOut, "./interpreter_tests/factorize.java");
    ASSERT_EQ(programOut.str(), "11\n29\n317\n");
}
