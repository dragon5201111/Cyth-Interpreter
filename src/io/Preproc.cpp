#include "../../include/io/Preproc.h"
#include "sys/Utils.h"

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
    bool skip_stack = false;
    while (std::regex_search(search_start, input.end(), match, INCLUDE)) {
        search_start = match.suffix().first;
        skip_stack = match[2].matched;
        input_result += process_include_directives(
            include_next_path(skip_stack ? match.str(2) : match.str(1), skip_stack));
    }

    dir_stack.pop_back();
    input_result += std::string(search_start, input.end());
    return input_result;
}

std::string Preprocessor::include_next_path(const std::string &path, const bool skip_stack) const {
    const auto relative_path = fs::path(path);

    if (!skip_stack) {
        for (const auto& dir : dir_stack) {
            try {
                return fs::canonical(dir / relative_path).string();
            }catch (std::exception& _) {}
        }
    }

    for (const auto& dir : include_dirs) {
        try {
            return fs::canonical(dir / relative_path).string();
        }catch (std::exception& _) {}
    }

    for (const auto& dir : utils::get_env_values(INCLUDE_ENV)) {
        try {
            return fs::canonical(fs::path(dir) / relative_path).string();
        }catch (std::exception& _) {}
    }

    throw std::runtime_error("Cannot include:" + path + ", not found.");
}
