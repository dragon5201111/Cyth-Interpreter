#include "../../include/interpreter/Interpreter.h"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <vector>
#include "../../include/interpreter/Builtin.h"
#include "../../include/interpreter/Call.h"
#include "../../include/interpreter/Except.h"
#include "../../include/value/Container.h"

void Interpreter::define_primitives() const {
    for (const auto& [name, function] : Builtins::primitive_functions) {
        local_env->bind(name, function);
    }

    for (const auto& [name, value] : Builtins::primitive_values) {
        local_env->bind(name, value);
    }
}

Value Interpreter::evaluate(const std::unique_ptr<Expr>& expr) {
    return expr->accept(*this);
}

void Interpreter::execute(const std::unique_ptr<Stmnt> &stmnt) {
    stmnt->accept(*this);
}

void Interpreter::execute_stmnts(const std::vector<std::unique_ptr<Stmnt>>& stmnts) {
    for (const auto& stmnt : stmnts) {
        execute(stmnt);
    }
}

void Interpreter::execute_stmnt_in_new_env(const std::unique_ptr<Stmnt> &stmnt, const std::shared_ptr<Env>& new_env) {
    execute_action_in_new_env([&stmnt, this] {
       if (stmnt) {
           execute(stmnt);
       }
   }, new_env);
}

void Interpreter::execute_stmnts_in_new_env(const std::vector<std::unique_ptr<Stmnt>> &stmnts, const std::shared_ptr<Env>& new_env) {
    execute_action_in_new_env([&stmnts, this] {
        execute_stmnts(stmnts);
    }, new_env);
}

void Interpreter::execute_action_in_new_env(const std::function<void()>& action, const std::shared_ptr<Env>& new_env) {
    const std::shared_ptr<Env> previous_env = local_env;
    local_env = new_env;
    try {
        action();
    }catch (...) {
        local_env = previous_env;
        std::rethrow_exception(std::current_exception());
    }
    local_env = previous_env;
}

Value Interpreter::visit_array_literal_expr(const ArrayLiteralExpr &expr) {
    std::deque<Value> values;
    for (const auto& e : expr.elements) {
        values.push_back(evaluate(e));
    }
    return Value(std::make_shared<ArrayContainer>(values));
}

Value Interpreter::visit_set_literal_expr(const SetLiteralExpr &expr) {
    std::set<Value> values;
    for (const auto& e : expr.elements) {
        values.insert(evaluate(e));
    }
    return Value(std::make_shared<SetContainer>(values));
}

Value Interpreter::visit_map_literal_expr(const MapLiteralExpr &expr) {
    std::map<Value, Value> values;
    for (const auto& [e1, e2] : expr.elements) {
        values[evaluate(e1)] = evaluate(e2);
    }

    return Value(std::make_shared<MapContainer>(values));
}

Value Interpreter::visit_postfix_expr(const PostfixExpr &expr) {
    Value lhs = evaluate(expr.lhs);
    const Value rhs = evaluate(expr.rhs);

    if (lhs.is_container()) {
        return (*lhs.as_container())[rhs];
    }

    if (lhs.is_string()) {
        return Value(std::string(1, lhs.as_string()[static_cast<int64_t>(rhs.as_number())]));
    }

    throw std::runtime_error("Unsupported postfix.");
}

Value Interpreter::visit_identifier_expr(const IdentifierExpr &expr) {
    return std::get<Value>(local_env->get(expr.name));
}

Value Interpreter::visit_unary_expr(const UnaryExpr &expr) {
    if (expr.op == "!") {
        return Value(!evaluate(expr.rhs).is_truthy());
    }

    if (expr.op == "-") {
        return Value(-evaluate(expr.rhs).as_number());
    }

    if (expr.op == "~") {
        return Value(~evaluate(expr.rhs).as_number());
    }

    throw std::runtime_error("Unsupported unary operator");
}

Value Interpreter::visit_binary_expr(const BinaryExpr &expr) {
    if (expr.op == "&&" || expr.op == "||") {
        return evaluate_logical_expr(expr);
    }

    if (expr.op == "+") {
        return evaluate_addition(expr);
    }

    const Value lhs = evaluate(expr.lhs);
    const Value rhs = evaluate(expr.rhs);

    // Number operations
    if (expr.op == "*") {return Value(lhs.as_number() * rhs.as_number());}
    if (expr.op == "/") return Value(lhs.as_number() / rhs.as_number());
    if (expr.op == "-") return Value(lhs.as_number() - rhs.as_number());
    if (expr.op == "%") return Value(lhs.as_number() % rhs.as_number());
    if (expr.op == "&")  return Value(lhs.as_number() & rhs.as_number());
    if (expr.op == "|")  return Value(lhs.as_number() | rhs.as_number());
    if (expr.op == "^")  return Value(lhs.as_number() ^ rhs.as_number());
    if (expr.op == "<<") return Value(lhs.as_number() << rhs.as_number());
    if (expr.op == ">>") return Value(lhs.as_number() >> rhs.as_number());

    // General operations
    if (expr.op == "==") return Value(lhs == rhs);
    if (expr.op == "!=") return Value(lhs != rhs);
    if (expr.op == "<")  return Value(lhs < rhs);
    if (expr.op == "<=") return Value(lhs <= rhs);
    if (expr.op == ">")  return Value(lhs > rhs);
    if (expr.op == ">=") return Value(lhs >= rhs);

    throw std::runtime_error("Unsupported binary operator");
}

Value Interpreter::evaluate_logical_expr(const BinaryExpr &expr) {
    const Value lhs = evaluate(expr.lhs);
    if (expr.op == "||") {
        // Short-circuit
        if (lhs.is_truthy()) {
            return Value(true);
        }
        return Value(evaluate(expr.rhs).is_truthy());
    }

    // Is a logical AND
    if (!lhs.is_truthy()) {
        return Value(false); // Short-circuit
    }

    return Value(evaluate(expr.rhs).is_truthy());
}

