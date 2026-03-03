#pragma once
#include <cstdint>
#include <utility>
#include <variant>
#include "../io/Print.h"

class Number : public Printable{
    template<typename F>
    Number binary_op(const Number& other, F&& f) const {
        return std::visit([&]<typename T0, typename T1>(T0&& lhs, T1&& rhs){
            return Number{ static_cast<std::common_type_t<std::decay_t<T0>, std::decay_t<T1>>>(f(lhs, rhs)) };
        }, value, other.value);
    }

    template<typename F>
    Number unary_op(F&& f) const {
        return std::visit([&]<typename T0>(T0&& v){
            return Number{ static_cast<std::decay_t<T0>>(f(v))};
        }, value);
    }

public:
    std::variant<int8_t, int64_t, double, float> value;
    explicit Number(const int8_t value) : value(value) {}
    explicit Number(const int64_t value) : value(value) {}
    explicit Number(const double value) : value(value) {}
    explicit Number(const float value) : value(value) {}

    explicit operator int() const;
    explicit operator int8_t() const { return std::get<int8_t>(value); }
    explicit operator int64_t() const { return std::get<int64_t>(value); }
    explicit operator double() const { return std::get<double>(value); }
    explicit operator float() const { return std::get<float>(value); }

    [[nodiscard]] bool is_zero() const;
    Number operator+(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;
    Number operator-() const;

    Number operator~() const;
    Number operator&(const Number& other) const;
    Number operator|(const Number& other) const;
    Number operator^(const Number& other) const;
    Number operator<<(const Number& other) const;
    Number operator>>(const Number& other) const;
    Number operator%(const Number& other)  const;

    bool operator<(const Number& other) const;
    bool operator<=(const Number& other) const;
    bool operator>(const Number& other) const;
    bool operator>=(const Number& other) const;
    bool operator==(const Number& other) const;

    [[nodiscard]] std::string to_string() const override;
};
