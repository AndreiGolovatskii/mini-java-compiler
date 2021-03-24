#include <gtest/gtest.h>

#include "scope.hh"
#include "scope_table.hh"
#include "types.hh"


TEST(ScopeTable, BeginEnd) {
    TScopeTable table;

    table.BeginScope();
    ASSERT_THROW(table.Variable("x"), std::logic_error);
    table.AddVariable("x", std::make_unique<TIntegerType>());

    ASSERT_NO_THROW(table.Variable("x"));
    table.AddVariable("y", std::make_unique<TIntegerType>());
    ASSERT_NO_THROW(table.Variable("y"));

    table.BeginScope();
    table.AddVariable("x", std::make_unique<TIntegerType>());
    table.AddVariable("z", std::make_unique<TIntegerType>());
    ASSERT_NO_THROW(table.Variable("x"));

    table.EndScope();
    ASSERT_THROW(table.Variable("z"), std::logic_error);
    table.EndScope();
}