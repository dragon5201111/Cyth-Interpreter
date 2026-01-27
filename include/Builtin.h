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
            for (const auto& arg : args) {
                std::cout << arg << " ";
            }
            return Value();
        })}
    };
}
