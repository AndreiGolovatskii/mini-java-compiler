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

    TSymbolTable<> Table;
};


TEST_F(SymbolTableBuilder, Sample) {
    BuildSymbolTree("./symbol_table_tests/sample.java");

    ASSERT_THROW((void) Table.Get("NoClass"), std::logic_error);
    ASSERT_NO_THROW((void) Table.Get("Factorial"));

    ASSERT_TRUE(Table.Get("Factorial")->Method("main")->IsStatic());
    ASSERT_FALSE(Table.Get("Fac")->Method("ComputeFac")->IsStatic());
}

TEST_F(SymbolTableBuilder, CyclicReference) {
    BuildSymbolTree("./symbol_table_tests/cyclic.java");

    ASSERT_EQ(ClassTypeSpec(Table.Get("A")->Variable("VarB")->Type()), Table.Get("B").get());
    ASSERT_EQ(ClassTypeSpec(Table.Get("A")->Variable("VarA")->Type()), Table.Get("A").get());

    ASSERT_EQ(ClassTypeSpec(Table.Get("B")->Variable("VarA")->Type()), Table.Get("A").get());

    ASSERT_TRUE(IsEqual(Table.Get("A")->Variable("VarInt")->Type(), std::make_unique<TIntegerType>().get()));

    ASSERT_EQ(ClassTypeSpec(Table.Get("A")->Method("methodA")->ReturnType()), Table.Get("A").get());
    ASSERT_EQ(ClassTypeSpec(Table.Get("A")->Method("methodB")->ReturnType()), Table.Get("B").get());

    ASSERT_EQ(ClassTypeSpec(Table.Get("A")->Method("methodA")->Args()[0].Type()), Table.Get("A").get());
    ASSERT_TRUE(Table.Get("A")->Method("methodB")->Args()[1].Name() == "argB");
}