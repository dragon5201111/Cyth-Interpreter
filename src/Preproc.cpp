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

std::string Preprocessor::preprocess() {
    return preprocess_rec(file_reader.rread(in_path.string()));
}

std::string Preprocessor::preprocess_rec(const std::string& input) {
    const auto tokens = strip_whitespace(input);
    const auto tokens_size = tokens.size();
    std::string input_result;

    int i;
    for (i = 0; i < tokens_size; i++) {
        const auto& token = tokens[i];
        if (token == "include") {
            if (i + 1 > tokens_size) {
                throw std::runtime_error("Missing path for include directive.");
            }

            input_result += preprocess_rec(file_reader.rread(next_path(tokens[i + 1]))) + '\n';
            i ++;
        }else {
            break;
        }
    }

    input_result += join(tokens, " ", i);
    return input_result;
}

std::string Preprocessor::next_path(const std::string &relative_path) const {
    return fs::canonical(in_path_parent / fs::path(relative_path)).string();
}
