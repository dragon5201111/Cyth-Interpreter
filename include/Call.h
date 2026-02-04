#pragma once
#include <functional>
#include <utility>
#include "Expr.h"
#include "Prog.h"

class Interpreter;
class Env;

class Callable {
public:
    virtual ~Callable() = default;
    virtual Value call(Interpreter& interpreter, const std::vector<Value>& args) = 0;
};


class UserFunction final : public Callable {
    std::weak_ptr<Env> enclosing_env; // Avoid circular references
    const FunctionDecl& function_decl;

public:
    explicit UserFunction(const std::shared_ptr<Env>& enclosing_env, const FunctionDecl& function_decl)
        : enclosing_env(enclosing_env), function_decl(function_decl) {}

    Value call(Interpreter& interpreter, const std::vector<Value>& args) override;
};


class PrimitiveFunction final : public Callable {
    std::function<Value(const std::vector<Value>&)> function;
public:
    explicit PrimitiveFunction(std::function<Value(const std::vector<Value>&)> function) : function(std::move(function)) {}
    Value call(Interpreter& interpreter, const std::vector<Value>& args) override {
        return function(args);
    }
};