#include "Env.h"
#include <stdexcept>

void Env::define(const std::string& name, Binding value) {
    bindings[name] = std::move(value);
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
