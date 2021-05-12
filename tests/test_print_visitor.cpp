#include <filesystem>

#include <gtest/gtest.h>

#include "driver.hh"
#include "yaml_visitor.hh"

#include "test_utils.hh"


class PrintVisitorTest : public testing::TestWithParam<std::filesystem::path> {
protected:
    static void TestParse(const std::filesystem::path& src) {
        TDriver driver;
        ASSERT_EQ(driver.parse(src), 0);

        std::filesystem::path ans = src;
        ans.replace_extension(".yaml");

        TYamlVisitor visitor;
        driver.Program_->Accept(&visitor);

        std::ostringstream visitor_out;

        std::ostringstream correct_answer;
        {
            std::ifstream tmp(ans);
            correct_answer << tmp.rdbuf();
        }

        visitor.Print(visitor_out);
        ASSERT_EQ(visitor_out.str(), correct_answer.str());
    }
};


TEST_P(PrintVisitorTest, ParseTest) {
    TestParse(GetParam());
}


INSTANTIATE_TEST_SUITE_P(ParseTest, PrintVisitorTest,
                         ::testing::ValuesIn(FilesToTest({"print_visitor_tests"})));