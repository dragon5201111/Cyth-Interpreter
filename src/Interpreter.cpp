#include "Interpreter.h"
#include <iostream>
#include <stack>
#include <stdexcept>
#include "Builtin.h"
#include "Call.h"

void Interpreter::define_primitives() const {
    for (const auto& [name, function] : Builtins::primitive_functions) {
        local_env->define(name, function);
    }

    for (const auto& [name, value] : Builtins::primitive_values) {
        local_env->define(name, value);
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

void Interpreter::execute_in_new_env(const std::vector<std::unique_ptr<Stmnt> > &stmnts, const std::shared_ptr<Env>& new_env) {
    const std::shared_ptr<Env> previous_env = local_env;
    local_env = new_env;
    try {
        execute_stmnts(stmnts);
    }catch (ReturnException& _) {
        local_env = previous_env;
        throw;
    }
    local_env = previous_env;
}

Value Interpreter::visit_array_literal_expr(const ArrayLiteralExpr &expr) {
    std::deque<Value> values;

    for (const auto& e : expr.elements) {
        values.push_back(evaluate(e));
    }

    return Value(values);
}

Value Interpreter::visit_array_access_expr(const ArrayAccessExpr &expr) {
    const Value base = evaluate(expr.array);

    const auto& array = base.as_array();
    const uint64_t index = evaluate(expr.index).as_number();

    if (index >= array.size()) {
        throw std::runtime_error("Index out of bounds");
    }

    return array[index];
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

    if (expr.op == "*") {return Value(lhs.as_number() * rhs.as_number());}
    if (expr.op == "/") return Value(lhs.as_number() / rhs.as_number());
    if (expr.op == "-") return Value(lhs.as_number() - rhs.as_number());
    if (expr.op == "%") return Value(lhs.as_number() % rhs.as_number());
    if (expr.op == "==") return Value(lhs == rhs);
    if (expr.op == "!=") return Value(lhs != rhs);
    if (expr.op == "<")  return Value(lhs.as_number() < rhs.as_number());
    if (expr.op == "<=") return Value(lhs.as_number() <= rhs.as_number());
    if (expr.op == ">")  return Value(lhs.as_number() > rhs.as_number());
    if (expr.op == ">=") return Value(lhs.as_number() >= rhs.as_number());
    if (expr.op == "&")  return Value(lhs.as_number() & rhs.as_number());
    if (expr.op == "|")  return Value(lhs.as_number() | rhs.as_number());
    if (expr.op == "^")  return Value(lhs.as_number() ^ rhs.as_number());
    if (expr.op == "<<") return Value(lhs.as_number() << rhs.as_number());
    if (expr.op == ">>") return Value(lhs.as_number() >> rhs.as_number());

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

Value Interpreter::visit_constant_expr(const ConstantExpr &expr) {
    return Value(expr.value);
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

void Interpreter::visit_variable_decl_stmnt(const VariableDeclStmnt &stmnt) {
    Value value = stmnt.initializer ? evaluate(stmnt.initializer) : Value();
    local_env->define(stmnt.name, std::move(value));
}

void Interpreter::visit_variable_assign_stmnt(const AssignStmnt &stmnt) {
    Value value = evaluate(stmnt.rhs);

    if (const auto identifier = dynamic_cast<const IdentifierExpr*>(stmnt.lhs.get())) {
        local_env->assign(identifier->name, std::move(value));
        return;
    }

    auto parent = dynamic_cast<ArrayAccessExpr*>(stmnt.lhs.get());
    std::deque<uint64_t> indices;
    while (const auto current = dynamic_cast<ArrayAccessExpr*>(parent->array.get())) {
        indices.push_front(evaluate(parent->index).as_number());
        parent = current;
    }

    indices.push_front(evaluate(parent->index).as_number());
    const auto identifier = dynamic_cast<IdentifierExpr*>(parent->array.get());
    Value* array = &std::get<Value>(local_env->get(identifier->name));

    for (size_t i = 1; i < indices.size(); ++i) {
        array = &array->as_array()[indices.front()];
        indices.pop_front();
    }

    array->as_array()[indices.front()] = std::move(value);
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
            execute_stmnts(stmnt.body);
        }catch (BreakException& _) {
            break;
        }
    }
}

void Interpreter::visit_function_call_stmnt(const FunctionCallStmnt &stmnt) {
    evaluate(stmnt.function_call_expr);
}

void Interpreter::visit_function_decl(const FunctionDecl &func) {
    local_env.get()->define(func.name, std::make_shared<UserFunction>(local_env, func));
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



