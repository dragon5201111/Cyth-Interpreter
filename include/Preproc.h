#pragma once
#include <filesystem>
#include <regex>
#include <string>
#include "Reader.h"

namespace fs = std::filesystem;

class Preprocessor {
    const std::regex INCLUDE_REGEX = std::regex(R"(include\s+\"(.+)\")");
    // TODO: Fix define regex
    // const std::regex DEFINE_REGEX = std::regex(R"(define\s+(?:([^\s()]+)|\(([^)]+\))))");

    fs::path in_path;
    fs::path in_path_parent;
    FileReader file_reader;

    std::string preprocess_rec(const std::string& input);
    std::string next_path(const std::string& relative_path) const;
public:
    explicit Preprocessor(const std::string& in) {
        in_path = in;
        in_path_parent = in_path.parent_path();
    }

    std::string preprocess();
};
