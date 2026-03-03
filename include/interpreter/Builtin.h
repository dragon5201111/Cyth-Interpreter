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

        {"length", std::make_shared<PrimitiveFunction>(1, [](const std::vector<Value>& args) {
            if (args[0].is_string()) {
                return Value(Number(static_cast<int64_t>(args[0].to_string().size())));
            }

            return Value(Number(static_cast<int64_t>(args[0].as_container()->size())));
        })},

        {"remove", std::make_shared<PrimitiveFunction>(2, [](const std::vector<Value>& args) {
            args[0].as_container()->remove(args[1]);
            return Value();
        })},

        {"put", std::make_shared<PrimitiveFunction>(3, [](const std::vector<Value>& args) {
            args[0].as_container()->put(args[1], args[2]);
            return Value();
        })},


        {"id", std::make_shared<PrimitiveFunction>(1, [](const std::vector<Value>& args) {
            std::stringstream string_stream;
            string_stream << &args[0];
            return Value(string_stream.str());
        })},

        {"open", std::make_shared<PrimitiveFunction>(2, [](const std::vector<Value>& args) {
            const auto file_container = std::make_shared<FileContainer>();
            file_container->open(args[0].as_string(), args[1].as_string());
            return Value(file_container);
        })},

        {"close", std::make_shared<PrimitiveFunction>(1, [](const std::vector<Value>& args) {
            args[0].as_container<FileContainer>()->close();
            return Value();
        })},
    };
}
