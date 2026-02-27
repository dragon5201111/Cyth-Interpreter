#pragma once
#include <memory>
#include <string>
#include <variant>
#include "./Num.h"

class AbstractContainer;
class Value final : public Printable {
    std::variant<
        std::monostate,
        bool,
        Number,
        std::shared_ptr<AbstractContainer>,
        std::shared_ptr<std::string>
    > value;

    [[nodiscard]] std::string to_string_impl(const std::monostate&) const { return "nil"; }
    [[nodiscard]] std::string to_string_impl(const bool b) const { return b ? "true" : "false"; }
    [[nodiscard]] std::string to_string_impl(const Number& n) const { return n.to_string(); }
    [[nodiscard]] std::string to_string_impl(const std::shared_ptr<std::string>& s) const { return *s; }
    [[nodiscard]] std::string to_string_impl(const std::shared_ptr<AbstractContainer>& a) const;
public:
    explicit Value() : value(std::monostate{}) {}
    explicit Value(bool b) : value(b) {}
    explicit Value(Number n) : value(n) {}
    explicit Value(std::string s) : value(std::make_shared<std::string>(std::move(s))) {}
    explicit Value(const char *s) : value(std::make_shared<std::string>(s)) {}
    explicit Value(std::shared_ptr<AbstractContainer> a) : value(std::move(a)) {}

    [[nodiscard]] bool is_truthy() const;
    [[nodiscard]] bool is_nil() const { return std::holds_alternative<std::monostate>(value); }

    [[nodiscard]] bool is_bool() const { return std::holds_alternative<bool>(value); }
    [[nodiscard]] bool as_bool() const { return std::get<bool>(value); }

    [[nodiscard]] bool is_number() const { return std::holds_alternative<Number>(value); }
    [[nodiscard]] Number as_number() const { return std::get<Number>(value); }

    [[nodiscard]] bool is_string() const { return std::holds_alternative<std::shared_ptr<std::string>>(value); }
    [[nodiscard]] const std::string& as_string() const { return *std::get<std::shared_ptr<std::string>>(value); }
    [[nodiscard]] std::string& as_string() { return *std::get<std::shared_ptr<std::string>>(value); }

    [[nodiscard]] bool is_container() const { return std::holds_alternative<std::shared_ptr<AbstractContainer>>(value); }
    [[nodiscard]] std::shared_ptr<AbstractContainer> as_container() const { return std::get<std::shared_ptr<AbstractContainer>>(value); }

    bool operator==(const Value& other) const;
    bool operator!=(const Value& other) const;
    bool operator<(const Value& other) const;

    [[nodiscard]] bool other_is_same_type(const Value& other) const;

    bool operator<=(const Value &other) const;
    bool operator>(const Value &other) const;
    bool operator>=(const Value &other) const;

    [[nodiscard]] std::string to_string() const override {
        return std::visit([this](const auto& v) { return to_string_impl(v); }, value);
    }
};