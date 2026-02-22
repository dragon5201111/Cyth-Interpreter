#pragma once
#include <filesystem>
#include <functional>
#include <string>
#include <vector>
#include "Reader.h"

namespace fs = std::filesystem;

class Preprocessor {
    fs::path in_path;
    fs::path in_path_parent;
    FileReader file_reader;

    std::vector<std::string> strip_whitespace(const std::string& input);
    std::vector<std::string> strip(const std::string& input, const std::function<bool(char)>& discard);
    std::string join(const std::vector<std::string>& tokens, const std::string& delimiter, int start);

    std::string preprocess_rec(const std::string& input);
    std::string next_path(const std::string& relative_path) const;
public:
    explicit Preprocessor(const std::string& in) {
        in_path = in;
        in_path_parent = in_path.parent_path();
    }
    std::string preprocess();
};
