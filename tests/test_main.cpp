#include <filesystem>

#include <gtest/gtest.h>

#include "driver.hh"
#include "yaml_visitor.hh"


class TCompilerTest : public testing::TestWithParam<std::filesystem::path> {
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


TEST_P(TCompilerTest, ParseTest) {
    TestParse(GetParam());
}


std::vector<std::filesystem::path> FilesToTest(const std::vector<std::string>& testDirs) {
    std::vector<std::filesystem::path> res;
    for (const auto& testDir : testDirs) {
        for (const auto& file : std::filesystem::directory_iterator(testDir)) {
            if (file.is_regular_file() && file.path().extension() == ".java") {
                res.push_back(file.path());
            }
        }
    }
    return res;
}

INSTANTIATE_TEST_SUITE_P(ParseTest, TCompilerTest, ::testing::ValuesIn(FilesToTest({"parse_tests"})));