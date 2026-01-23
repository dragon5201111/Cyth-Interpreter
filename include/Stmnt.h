#pragma once
#include <memory>
#include <string>
#include <utility>

#include "Expr.h"

class VariableDeclStmnt;
class VariableAssignStmnt;
class ReturnStmnt;
class IfStmnt;
class WhileStmnt;
class PrintStmnt;

class StmntVisitor {
public:
    virtual ~StmntVisitor() = default;
    virtual void visit_variable_decl_stmnt(const VariableDeclStmnt& stmnt) = 0;
    virtual void visit_variable_assign_stmnt(const VariableAssignStmnt& stmnt) = 0;
    virtual void visit_return_stmnt(const ReturnStmnt& stmnt) = 0;
    virtual void visit_if_stmnt(const IfStmnt& stmnt) = 0;
    virtual void visit_while_stmnt(const WhileStmnt& stmnt) = 0;
    virtual void visit_print_stmnt(const PrintStmnt& stmnt) = 0;
};

class Stmnt {
public:
    virtual ~Stmnt() = default;
    virtual void accept(StmntVisitor& visitor) const = 0;
};

class VariableDeclStmnt final : public Stmnt {
public:
    std::string name;
    explicit VariableDeclStmnt(std::string name) : name(std::move(name)) {}

    void accept(StmntVisitor &visitor) const override {
        visitor.visit_variable_decl_stmnt(*this);
    }
};

class VariableAssignStmnt final : public Stmnt {
public:
    std::string name;
    std::unique_ptr<Expr> rhs;

    explicit VariableAssignStmnt(std::string name, std::unique_ptr<Expr> rhs) : name(std::move(name)), rhs(std::move(rhs)) {}

    void accept(StmntVisitor &visitor) const override {
        visitor.visit_variable_assign_stmnt(*this);
    }
};


class ReturnStmnt final : public Stmnt {
public:
    std::unique_ptr<Expr> value;
    explicit ReturnStmnt (std::unique_ptr<Expr> value) : value(std::move(value)) {}
    void accept(StmntVisitor &visitor) const override {
        visitor.visit_return_stmnt(*this);
    }
};

class IfStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmnt>> then_branch;
    std::vector<std::unique_ptr<Stmnt>> else_branch;

    explicit IfStmnt(std::unique_ptr<Expr> condition,
        std::vector<std::unique_ptr<Stmnt>> then_branch,
        std::vector<std::unique_ptr<Stmnt>> else_branch = {}) :
    condition(std::move(condition)), then_branch(std::move(then_branch)), else_branch(std::move(else_branch)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_if_stmnt(*this);
    }
};

class WhileStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit WhileStmnt(std::unique_ptr<Expr> condition, std::vector<std::unique_ptr<Stmnt>> body) : condition(std::move(condition)), body(std::move(body)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_while_stmnt(*this);
    }
};

class PrintStmnt final: public Stmnt {
public:
    std::unique_ptr<Expr> expr;
    explicit PrintStmnt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_print_stmnt(*this);
    }
};
