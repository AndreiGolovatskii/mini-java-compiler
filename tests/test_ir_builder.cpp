#include <gtest/gtest.h>

#include <memory>

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Support/raw_ostream.h"


#include "driver.hh"
#include "program_builder.hh"
#include "test_utils.hh"

class IrBuilderTest : public testing::TestWithParam<std::filesystem::path> {
public:
    static void TestBuild(const std::filesystem::path& src) {
        TDriver driver;
        ASSERT_EQ(driver.parse(src), 0);

        std::filesystem::path ans = src;
        ans.replace_extension(".ll");

        std::ostringstream correct_answer;
        {
            std::ifstream tmp(ans);
            correct_answer << tmp.rdbuf();
        }

        llvm::LLVMContext context;
        auto module = std::make_unique<llvm::Module>("main", context);

        TProgramBuilder moduleVisitor{context, *module};
        driver.Program_->Accept(&moduleVisitor);

        ASSERT_EQ(ToLL(module.get()), correct_answer.str());
    }

    static std::string ToLL(llvm::Module* module) {
        std::string str;
        llvm::raw_string_ostream stream(str);
        module->print(stream, nullptr);
        return str;
    }
};


TEST_P(IrBuilderTest, BuildTest) {
    TestBuild(GetParam());
}


INSTANTIATE_TEST_SUITE_P(BuildTest, IrBuilderTest, ::testing::ValuesIn(FilesToTest({"ir_builder_tests"})));
