#pragma once
#include <cstdint>
#include <stdexcept>
#include <deque>
#include <memory>
#include <string>
#include <variant>
#include "Print.h"

class Value;
using ValueVariant = std::variant<std::monostate, bool, int64_t, std::shared_ptr<std::string>, std::shared_ptr<std::deque<Value>>>;

class Value final : public Printable {
    ValueVariant value;
    [[nodiscard]] std::string to_string_impl(const std::monostate&) const { return "nil"; }
    [[nodiscard]] std::string to_string_impl(const bool b) const { return b ? "true" : "false"; }
    [[nodiscard]] std::string to_string_impl(const int64_t n) const { return std::to_string(n); }
    [[nodiscard]] std::string to_string_impl(const std::shared_ptr<std::string>& s) const { return *s; }
    [[nodiscard]] std::string to_string_impl(const std::shared_ptr<std::deque<Value>>& arr) const;

public:
    explicit Value() : value(std::monostate{}) {}
    explicit Value(bool b) : value(b) {}
    explicit Value(int64_t n) : value(n) {}
    explicit Value(std::string s) : value(std::make_shared<std::string>(std::move(s))) {}
    explicit Value(std::deque<Value> v) : value(std::make_shared<std::deque<Value>>(std::move(v))) {}

    [[nodiscard]] bool is_truthy() const;
    [[nodiscard]] bool is_nil() const { return std::holds_alternative<std::monostate>(value); }

    [[nodiscard]] bool is_bool() const { return std::holds_alternative<bool>(value); }
    [[nodiscard]] bool as_bool() const { return std::get<bool>(value); }

    [[nodiscard]] bool is_number() const { return std::holds_alternative<int64_t>(value); }
    [[nodiscard]] int64_t as_number() const { return std::get<int64_t>(value); }

    [[nodiscard]] bool is_string() const { return std::holds_alternative<std::shared_ptr<std::string>>(value); }
    [[nodiscard]] const std::string& as_string() const { return *std::get<std::shared_ptr<std::string>>(value); }
    [[nodiscard]] std::string& as_string() { return *std::get<std::shared_ptr<std::string>>(value); }

    [[nodiscard]] bool is_array() const { return std::holds_alternative<std::shared_ptr<std::deque<Value>>>(value); }
    [[nodiscard]] const std::deque<Value>& as_array() const { return *std::get<std::shared_ptr<std::deque<Value>>>(value); }
    [[nodiscard]] std::deque<Value>& as_array() { return *std::get<std::shared_ptr<std::deque<Value>>>(value);}

    bool operator==(const Value& other) const;

    bool operator!=(const Value& other) const {
        return !(*this == other);
    }

    [[nodiscard]] std::string to_string() const override {
        return std::visit([this](const auto& v) { return this->to_string_impl(v); }, value);
    }
};