#include <filesystem>

#include <gtest/gtest.h>

#include "driver.hh"


TEST(CommentsTest, CommentsOk) {
    TDriver driver;
    ASSERT_EQ(driver.parse(std::filesystem::path("./parse_tests/comments.java")), 0);
}