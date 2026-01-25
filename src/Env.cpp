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
        enclosing->assign(name, value);
    }

    throw std::runtime_error("Undefined variable: " + name);
}
