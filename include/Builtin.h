#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Call.h"

namespace Builtins {
    const static std::unordered_map<std::string, Value> primitive_values = {
        // Add primitive values here
    };

    const static std::unordered_map<std::string, std::shared_ptr<PrimitiveFunction>> primitive_functions = {
        {"print", std::make_shared<PrimitiveFunction>([](const std::vector<Value>& args) {
            const auto args_size = args.size();
            for (int i = 0; i < args_size; ++i) {
                std::cout << args[i];
                if (i != args_size - 1) {
                    std::cout << " ";
                }
            }
            return Value();
        })},

        {"exit", std::make_shared<PrimitiveFunction>([](const std::vector<Value>& args) {
            if (args.size() != 1) {
                throw std::invalid_argument("Exit function must have exactly 1 number argument.");
            }

            exit(static_cast<int>(args[0].as_number()));
            return Value(); // Dummy return value
        })},

    {"length", std::make_shared<PrimitiveFunction>([](const std::vector<Value>& args) {
            if (args.size() != 1) {
                throw std::invalid_argument("Length function must have exactly 1 argument.");
            }

            const auto& array = args[0];
            if (!array.is_array()) {
                throw std::invalid_argument("Length expects an array.");
            }

            return Value(static_cast<int64_t>(array.as_array().size()));
        })}
    };
}
