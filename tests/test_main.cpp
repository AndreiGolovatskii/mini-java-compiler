#include <filesystem>

#include <gtest/gtest.h>

#include "driver.hh"


class TCompilerTest : public testing::TestWithParam<std::string> {
protected:
    static void TestParse(const std::string& src) {
        TDriver driver;
        ASSERT_EQ(driver.parse(src), 0);
    }
};


TEST_P(TCompilerTest, ParseTest) {
    TestParse(GetParam());
}


std::vector<std::string> FilesToTest(const std::vector<std::string>& testDirs) {
    std::vector<std::string> res;
    for (const auto& testDir : testDirs) {
        for (const auto& file : std::filesystem::directory_iterator(testDir)) {
            if (file.is_regular_file()) {
                res.push_back(file.path());
            }
        }
    }
    return res;
}

INSTANTIATE_TEST_SUITE_P(ParseTest, TCompilerTest, ::testing::ValuesIn(FilesToTest({"parse_tests"})));