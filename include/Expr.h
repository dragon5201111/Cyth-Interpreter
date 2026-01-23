#pragma once
#include <memory>
#include <string>
#include <vector>

class IdentifierExpr;
class UnaryExpr;
class BinaryExpr;
class StringExpr;
class BoolExpr;
class ConstantExpr;
class FunctionCallExpr;

class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual void visit_identifier_expr(const IdentifierExpr& expr) = 0;
    virtual void visit_unary_expr(const UnaryExpr& expr) = 0;
    virtual void visit_binary_expr(const BinaryExpr& expr) = 0;
    virtual void visit_string_expr(const StringExpr& expr) = 0;
    virtual void visit_bool_expr(const BoolExpr& expr) = 0;
    virtual void visit_constant_expr(const ConstantExpr& expr) = 0;
    virtual void visit_function_call_expr(const FunctionCallExpr& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual void accept(ExprVisitor& visitor) const = 0;
};

class IdentifierExpr final : public Expr {
public:
    std::string name;

    explicit IdentifierExpr(std::string name) : name(std::move(name)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_identifier_expr(*this);
    }
};

class UnaryExpr final : public Expr {
public:
    std::unique_ptr<Expr> rhs;
    std::string op;

    explicit UnaryExpr(std::string op, std::unique_ptr<Expr> rhs) : op(std::move(op)), rhs(std::move(rhs)) {}
    void accept(ExprVisitor& visitor) const override {
        visitor.visit_unary_expr(*this);
    }
};

class BinaryExpr final : public Expr{
public:
    std::unique_ptr<Expr> lhs, rhs;
    std::string op;

    explicit BinaryExpr(std::unique_ptr<Expr> lhs, std::string op,  std::unique_ptr<Expr> rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)), op(std::move(op)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_binary_expr(*this);
    }
};


class StringExpr final : public Expr {
public:
    std::string value;
    explicit StringExpr(std::string value) : value(std::move(value)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_string_expr(*this);
    }
};

class BoolExpr final : public Expr {
public:
    bool value;
    explicit BoolExpr(const bool value) : value(value) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_bool_expr(*this);
    }
};

class ConstantExpr final : public Expr {
public:
    uint32_t value;
    explicit ConstantExpr(const uint32_t value) : value(value) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_constant_expr(*this);
    }
};

class FunctionCallExpr final : public Expr {
public:
    std::string name;
    std::vector<std::unique_ptr<Expr>> args;
    explicit FunctionCallExpr(std::string name, std::vector<std::unique_ptr<Expr>> args)
        : name(std::move(name)), args(std::move(args)) {}

    void accept(ExprVisitor& visitor) const override {
        visitor.visit_function_call_expr(*this);
    }
};