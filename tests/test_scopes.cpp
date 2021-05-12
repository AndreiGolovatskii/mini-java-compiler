#include <gtest/gtest.h>

#include "scope_table.hh"
#include "types.hh"


TEST(ScopeTable, BeginEnd) {
    TScopeTable table;

    table.BeginScope();
    ASSERT_THROW((void) table.Variable("x"), std::logic_error);
    table.AddVariable("x", std::make_unique<TVariableSpecification>(std::make_unique<TIntegerType>(), false));

    ASSERT_THROW(
            table.AddVariable("x", std::make_unique<TVariableSpecification>(std::make_unique<TIntegerType>(), false)),
            std::logic_error);

    ASSERT_NO_THROW((void) table.Variable("x"));
    table.AddVariable("y", std::make_unique<TVariableSpecification>(std::make_unique<TIntegerType>(), false));
    ASSERT_NO_THROW((void) table.Variable("y"));


    table.BeginScope();
    table.AddVariable(
            "x", std::make_unique<TVariableSpecification>(std::make_unique<TIntegerType>(), false));// shadow x variable
    table.AddVariable("z", std::make_unique<TVariableSpecification>(std::make_unique<TIntegerType>(), false));
    ASSERT_NO_THROW((void) table.Variable("x"));

    table.EndScope();
    ASSERT_THROW((void) table.Variable("z"), std::logic_error);
    table.EndScope();
}