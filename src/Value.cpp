#include "Value.h"
#include "Container.h"
#include <stdexcept>

std::string Value::to_string_impl(const std::shared_ptr<AbstractContainer> &a) const {
    return a->to_string();
}

bool Value::is_truthy() const {
    if (is_nil()) {
        return false;
    }

    if (is_bool()) {
        return as_bool();
    }

    if (is_number()) {
        return !as_number().is_zero();
    }

    if (is_string()) {
        return !as_string().empty();
    }

    if (is_container()) {
        return !as_container()->empty();
    }

    throw std::runtime_error("Cannot evaluate is truthy");
}

bool Value::operator==(const Value &other) const {
    if (is_number() && other.is_number()) {
        return as_number() == other.as_number();
    }

    if (is_bool() && other.is_bool()) {
        return as_bool() == other.as_bool();
    }

    if (is_nil() && other.is_nil()) {
        return true;
    }

    if (is_string() && other.is_string()) {
        return as_string() == other.as_string();
    }

    if (is_container() && other.is_container()) {
        return *as_container() == *other.as_container();
    }

    return false;
}
