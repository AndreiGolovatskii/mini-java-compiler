#pragma once

#include <filesystem>
#include <gtest/gtest.h>

#include "driver.hh"
#include "symbol_table_builder.hh"


class SymbolTableBuilder : public ::testing::Test {
public:
    TProgram* Parse(const std::filesystem::path& path) {
        Driver_.parse(path.string());
        return Driver_.Program_.get();
    }

protected:
    TDriver Driver_;
};


TEST_F(SymbolTableBuilder, Sample) {
    TProgram* program = Parse("./parse_tests/sample.java");

    TSymbolTableBuilder tableBuilder;
    program->Accept(&tableBuilder);

    auto& symbolTable = tableBuilder.SymbolTable();

    ASSERT_THROW(symbolTable.Class("NoClass"), std::logic_error);
    ASSERT_NO_THROW(symbolTable.Class("Factorial"));

    ASSERT_TRUE(symbolTable.Class("Factorial")->Method("main")->IsStatic());
    ASSERT_FALSE(symbolTable.Class("Fac")->Method("ComputeFac")->IsStatic());
}