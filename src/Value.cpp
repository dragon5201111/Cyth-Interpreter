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
    if (!other_is_same_type(other)) {
        return false;
    }

    if (is_number()) {
        return as_number() == other.as_number();
    }

    if (is_bool()) {
        return as_bool() == other.as_bool();
    }

    if (is_string()) {
        return as_string() == other.as_string();
    }

    if (is_container()) {
        return *as_container() == *other.as_container();
    }

    return true;
}

bool Value::operator!=(const Value &other) const {
    return !(*this == other);
}

bool Value::operator<(const Value &other) const {
    if (!other_is_same_type(other)) {
        return value.index() < other.value.index();
    }

    if (is_number()) {
        return as_number() < other.as_number();
    }

    if (is_bool()) {
        return as_bool() < other.as_bool();
    }

    if (is_string()) {
        return as_string() < other.as_string();
    }

    if (is_container()) {
        return *as_container() < *other.as_container();
    }

    return false;
}

bool Value::other_is_same_type(const Value &other) const {
    return value.index() == other.value.index();
}


bool Value::operator<=(const Value &other) const {
    return *this < other || *this == other;
}

bool Value::operator>(const Value &other) const {
    return !this->operator<=(other);
}

bool Value::operator>=(const Value &other) const {
    return !this->operator<(other);
}