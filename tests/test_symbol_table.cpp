#include <gtest/gtest.h>

#include "symbol_table.hh"
#include "types.hh"

TEST(SymbolTable, Add) {
    TSymbolTable table;

    table.AddClass("MainClass");
    ASSERT_THROW(table.AddClass("MainClass"), std::logic_error);
    ASSERT_THROW(table.AddClass("MainClass"), std::logic_error);
    ASSERT_THROW((void)table.Class("NoSuchClass"), std::logic_error);

    table.Class("MainClass")->AddVariable("x", std::make_unique<TIntegerType>());
    ASSERT_THROW(table.Class("MainClass")->AddVariable("x", std::make_unique<TIntegerType>()), std::logic_error);
    table.Class("MainClass")->AddVariable("self", std::make_unique<TClassPtrType>(table.Class("MainClass")));

    ASSERT_EQ(table.Class("MainClass")->Variable("self")->IsStatic(), false);
}