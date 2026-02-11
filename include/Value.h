// TODO: Refactor Value class
#pragma once
#include <deque>
#include <memory>
#include <set>
#include <string>
#include <variant>
#include "Print.h"

class Value;
using ValueVariant = std::variant<
    std::monostate,
    bool,
    int64_t,
    std::shared_ptr<std::string>,
    std::shared_ptr<std::deque<Value>>,
    std::shared_ptr<std::set<Value>>
>;

class Value final : public Printable {
    ValueVariant value;
    [[nodiscard]] std::string to_string_impl(const std::monostate&) const { return "nil"; }
    [[nodiscard]] std::string to_string_impl(const bool b) const { return b ? "true" : "false"; }
    [[nodiscard]] std::string to_string_impl(const int64_t n) const { return std::to_string(n); }
    [[nodiscard]] std::string to_string_impl(const std::shared_ptr<std::string>& s) const { return *s; }
    [[nodiscard]] std::string to_string_impl(const std::shared_ptr<std::deque<Value>>& arr) const;
    [[nodiscard]] std::string to_string_impl(const std::shared_ptr<std::set<Value>>& arr) const;

    template <typename C>
    std::string container_to_string(const C& c, const std::string& left_closing, const std::string& right_closing) const {
        std::string result = left_closing;
        for (auto begin = c.begin(), end = c.end(); begin != end; ++begin) {
            if (begin != c.begin()) {
                result += ", ";
            }
            result += (*begin).to_string();
        }
        result += right_closing;
        return result;
    }

public:
    explicit Value() : value(std::monostate{}) {}
    explicit Value(bool b) : value(b) {}
    explicit Value(int64_t n) : value(n) {}
    explicit Value(std::string s) : value(std::make_shared<std::string>(std::move(s))) {}
    explicit Value(std::deque<Value> v) : value(std::make_shared<std::deque<Value>>(std::move(v))) {}
    explicit Value(std::set<Value> v) : value(std::make_shared<std::set<Value>>(std::move(v))) {}

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

    [[nodiscard]] bool is_set() const { return std::holds_alternative<std::shared_ptr<std::set<Value>>>(value); }
    [[nodiscard]] const std::set<Value>& as_set() const { return *std::get<std::shared_ptr<std::set<Value>>>(value); }

    bool operator==(const Value& other) const;

    template <typename C1, typename C2>
    bool containers_are_equal(const C1& c1, const C2& c2) const;

    bool operator!=(const Value& other) const {
        return !(*this == other);
    }

    bool operator<(const Value& other) const {
        return this->value < other.value;
    }

    [[nodiscard]] std::string to_string() const override {
        return std::visit([this](const auto& v) { return this->to_string_impl(v); }, value);
    }
};