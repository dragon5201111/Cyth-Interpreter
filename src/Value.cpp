#include "Value.h"

std::string Value::to_string_impl(const std::shared_ptr<std::deque<Value>> &arr) const {
    std::string result = "[";

    const auto arr_size = arr->size();
    for (size_t i = 0; i < arr_size; ++i) {
        result += arr->at(i).to_string();
        if (i + 1 < arr_size) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

bool Value::is_truthy() const {
    if (is_nil()) {
        return false;
    }

    if (is_bool()) {
        return as_bool();
    }

    if (is_number()) {
        return as_number() != 0;
    }

    if (is_string()) {
        return !as_string().empty();
    }

    if (is_array()) {
        return !as_array().empty();
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

    if (this->is_array() && other.is_array()) {
        const auto& lhs_array = this->as_array();
        const auto& rhs_array = other.as_array();

        const auto lhs_array_size = lhs_array.size();
        if (lhs_array_size != rhs_array.size()) {
            return false;
        }

        for (size_t i = 0; i < lhs_array_size; ++i) {
            if (lhs_array[i] != rhs_array[i]) {
                return false;
            }
        }
        return true;
    }

    return false;
}
