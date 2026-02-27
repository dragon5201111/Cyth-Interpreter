#pragma once
#include <filesystem>
#include <regex>
#include <string>
#include "Reader.h"

namespace fs = std::filesystem;

class Preprocessor {
    std::vector<fs::path> dir_stack;
    std::vector<fs::path> include_dirs;
    const std::regex INCLUDE = std::regex(R"(include\s+\"(.+)\")");

    FileReader file_reader;

    std::string process_include_directives(const std::string& in_path);
    std::string include_next_path(const std::string& path) const;
public:
    explicit Preprocessor(const std::vector<std::string>& include_dirs = {}) {
        for (const auto& include_dir : include_dirs) {
            this->include_dirs.emplace_back(include_dir);
        }
    }

    std::string preprocess(const std::string& in_path);
};
