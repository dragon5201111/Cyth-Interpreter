#include "../../include/io/Preproc.h"
#include <map>

std::string Preprocessor::preprocess(const std::string& in_path) {
    dir_stack.clear(); // Need to clear stack in case of multiple calls to preprocess
    return process_include_directives(in_path);
}

std::string Preprocessor::process_include_directives(const std::string& in_path) {
    std::string input_result;
    std::smatch match;

    dir_stack.push_back(fs::path(in_path).parent_path());

    const std::string input = file_reader.rread(in_path);
    auto search_start = input.cbegin();
    while (std::regex_search(search_start, input.end(), match, INCLUDE)) {
        search_start = match.suffix().first;
        input_result += process_include_directives(include_next_path(match.str(1)));
    }

    dir_stack.pop_back();
    input_result += std::string(search_start, input.end());
    return input_result;
}

std::string Preprocessor::include_next_path(const std::string &path) const {
    const auto relative_path = fs::path(path);

    for (const auto& dir : dir_stack) {
        try {
            return fs::canonical(dir / relative_path).string();
        }catch (std::exception& _) {}
    }

    for (const auto& dir : include_dirs) {
        try {
            return fs::canonical(dir / relative_path).string();
        }catch (std::exception& _) {}
    }

    throw std::runtime_error("Cannot include:" + path + ", not found.");
}
