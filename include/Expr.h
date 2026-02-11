#pragma once

#include <memory>
#include <string>
#include <cstdint>
#include <vector>
#include "Value.h"

class ArrayLiteralExpr;
class SetLiteralExpr;
class PostfixExpr;
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
    virtual Value visit_set_literal_expr(const SetLiteralExpr& expr) = 0;
    virtual Value visit_postfix_expr(const PostfixExpr& expr) = 0;
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

class ContainerExpr : public Expr {
public:
    std::vector<std::unique_ptr<Expr>> elements;
    explicit ContainerExpr(std::vector<std::unique_ptr<Expr>> elements) : elements(std::move(elements)) {}
    Value accept(ExprVisitor& visitor) const override = 0;
};

class ArrayLiteralExpr final : public ContainerExpr {
public:
    using ContainerExpr::ContainerExpr;
    Value accept(ExprVisitor &visitor) const override {
        return visitor.visit_array_literal_expr(*this);
    }
};

class SetLiteralExpr final : public ContainerExpr {
public:
    using ContainerExpr::ContainerExpr;
    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_set_literal_expr(*this);
    }
};

class PostfixExpr final : public Expr {
public:
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;

    PostfixExpr(std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    Value accept(ExprVisitor& visitor) const override {
        return visitor.visit_postfix_expr(*this);
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