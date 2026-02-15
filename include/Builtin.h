#pragma once
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Call.h"

namespace Builtins {
    const static std::unordered_map<std::string, Value> primitive_values = {
        {"NUMBER_MAX", Value(INT64_MAX)},
        {"NUMBER_MIN", Value(INT64_MIN)}
    };

    const static std::unordered_map<std::string, std::shared_ptr<PrimitiveFunction>> primitive_functions = {
        {"print", std::make_shared<PrimitiveFunction>(Callable::VARIABLE_ARITY, [](const std::vector<Value>& args) {
            const auto args_size = args.size();
            for (int i = 0; i < args_size; ++i) {
                std::cout << args[i];
                if (i != args_size - 1) {
                    std::cout << " ";
                }
            }
            return Value();
        })},

        {"exit", std::make_shared<PrimitiveFunction>(1, [](const std::vector<Value>& args) {
            exit(static_cast<int>(args[0].as_number()));
            return Value(); // Dummy return value
        })}
    };
}
