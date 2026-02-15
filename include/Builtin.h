#pragma once
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Call.h"

namespace Builtins {
    const static std::unordered_map<std::string, Value> primitive_values = {
        {"INTEGER_MAX", Value(Number(INT64_MAX))},
        {"INTEGER_MIN", Value(Number(INT64_MIN))},
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
        })},
        {"assert", std::make_shared<PrimitiveFunction>(3, [](const std::vector<Value>& args) {
            if (!args[2].is_string()) {
                throw std::invalid_argument("Assert expects a string for error message");
            }

            if (args[0] != args[1]) {
                throw std::runtime_error("Assert failed: " + args[2].as_string() + ". Got: " + args[0].to_string() + ", expected: " + args[1].to_string());
            }

            return Value();
        })}
    };
}
