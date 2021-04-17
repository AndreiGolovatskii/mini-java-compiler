#include <filesystem>
#include <gtest/gtest.h>

#include "driver.hh"
#include "symbol_table_builder.hh"
#include "types_utils.hh"


class SymbolTableBuilder : public ::testing::Test {
public:
    void BuildSymbolTree(const std::filesystem::path& path) {
        TDriver driver;
        driver.parse(path.string());

        TSymbolTableBuilder builder;
        builder.Accept(driver.Program_.get());
        Table = std::move(builder.SymbolTable());
    }

    TSymbolTable Table;
};


TEST_F(SymbolTableBuilder, Sample) {
    BuildSymbolTree("./symbol_table_tests/sample.java");

    ASSERT_THROW((void) Table.Class("NoClass"), std::logic_error);
    ASSERT_NO_THROW((void) Table.Class("Factorial"));

    ASSERT_TRUE(Table.Class("Factorial")->Method("main")->IsStatic());
    ASSERT_FALSE(Table.Class("Fac")->Method("ComputeFac")->IsStatic());
}

TEST_F(SymbolTableBuilder, CyclicReference) {
    BuildSymbolTree("./symbol_table_tests/cyclic.java");

    ASSERT_EQ(ClassTypeSpec(Table.Class("A")->Variable("VarB")->Type()), Table.Class("B"));
    ASSERT_EQ(ClassTypeSpec(Table.Class("A")->Variable("VarA")->Type()), Table.Class("A"));

    ASSERT_EQ(ClassTypeSpec(Table.Class("B")->Variable("VarA")->Type()), Table.Class("A"));

    ASSERT_TRUE(IsEqual(Table.Class("A")->Variable("VarInt")->Type(), std::make_unique<TIntegerType>().get()));

    ASSERT_EQ(ClassTypeSpec(Table.Class("A")->Method("methodA")->ReturnType()), Table.Class("A"));
    ASSERT_EQ(ClassTypeSpec(Table.Class("A")->Method("methodB")->ReturnType()), Table.Class("B"));

    ASSERT_EQ(ClassTypeSpec(Table.Class("A")->Method("methodA")->Args()[0].Type()), Table.Class("A"));
    ASSERT_TRUE(Table.Class("A")->Method("methodB")->Args()[1].Name() == "argB");
}