#pragma once
#include <memory>
#include <vector>
#include "./Stmnt.h"

class FunctionDecl;
class ProgramDecl;

class DeclVisitor {
public:
    virtual ~DeclVisitor() = default;
    virtual void visit_function_decl(const FunctionDecl& func) = 0;
    virtual int64_t visit_program(const ProgramDecl& program) = 0;
};

template <typename T>
class Decl {
public:
    virtual ~Decl() = default;
    virtual T accept(DeclVisitor& visitor) const = 0;
};

class FunctionDecl final : public Decl<void> {
public:
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit FunctionDecl(std::string name, std::vector<std::string> parameters = {}, std::vector<std::unique_ptr<Stmnt>> body = {})
        : name(std::move(name)),
          parameters(std::move(parameters)),
          body(std::move(body)) {}

    void accept(DeclVisitor& visitor) const override {
        visitor.visit_function_decl(*this);
    }
};

class ProgramDecl final : public Decl<int64_t> {
public:
    std::string args_name;
    std::vector<std::string> args;
    std::vector<std::unique_ptr<FunctionDecl>> declarations;
    std::vector<std::unique_ptr<Stmnt>> body;

    explicit ProgramDecl(
        std::string args_name = "",
        std::vector<std::unique_ptr<FunctionDecl>> declarations = {},
        std::vector<std::unique_ptr<Stmnt>> body = {})
        :
            args_name(std::move(args_name)),
            declarations(std::move(declarations)),
            body(std::move(body)) {}

    int64_t accept(DeclVisitor &visitor) const override {
        return visitor.visit_program(*this);
    }
};


