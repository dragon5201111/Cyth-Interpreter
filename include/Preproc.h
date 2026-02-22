#pragma once
#include <functional>
#include <string>
#include <vector>

class Preprocessor {
public:
    std::vector<std::string> strip_whitespace(const std::string& input);
    std::vector<std::string> strip(const std::string& input, const std::function<bool(char)>& discard);
    std::string join(const std::vector<std::string>& tokens, const std::string& delimiter, int start);
};
