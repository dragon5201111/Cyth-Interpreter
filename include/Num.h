#pragma once
#include <cstdint>
#include <variant>
#include "Print.h"

class Number : public Printable{
public:
    std::variant<int64_t, double, float> value;

    explicit Number(const int64_t value) : value(value) {}
    explicit Number(const double value) : value(value) {}
    explicit Number(const float value) : value(value) {}

    explicit operator int() const;

    explicit operator int64_t() const { return std::get<int64_t>(value); }
    explicit operator double() const { return std::get<double>(value); }
    explicit operator float() const { return std::get<float>(value); }

    [[nodiscard]] bool is_zero() const;

    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator-() const;
    Number operator~() const;
    Number operator%(const Number& other)  const;
    bool operator<(const Number& other) const;
    bool operator<=(const Number& other) const;
    bool operator>(const Number& other) const;
    bool operator>=(const Number& other) const;
    Number operator&(const Number& other) const;
    Number operator|(const Number& other) const;
    Number operator^(const Number& other) const;
    Number operator<<(const Number& other) const;
    Number operator>>(const Number& other) const;
    Number operator+(const Number& other) const;
    bool operator==(const Number& other) const;

    [[nodiscard]] std::string to_string() const override;
};
