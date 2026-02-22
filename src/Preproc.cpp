#include "Preproc.h"
#include <functional>

std::vector<std::string> Preprocessor::strip_whitespace(const std::string &input) {
    return strip(input, [](const char c) {
       return std::isspace(c);
    });
}

std::vector<std::string> Preprocessor::strip(const std::string &input, const std::function<bool(char)>& discard) {
    std::vector<std::string> strip_result;

    int current = 0;
    const auto input_size = input.length();

    // Skip leading
    while (current < input_size && discard(input[current]))
        current++;

    std::string token;
    while (current < input_size) {
        if (discard(input[current])) {
            if (!token.empty()) {
                strip_result.push_back(token);
                token = "";
            }
        }else{
            token += input[current];
        }
        current++;
    }

    if (!token.empty()) {
        strip_result.push_back(token);
    }

    return strip_result;
}

std::string Preprocessor::join(const std::vector<std::string> &tokens, const std::string &delimiter, const int start) {
    std::string joined_result;
    const auto tokens_size = tokens.size();
    for (int i = start; i < tokens_size; i++) {
        joined_result += tokens[i];

        if (i != tokens_size - 1) {
            joined_result += delimiter;
        }
    }
    return joined_result;
}
