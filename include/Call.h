#pragma once
#include <functional>
#include <utility>
#include "Expr.h"
#include "Prog.h"

class Interpreter;
class Env;

class Callable {
    size_t arity;
public:
    static constexpr size_t VARIABLE_ARITY = 0;

    explicit Callable(const size_t arity) : arity(arity) {}
    virtual ~Callable() = default;
    virtual Value call(Interpreter& interpreter, const std::vector<Value>& args) = 0;

    void check_arity(const std::vector<Value>& args) const {
        if (const auto args_size = args.size(); arity != VARIABLE_ARITY && arity != args_size) {
            throw std::runtime_error("Arity mismatch. Expected " + std::to_string(arity) + " arg(s) got, " + std::to_string(args_size));
        }
    }
};

class UserFunction final : public Callable {
    std::weak_ptr<Env> enclosing_env; // Avoid circular references
    const FunctionDecl& function_decl;

public:
    explicit UserFunction(const size_t arity, const std::shared_ptr<Env>& enclosing_env, const FunctionDecl& function_decl)
        : Callable(arity), enclosing_env(enclosing_env), function_decl(function_decl) {}

    Value call(Interpreter& interpreter, const std::vector<Value>& args) override;
};


class PrimitiveFunction final : public Callable {
    std::function<Value(const std::vector<Value>&)> function;
public:
    explicit PrimitiveFunction(const size_t arity, std::function<Value(const std::vector<Value>&)> function) : Callable(arity), function(std::move(function)) {}
    Value call(Interpreter& interpreter, const std::vector<Value>& args) override {
        check_arity(args);
        return function(args);
    }
};