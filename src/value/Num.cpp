#include "../../include/value/Num.h"
#include <variant>
#include <string>

Number::operator int() const {
    return std::visit([](auto&& v){ return static_cast<int>(v); }, value);
}

[[nodiscard]] bool Number::is_zero() const {
    return std::visit([](auto&& v){ return v == 0; }, value);
}

Number Number::operator+(const Number& other) const { return binary_op(other, [](auto a, auto b){ return a + b; }); }
Number Number::operator-(const Number& other) const { return binary_op(other, [](auto a, auto b){ return a - b; }); }
Number Number::operator*(const Number& other) const { return binary_op(other, [](auto a, auto b){ return a * b; }); }
Number Number::operator/(const Number& other) const { return binary_op(other, [](auto a, auto b){ return a / b; }); }
Number Number::operator-() const { return unary_op([](auto v){ return -v; }); }

Number Number::operator~() const {
    return unary_op([](auto v){
        return ~static_cast<int64_t>(v);
    });
}

Number Number::operator&(const Number& other) const {
    return binary_op(other, [](auto a, auto b){
        return static_cast<int64_t>(a) & static_cast<int64_t>(b);
    });
}

Number Number::operator|(const Number& other) const {
    return binary_op(other, [](auto a, auto b){
        return static_cast<int64_t>(a) | static_cast<int64_t>(b);
    });
}

Number Number::operator^(const Number& other) const {
    return binary_op(other, [](auto a, auto b){
        return static_cast<int64_t>(a) ^ static_cast<int64_t>(b);
    });
}

Number Number::operator<<(const Number& other) const {
    return binary_op(other, [](auto a, auto b){
        return static_cast<int64_t>(a) << static_cast<int64_t>(b);
    });
}

Number Number::operator>>(const Number& other) const {
    return binary_op(other, [](auto a, auto b){
        return static_cast<int64_t>(a) >> static_cast<int64_t>(b);
    });
}

Number Number::operator%(const Number& other) const {
    return binary_op(other, [](auto a, auto b){
        return static_cast<int64_t>(a) % static_cast<int64_t>(b);
    });
}

bool Number::operator<(const Number& other) const { return std::visit([](auto&& a, auto&& b){ return a < b; }, value, other.value); }
bool Number::operator<=(const Number& other) const { return std::visit([](auto&& a, auto&& b){ return a <= b; }, value, other.value); }
bool Number::operator>(const Number& other) const { return std::visit([](auto&& a, auto&& b){ return a > b; }, value, other.value); }
bool Number::operator>=(const Number& other) const { return std::visit([](auto&& a, auto&& b){ return a >= b; }, value, other.value); }
bool Number::operator==(const Number& other) const { return std::visit([](auto&& a, auto&& b){ return a == b; }, value, other.value); }

[[nodiscard]] std::string Number::to_string() const {
    return std::visit([this](auto&& v){ return std::to_string(v) + postfix; }, value);
}