#include "Preproc.h"
#include <map>

std::string Preprocessor::preprocess() {
    return preprocess_rec(file_reader.rread(in_path.string()));
}

// TODO: Fix - handling comments
std::string Preprocessor::preprocess_rec(const std::string& input) {
    std::string input_result;
    std::smatch match;

    auto search_start = input.cbegin();
    while (std::regex_search(search_start, input.end(), match, INCLUDE)) {
        search_start = match.suffix().first;
        input_result += preprocess_rec(file_reader.rread(next_path(match.str(1))));
    }

    input_result += std::string(search_start, input.end());
    return input_result;
}

std::string Preprocessor::next_path(const std::string &path) {
    const auto relative_path = fs::path(path);
    // Is absolute path, no need to check or update last_path_parent
    if (fs::exists(relative_path)) {
        return relative_path.string();
    }

    fs::path next_path;
    for (const auto& dir : include_dirs) {
        try {
            next_path = fs::canonical(dir / relative_path);
            last_path_parent = next_path.parent_path();
            return next_path.string();
        }catch (std::exception& _) {}
    }

    next_path = fs::canonical(last_path_parent / relative_path);
    last_path_parent = next_path.parent_path();
    return next_path.string();
}
