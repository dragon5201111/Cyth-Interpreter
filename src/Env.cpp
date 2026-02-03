#include "Env.h"
#include <stdexcept>
#include <cstdint>

void Env::define(const std::string& name, Binding value) {
    bindings[name] = std::move(value);
}

bool Env::is_bound(const std::string &name, const uint64_t depth) const {
    if (depth == 0) {
        return bindings.count(name) == 1;
    }

    if (enclosing) {
        return enclosing->is_bound(name, depth - 1);
    }

    return false;
}

void Env::bind(const std::string& name, Binding value) {
    if (bindings.count(name)) {
        bindings[name] = std::move(value);
        return;
    }

    if (enclosing) {
        enclosing->bind(name, std::move(value));
        return;
    }

    throw std::runtime_error("Undefined variable '" + name + "'");
}

Binding& Env::get(const std::string& name) {
    if (bindings.count(name)) {
        return bindings.at(name);
    }

    if (enclosing) {
        return enclosing->get(name);
    }

    throw std::runtime_error("Undefined variable '" + name + "'");
}
