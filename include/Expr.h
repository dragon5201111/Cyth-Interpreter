#pragma once
#include <deque>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <cstdint>
#include <vector>
#include "Print.h"

class Value;
using ValueVariant = std::variant<std::monostate, bool, int64_t, std::string, std::deque<Value>>;

class Value final : public Printable {
    ValueVariant value;

    [[nodiscard]] std::string to_string_impl(const std::monostate&) const { return "nil"; }
    [[nodiscard]] std::string to_string_impl(const bool b) const { return b ? "true" : "false"; }
    [[nodiscard]] std::string to_string_impl(const int64_t n) const { return std::to_string(n); }
    [[nodiscard]] std::string to_string_impl(const std::string& s) const { return s; }
    [[nodiscard]] std::string to_string_impl(const std::deque<Value>& arr) const {
        std::string result = "[";
        for (size_t i = 0; i < arr.size(); ++i) {
            result += arr[i].to_string();
            if (i + 1 < arr.size()) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

public:
    explicit Value() : value(std::monostate{}) {}
    explicit Value(bool b) : value(b) {}
    explicit Value(int64_t n) : value(n) {}
    explicit Value(std::string s) : value(std::move(s)) {}
    explicit Value(std::deque<Value> v) : value(std::move(v)) {}

    [[nodiscard]] bool is_truthy() const {
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

    [[nodiscard]] bool is_nil() const { return std::holds_alternative<std::monostate>(value); }

    [[nodiscard]] bool is_bool() const { return std::holds_alternative<bool>(value); }
    [[nodiscard]] bool as_bool() const { return std::get<bool>(value); }

    [[nodiscard]] bool is_number() const { return std::holds_alternative<int64_t>(value); }
    [[nodiscard]] int64_t as_number() const { return std::get<int64_t>(value); }

    [[nodiscard]] bool is_string() const { return std::holds_alternative<std::string>(value); }
    [[nodiscard]] std::string as_string() const { return std::get<std::string>(value); }

    [[nodiscard]] bool is_array() const { return std::holds_alternative<std::deque<Value>>(value); }
    [[nodiscard]] const std::deque<Value>& as_array() const { return std::get<std::deque<Value>>(value); }
    [[nodiscard]] std::deque<Value>& as_array() { return std::get<std::deque<Value>>(value);}

    bool operator==(const Value& other) const {
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

    bool operator!=(const Value& other) const {
        return !(*this == other);
    }

    [[nodiscard]] std::string to_string() const override {
        return std::visit([this](const auto& v) { return this->to_string_impl(v); }, value);
    }
};

class ArrayLiteralExpr;
class ArrayAccessExpr;
class IdentifierExpr;
class UnaryExpr;
class BinaryExpr;
class StringExpr;
class BoolExpr;
class ConstantExpr;
class FunctionCallExpr;
class NilExpr;

class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual Value visit_array_literal_expr(const ArrayLiteralExpr& expr) = 0;
    virtual Value visit_array_access_expr(const ArrayAccessExpr& expr) = 0;
    virtual Value visit_identifier_expr(const IdentifierExpr& expr) = 0;
    virtual Value visit_unary_expr(const UnaryExpr& expr) = 0;
    virtual Value visit_binary_expr(const BinaryExpr& expr) = 0;
    virtual Value visit_string_expr(const StringExpr& expr) = 0;
    virtual Value visit_bool_expr(const BoolExpr& expr) = 0;
    virtual Value visit_constant_expr(const ConstantExpr& expr) = 0;
    virtual Value visit_function_call_expr(const FunctionCallExpr& expr) = 0;
    virtual Value visit_nil_expr(const NilExpr& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual Value accept(ExprVisitor& visitor) const = 0;
};

class ArrayLiteralExpr final : public Expr {
public:
    std::vector<std::unique_ptr<Expr>> elements;

    explicit ArrayLiteralExpr(std::vector<std::unique_ptr<Expr>> elements) : elements(std::move(elements)) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_array_literal_expr(*this);
    }
};

class ArrayAccessExpr final : public Expr {
public:
    std::unique_ptr<Expr> array;
    std::unique_ptr<Expr> index;

    ArrayAccessExpr(std::unique_ptr<Expr> array, std::unique_ptr<Expr> index) : array(std::move(array)), index(std::move(index)) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_array_access_expr(*this);
    }
};


class IdentifierExpr final : public Expr {
public:
    std::string name;

    explicit IdentifierExpr(std::string name) : name(std::move(name)) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_identifier_expr(*this);
    }
};

class UnaryExpr final : public Expr {
public:
    std::unique_ptr<Expr> rhs;
    std::string op;

    explicit UnaryExpr(std::string op, std::unique_ptr<Expr> rhs) : rhs(std::move(rhs)), op(std::move(op)) {}
    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_unary_expr(*this);
    }
};

class BinaryExpr final : public Expr{
public:
    std::unique_ptr<Expr> lhs, rhs;
    std::string op;

    explicit BinaryExpr(std::unique_ptr<Expr> lhs, std::string op,  std::unique_ptr<Expr> rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)), op(std::move(op)) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_binary_expr(*this);
    }
};


class StringExpr final : public Expr {
public:
    std::string value;
    explicit StringExpr(std::string value) : value(std::move(value)) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_string_expr(*this);
    }
};

class BoolExpr final : public Expr {
public:
    bool value;
    explicit BoolExpr(const bool value) : value(value) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_bool_expr(*this);
    }
};

class ConstantExpr final : public Expr {
public:
    int64_t value;
    explicit ConstantExpr(const int64_t value) : value(value) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_constant_expr(*this);
    }
};

class FunctionCallExpr final : public Expr {
public:
    std::string name;
    std::vector<std::unique_ptr<Expr>> args;
    explicit FunctionCallExpr(std::string name, std::vector<std::unique_ptr<Expr>> args)
        : name(std::move(name)), args(std::move(args)) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_function_call_expr(*this);
    }
};

class NilExpr final : public Expr {
public:
    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_nil_expr(*this);
    }
};