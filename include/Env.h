#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include "Expr.h"
#include "Call.h"

using Binding = std::variant<Value, std::shared_ptr<Callable>>;

class Env {
    std::shared_ptr<Env> enclosing;
    std::unordered_map<std::string, Binding> bindings;

public:
    explicit Env(std::shared_ptr<Env> enclosing = nullptr)
        : enclosing(std::move(enclosing)) {}

    void define(const std::string& name, Binding value);
    bool is_bound(const std::string& name, uint64_t depth) const;
    void bind(const std::string& name, Binding value);
    Binding& get(const std::string& name);
};
