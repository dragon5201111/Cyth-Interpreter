#pragma once
#include <memory>
#include <vector>
#include "Stmnt.h"

class FunctionDecl;
class ProgramDecl;

class DeclVisitor {
public:
    virtual ~DeclVisitor() = default;
    virtual void visit_function_decl(const FunctionDecl& func) = 0;
    virtual void visit_program(const ProgramDecl& program) = 0;
};

class Decl {
public:
    virtual ~Decl() = default;
    virtual void accept(DeclVisitor& visitor) const = 0;
};

class FunctionDecl final : public Decl {
public:
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::unique_ptr<Stmnt>> body;

    FunctionDecl(std::string name, std::vector<std::string> parameters, std::vector<std::unique_ptr<Stmnt>> body)
        : name(std::move(name)),
          parameters(std::move(parameters)),
          body(std::move(body)) {}

    void accept(DeclVisitor& visitor) const override {
        visitor.visit_function_decl(*this);
    }
};

class ProgramDecl final : public Decl {
public:
    std::vector<std::unique_ptr<FunctionDecl>> declarations;
    std::vector<std::unique_ptr<Stmnt>> stmts;

    explicit ProgramDecl(std::vector<std::unique_ptr<FunctionDecl>> declarations = {}, std::vector<std::unique_ptr<Stmnt>> stmts = {})
        : declarations(std::move(declarations)), stmts(std::move(stmts)) {}

    void accept(DeclVisitor &visitor) const override {
        visitor.visit_program(*this);
    }
};


