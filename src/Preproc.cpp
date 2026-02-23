#include "Preproc.h"
#include <functional>
#include <map>


std::vector<std::string> Preprocessor::strip_whitespace(const std::string &input) {
    return strip(input, [](const char c) {
       return c == ' ';
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
        }else if (input[current] == '\n'){
            strip_result.emplace_back("\n");
        }else {
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
    std::map<std::string, std::string> define_map;
    const auto tokens = strip_whitespace(input);
    const auto tokens_size = tokens.size();
    std::string input_result;

    int i;
    for (i = 0; i < tokens_size; i++) {
        const auto& token = tokens[i];
        if (token == INCLUDE) {
            if (i + 1 > tokens_size) {
                throw std::runtime_error("Missing path for include directive.");
            }

            input_result += preprocess_rec(file_reader.rread(next_path(tokens[i + 1]))) + '\n';
            i ++;
        }else if (token == DEFINE){
            if (i + 2 > tokens_size) {
                throw std::runtime_error("Directives must have an identifier and replacement.");
            }
            define_map.insert({tokens[i + 1], tokens[i + 2]});
            i += 2;
        }else {
            break;
        }
    }

    input_result += join(tokens, " ", i);

    for (const auto& [from, to] : define_map) {
        replace_all(input_result, from, to);
    }

    return input_result;
}

std::string Preprocessor::replace_all(std::string &input, const std::string &from, const std::string &to) {
    auto pos = input.find(from);
    while (pos != std::string::npos) {
        input.replace(pos, from.length(), to);
        pos = input.find(from, pos + to.length());
    }
    return input;
}

std::string Preprocessor::next_path(const std::string &relative_path) const {
    return fs::canonical(in_path_parent / fs::path(relative_path)).string();
}
