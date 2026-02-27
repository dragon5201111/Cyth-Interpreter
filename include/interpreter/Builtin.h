#pragma once
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Call.h"
#include "../value/Container.h"

namespace Builtins {
    const static std::unordered_map<std::string, Value> primitive_values = {};

    // Primitive functions don't handle errors; passing invalid arguments produces undefined behavior.
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
            if (args[0] != args[1]) {
                throw std::runtime_error("Assert failed: " + args[2].as_string() + ". Got: " + args[0].to_string() + ", expected: " + args[1].to_string());
            }

            return Value();
        })},

        {"split", std::make_shared<PrimitiveFunction>(2, [](const std::vector<Value>& args) {
            std::deque<Value> split;

            std::string str = args[0].as_string();
            const char delimiter = args[1].as_string()[0];
            size_t start = 0;
            size_t end = str.find(delimiter);

            while (end != std::string::npos) {
                split.emplace_back(str.substr(start, end - start));
                start = end + 1;
                end = str.find(delimiter, start);
            }

            split.emplace_back(str.substr(start));
            return Value(std::make_shared<ArrayContainer>(split));
        })},

        {"length", std::make_shared<PrimitiveFunction>(1, [](const std::vector<Value>& args) {
            return Value(Number(static_cast<int64_t>(args[0].as_container()->size())));
        })}
    };
}
