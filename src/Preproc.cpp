#include "Preproc.h"
#include <map>

std::string Preprocessor::preprocess() {
    return preprocess_rec(file_reader.rread(in_path.string()));
}

std::string Preprocessor::preprocess_rec(const std::string& input) {
    std::string input_result;
    std::smatch match;

    auto search_start = input.cbegin();
    while (std::regex_search(search_start, input.end(), match, INCLUDE_REGEX)) {
        search_start = match.suffix().first;
        input_result += preprocess_rec(file_reader.rread(next_path(match.str(1))));
    }

    input_result += std::string(search_start, input.end());
    return input_result;
}

std::string Preprocessor::next_path(const std::string &relative_path) const {
    return fs::canonical(in_path_parent / fs::path(relative_path)).string();
}
