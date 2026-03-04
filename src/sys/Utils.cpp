#include "../include/sys/Utils.h"
#include <sstream>
#include <cstdlib>

namespace utils {
    std::vector<std::string> get_env_values(const std::string& name) {
        const auto values = std::getenv(name.c_str());
        if (values == nullptr) {
            return {};
        }

        std::stringstream string_stream(values);
        char delimiter = ':'; // Default is colon
        #ifdef _WIN32
            delimiter = ';';
        #endif

        std::vector<std::string> split_result;
        std::string value;
        while (std::getline(string_stream, value, delimiter)) {
            split_result.push_back(value);
        }

        return split_result;
    }
}
