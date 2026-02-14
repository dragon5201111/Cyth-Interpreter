#include "Num.h"

Number::operator int() const {
    return std::visit([](auto&& value) {
        return static_cast<int>(value);
    }, value);
}

[[nodiscard]] bool Number::is_zero() const {
    return std::visit([](auto&& value) {
        return value == 0;
    }, value);
}

Number Number::operator*(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
        return Number(lhs * rhs);
    }, value, other.value);
}

Number Number::operator/(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
       return Number(lhs / rhs);
   }, value, other.value);
}

Number Number::operator-(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
       return Number(lhs - rhs);
   }, value, other.value);
}

Number Number::operator-() const {
    return std::visit([](auto&& value) {
      return Number(-value);
  }, value);
}

Number Number::operator~() const {
    return std::visit([](auto&& value) {
      return Number(~static_cast<int64_t>(value));
  }, value);
}

Number Number::operator%(const Number& other)  const {
    return std::visit([](auto&& lhs, auto&& rhs) {
               return Number(static_cast<int64_t>(lhs) % static_cast<int64_t>(rhs));
    }, value, other.value);
}

bool Number::operator<(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
       return lhs < rhs;
    }, value, other.value);
}

bool Number::operator<=(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
       return lhs <= rhs;
    }, value, other.value);
}

bool Number::operator>(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
       return lhs > rhs;
    }, value, other.value);
}

bool Number::operator>=(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
       return lhs >= rhs;
    }, value, other.value);
}

Number Number::operator&(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
        return Number(static_cast<int64_t>(lhs) & static_cast<int64_t>(rhs));
    }, value, other.value);
}

Number Number::operator|(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
        return Number(static_cast<int64_t>(lhs) | static_cast<int64_t>(rhs));
    }, value, other.value);
}

Number Number::operator^(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
        return Number(static_cast<int64_t>(lhs) ^ static_cast<int64_t>(rhs));
    }, value, other.value);
}

Number Number::operator<<(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
        return Number(static_cast<int64_t>(lhs) << static_cast<int64_t>(rhs));
    }, value, other.value);
}

Number Number::operator>>(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
        return Number(static_cast<int64_t>(lhs) >> static_cast<int64_t>(rhs));
    }, value, other.value);
}

Number Number::operator+(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
       return Number(lhs + rhs);
   }, value, other.value);
}

bool Number::operator==(const Number& other) const {
    return std::visit([](auto&& lhs, auto&& rhs) {
        return lhs == rhs;
    }, value, other.value);
}

[[nodiscard]] std::string Number::to_string() const {
    return std::visit([](auto&& value) {
        return std::to_string(value);
    }, value);
}