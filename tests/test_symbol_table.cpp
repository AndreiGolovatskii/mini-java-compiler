#include <gtest/gtest.h>

#include "symbol_table.hh"
#include "types.hh"

TEST(SymbolTable, Add) {
    TSymbolTable table;

    table.Add("MainClass", std::make_unique<TClassSpecification>());
    ASSERT_THROW(table.Add("MainClass"), std::logic_error);
    ASSERT_THROW(table.Add("MainClass"), std::logic_error);
    ASSERT_THROW((void) table.Get("NoSuchClass"), std::logic_error);

    table.Get("MainClass")->AddVariable("x", std::make_unique<TIntegerType>());
    ASSERT_THROW(table.Get("MainClass")->AddVariable("x", std::make_unique<TIntegerType>()), std::logic_error);
    table.Get("MainClass")->AddVariable("self", std::make_unique<TClassPtrType>(table.Get("MainClass").get()));

    ASSERT_EQ(table.Get("MainClass")->Variable("self")->IsStatic(), false);
}