#include "Value.h"
#include <stdexcept>

std::string Value::to_string_impl(const std::shared_ptr<std::deque<Value>> &arr) const {
    return container_to_string(*arr, "[", "]");
}

std::string Value::to_string_impl(const std::shared_ptr<std::set<Value> > &arr) const {
    return container_to_string(*arr, "{", "}");
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

    // TODO: Handle stl container case generically
    if (is_array()) {
        return !as_array().empty();
    }

    if (is_set()) {
        return !as_set().empty();
    }

    throw std::runtime_error("Cannot evaluate is truthy");
}

bool Value::operator==(const Value &other) const {
    if (this->is_number() && other.is_number()) {
        return this->as_number() == other.as_number();
    }

    if (this->is_bool() && other.is_bool()) {
        return this->as_bool() == other.as_bool();
    }

    if (this->is_nil() && other.is_nil()) {
        return true;
    }

    if (this->is_string() && other.is_string()) {
        return this->as_string() == other.as_string();
    }

    // TODO: Handle stl container case generically
    if (this->is_array() && other.is_array()) {
        return containers_are_equal(this->as_array(), other.as_array());
    }

    if (this->is_set() && other.is_set()) {
        return containers_are_equal(this->as_set(), other.as_set());
    }

    return false;
}

template<typename C1, typename C2>
bool Value::containers_are_equal(const C1 &c1, const C2 &c2) const {
    if (c1.size() != c2.size()) {
        return false;
    }

    return std::equal(c1.begin(), c1.end(), c2.begin(), c2.end());
}
