#pragma once

#include <filesystem>
#include <vector>


inline std::vector<std::filesystem::path> FilesToTest(const std::vector<std::string>& testDirs,
                                                      const std::string& filterExt = ".java") {
    std::vector<std::filesystem::path> res;
    for (const auto& testDir : testDirs) {
        for (const auto& file : std::filesystem::directory_iterator(testDir)) {
            if (file.is_regular_file() && file.path().extension() == filterExt) {
                res.push_back(file.path());
            }
        }
    }
    return res;
}