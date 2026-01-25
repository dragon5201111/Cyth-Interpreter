#pragma once
#include <memory>
#include <unordered_map>

#include "Expr.h"

class Env {
    std::shared_ptr<Env> enclosing;
    std::unordered_map<std::string, Value> values;
public:
    explicit Env() : enclosing({}) {}
    explicit Env(const std::shared_ptr<Env> &enclosing) : enclosing(enclosing) {}
    void define(const std::string& name, Value value);
    void assign(const std::string& name, Value value);
    Value get(const std::string& name);
};
