#pragma once
#include <cstdint>
#include <variant>

#include "Print.h"

class Number : public Printable{
public:
    std::variant<int64_t, double> value;

    explicit Number(const int64_t value) : value(value) {}
    explicit Number(const double value) : value(value) {}

    explicit operator int() const {
        return std::visit([](auto&& value) {
            return static_cast<int>(value);
        }, value);
    }

    explicit operator int64_t() const { return std::get<int64_t>(value); }
    explicit operator double() const { return std::get<double>(value); }

    [[nodiscard]] bool is_zero() const {
        return std::visit([](auto&& value) {
            return value == 0;
        }, value);
    }

    Number operator*(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
            return Number(lhs * rhs);
        }, value, other.value);
    }

    Number operator/(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
           return Number(lhs / rhs);
       }, value, other.value);
    }

    Number operator-(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
           return Number(lhs - rhs);
       }, value, other.value);
    }

    Number operator-() const {
        return std::visit([](auto&& value) {
          return Number(-value);
      }, value);
    }

    Number operator~() const {
        return std::visit([](auto&& value) {
          return Number(~static_cast<int64_t>(value));
      }, value);
    }

    Number operator%(const Number& other)  const {
        return std::visit([](auto&& lhs, auto&& rhs) {
                   return Number(static_cast<int64_t>(lhs) % static_cast<int64_t>(rhs));
        }, value, other.value);
    }

    bool operator<(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
           return lhs < rhs;
        }, value, other.value);
    }

    bool operator<=(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
           return lhs <= rhs;
        }, value, other.value);
    }

    bool operator>(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
           return lhs > rhs;
        }, value, other.value);
    }

    bool operator>=(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
           return lhs >= rhs;
        }, value, other.value);
    }

    Number operator&(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
            return Number(static_cast<int64_t>(lhs) & static_cast<int64_t>(rhs));
        }, value, other.value);
    }

    Number operator|(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
            return Number(static_cast<int64_t>(lhs) | static_cast<int64_t>(rhs));
        }, value, other.value);
    }

    Number operator^(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
            return Number(static_cast<int64_t>(lhs) ^ static_cast<int64_t>(rhs));
        }, value, other.value);
    }

    Number operator<<(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
            return Number(static_cast<int64_t>(lhs) << static_cast<int64_t>(rhs));
        }, value, other.value);
    }

    Number operator>>(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
            return Number(static_cast<int64_t>(lhs) >> static_cast<int64_t>(rhs));
        }, value, other.value);
    }

    Number operator+(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
           return Number(lhs + rhs);
       }, value, other.value);
    }

    bool operator==(const Number& other) const {
        return std::visit([](auto&& lhs, auto&& rhs) {
            return lhs == rhs;
        }, value, other.value);
    }

    [[nodiscard]] std::string to_string() const override {
        return std::visit([](auto&& value) {
            return std::to_string(value);
        }, value);
    }
};
