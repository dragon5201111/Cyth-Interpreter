#include "Env.h"

#include <stdexcept>
#include <utility>

void Env::define(const std::string &name, Value value) {
    values[name] = std::move(value);
}

void Env::assign(const std::string &name, Value value) {
    if (values.count(name)) {
        values[name] = std::move(value);
        return;
    }

    if (enclosing) {
        enclosing->assign(name, std::move(value));
        return;
    }

    throw std::runtime_error("Undefined variable: " + name);
}


Value Env::get(const std::string &name) {
    if (values.count(name)) {
        return values[name];
    }

    if (enclosing) {
        return enclosing->get(name);
    }

    throw std::runtime_error("Undefined variable: " + name);
}
