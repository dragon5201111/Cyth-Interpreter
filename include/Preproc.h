#pragma once
#include <filesystem>
#include <regex>
#include <string>
#include "Reader.h"

namespace fs = std::filesystem;

class Preprocessor {
    std::vector<fs::path> include_dirs;
    const std::regex INCLUDE = std::regex(R"(include\s+\"(.+)\")");

    fs::path in_path;
    fs::path last_path_parent;
    FileReader file_reader;

    std::string preprocess_rec(const std::string& input);
    std::string next_path(const std::string& path);
public:
    explicit Preprocessor(const std::string& in, const std::vector<std::string>& include_dirs = {}) {
        in_path = in;
        last_path_parent = in_path.parent_path();
        for (const auto& include_dir : include_dirs) {
            this->include_dirs.emplace_back(include_dir);
        }
    }

    std::string preprocess();
};
