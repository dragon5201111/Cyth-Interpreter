#pragma once
#include <memory>
#include <string>
#include <utility>
#include "Expr.h"

class BreakStmnt;
class VariableDeclStmnt;
class AssignStmnt;
class ReturnStmnt;
class IfStmnt;
class WhileStmnt;
class ForStmnt;
class FunctionCallStmnt;

class StmntVisitor {
public:
    virtual ~StmntVisitor() = default;
    virtual void visit_break_stmnt(const BreakStmnt& stmnt) = 0;
    virtual void visit_variable_decl_stmnt(const VariableDeclStmnt& stmnt) = 0;
    virtual void visit_variable_assign_stmnt(const AssignStmnt& stmnt) = 0;
    virtual void visit_return_stmnt(const ReturnStmnt& stmnt) = 0;
    virtual void visit_if_stmnt(const IfStmnt& stmnt) = 0;
    virtual void visit_while_stmnt(const WhileStmnt& stmnt) = 0;
    virtual void visit_for_stmnt(const ForStmnt& stmnt) = 0;
    virtual void visit_function_call_stmnt(const FunctionCallStmnt& stmnt) = 0;
};

class Stmnt {
public:
    virtual ~Stmnt() = default;
    virtual void accept(StmntVisitor& visitor) const = 0;
};

class BreakStmnt final : public Stmnt {
public:
    explicit BreakStmnt() = default;

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_break_stmnt(*this);
    }
};

class VariableDeclStmnt final : public Stmnt {
public:
    std::string name;
    std::unique_ptr<Expr> initializer;

    explicit VariableDeclStmnt(std::string name, std::unique_ptr<Expr> initializer = {}) : name(std::move(name)), initializer(std::move(initializer)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_variable_decl_stmnt(*this);
    }
};


class AssignStmnt final : public Stmnt {
public:
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;

    explicit AssignStmnt(std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

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

class ForStmnt final : public Stmnt {
public:
    std::unique_ptr<Stmnt> initializer;
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmnt> assignment;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit ForStmnt(std::unique_ptr<Stmnt> initializer, std::unique_ptr<Expr> condition, std::unique_ptr<Stmnt> assignment, std::vector<std::unique_ptr<Stmnt>> body) :
        initializer(std::move(initializer)), condition(std::move(condition)), assignment(std::move(assignment)), body(std::move(body)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_for_stmnt(*this);
    }
};

// TODO: Change this to discard statement?
class FunctionCallStmnt : public Stmnt {
public:
    std::unique_ptr<Expr> function_call_expr;

    explicit FunctionCallStmnt(std::unique_ptr<Expr> function_call_expr) : function_call_expr(std::move(function_call_expr)) {}

    void accept(StmntVisitor& visitor) const override {
        visitor.visit_function_call_stmnt(*this);
    }
};