Value Interpreter::evaluate_addition(const BinaryExpr &expr) {
    const Value lhs = evaluate(expr.lhs);
    const Value rhs = evaluate(expr.rhs);

    if (lhs.is_number() && rhs.is_number()) {
        return Value(lhs.as_number() + rhs.as_number());
    }

    if (lhs.is_string() && rhs.is_string()) {
        return Value(lhs.as_string() + rhs.as_string());
    }

    throw std::runtime_error("Unsupported operator between types");
}


Value Interpreter::visit_string_expr(const StringExpr &expr) {
    return Value(expr.value);
}

Value Interpreter::visit_bool_expr(const BoolExpr &expr) {
    return Value(expr.value);
}

Value Interpreter::visit_integer_expr(const IntegerExpr &expr) {
    return Value(Number(expr.value));
}

Value Interpreter::visit_double_expr(const DoubleExpr &expr) {
    return Value(Number(expr.value));
}

Value Interpreter::visit_float_expr(const FloatExpr &expr) {
    return Value(Number(expr.value));
}

Value Interpreter::visit_function_call_expr(const FunctionCallExpr &expr) {
    std::vector<Value> args;
    args.reserve(expr.args.size());
    for (const auto &arg : expr.args) {
        args.push_back(evaluate(arg));
    }

    const auto callable = std::get<std::shared_ptr<Callable>>(local_env->get(expr.name));
    return callable->call(*this, args);
}

Value Interpreter::visit_nil_expr(const NilExpr &expr) {
    return Value();
}

void Interpreter::visit_break_stmnt(const BreakStmnt &stmnt) {
    throw BreakException();
}

void Interpreter::visit_continue_stmnt(const ContinueStmnt &stmnt) {
    throw ContinueException();
}

void Interpreter::visit_variable_decl_stmnt(const VariableDeclStmnt &stmnt) {
    if (local_env->is_bound(stmnt.name, 0)) {
        throw std::runtime_error("Cannot define bound variable " + stmnt.name + "; redefinition of previous declaration");
    }

    Value value = stmnt.initializer ? evaluate(stmnt.initializer) : Value();
    local_env->bind(stmnt.name, std::move(value));
}

void Interpreter::visit_variable_assign_stmnt(const AssignStmnt &stmnt) {
    if (const auto identifier = dynamic_cast<IdentifierExpr*>(stmnt.lhs.get())) {
        local_env->rebind(identifier->name, evaluate(stmnt.rhs));
        return;
    }

    if (const auto postfix = dynamic_cast<PostfixExpr*>(stmnt.lhs.get())) {
        auto lhs = evaluate(postfix->lhs);
        const Value rhs = evaluate(postfix->rhs);

        Value value = evaluate(stmnt.rhs);
        if (lhs.is_string()) {
            lhs.as_string()[static_cast<int64_t>(rhs.as_number())] = value.as_string()[0];
        }
        else if (lhs.is_container()) {
            (*lhs.as_container())[rhs] = value;
        }
        else {
            throw std::runtime_error("Value is not subscriptable");
        }
    }
}

void Interpreter::visit_return_stmnt(const ReturnStmnt &stmnt) {
    throw ReturnException(evaluate(stmnt.value));
}

void Interpreter::visit_if_stmnt(const IfStmnt &stmnt) {
    if (evaluate(stmnt.condition).is_truthy()) {
        execute_stmnts(stmnt.then_branch);
    }else {
        execute_stmnts(stmnt.else_branch);
    }
}

void Interpreter::visit_while_stmnt(const WhileStmnt &stmnt) {
    while (evaluate(stmnt.condition).is_truthy()) {
        try {
            execute_stmnts_in_new_env(stmnt.body, std::make_shared<Env>(local_env));
        }catch (BreakException& _) {
            break;
        }catch (ContinueException& _) {
            // Do nothing
        }
    }
}

void Interpreter::visit_for_stmnt(const ForStmnt &stmnt) {
    const auto new_env = std::make_shared<Env>(local_env);
    execute_stmnt_in_new_env(stmnt.initializer, new_env);

    execute_action_in_new_env([&stmnt, &new_env, this] {
        while (evaluate(stmnt.condition).is_truthy()) {
            try {
                execute_stmnts_in_new_env(stmnt.body, std::make_shared<Env>(new_env)); // Execute in new env because a stmnt may try to declare a variable with same binding as initializer
                execute_stmnt_in_new_env(stmnt.assignment, new_env);
            }catch (BreakException& _) {
                break;
            }catch (ContinueException& _) {
                execute_stmnt_in_new_env(stmnt.assignment, new_env);
            }
        }
    }, new_env);
}

void Interpreter::visit_function_call_stmnt(const FunctionCallStmnt &stmnt) {
    evaluate(stmnt.function_call_expr);
}

void Interpreter::visit_function_decl(const FunctionDecl &func) {
    // Overwrite any existing functions; bind to the newest function declaration
    local_env->bind(func.name, std::make_shared<UserFunction>(func.parameters.size(),local_env, func));
}

void Interpreter::visit_program(const ProgramDecl &program) {
    for (const auto& func_decl : program.declarations) {
        func_decl->accept(*this);
    }

    try {
        execute_stmnts(program.body);
    }catch (ReturnException& return_exception) {
        if (!return_exception.value.is_number()) {
            throw std::runtime_error("Attempt to return from main with non-number.");
        }

        exit(static_cast<int>(return_exception.value.as_number()));
    }

    exit(EXIT_SUCCESS);
}



