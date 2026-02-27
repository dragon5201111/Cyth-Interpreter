#include "../../include/interpreter/Env.h"
#include <stdexcept>
#include <cstdint>

void Env::bind(const std::string& name, Binding value) {
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

void Env::rebind(const std::string& name, Binding value) {
    if (bindings.contains(name)) {
        bindings[name] = std::move(value);
        return;
    }

    if (enclosing) {
        enclosing->rebind(name, std::move(value));
        return;
    }

    throw std::runtime_error("Unable to rebind, '" + name + "'. Binding for " + name + "doesn't exist");
}

Binding& Env::get(const std::string& name) {
    if (bindings.contains(name)) {
        return bindings.at(name);
    }

    if (enclosing) {
        return enclosing->get(name);
    }

    throw std::runtime_error("'" + name + "' is unbound, cannot get binding");
}
