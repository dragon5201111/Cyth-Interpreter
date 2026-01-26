#include "Interpreter.h"

#include <iostream>
#include <stdexcept>

Value Interpreter::evaluate(const std::unique_ptr<Expr>& expr) {
    return expr->accept(*this);
}

void Interpreter::execute(const std::unique_ptr<Stmnt> &stmnt) {
    stmnt->accept(*this);
}

Value Interpreter::visit_array_literal_expr(const ArrayLiteralExpr &expr) {
    std::vector<Value> values;
    values.reserve(expr.elements.size());

    for (const auto& e : expr.elements) {
        values.push_back(evaluate(e));
    }

    return Value(values);
}

Value Interpreter::visit_array_access_expr(const ArrayAccessExpr &expr) {
    throw std::runtime_error("Array access expr not implemented");
}

Value Interpreter::visit_identifier_expr(const IdentifierExpr &expr) {
    return local_env->get(expr.name);
}

Value Interpreter::visit_unary_expr(const UnaryExpr &expr) {
    throw std::runtime_error("Unary expr not implemented");
}

Value Interpreter::visit_binary_expr(const BinaryExpr &expr) {
    const Value lhs = evaluate(expr.lhs);
    const Value rhs = evaluate(expr.rhs);

    if (expr.op == "*") {
        return Value(lhs.as_number() * rhs.as_number());
    }

    if (expr.op == "/"){
        return Value(lhs.as_number() / rhs.as_number());
    }

    if (expr.op == "-") {
        return Value(lhs.as_number() - rhs.as_number());
    }

    if (expr.op == "&") {
        return Value(lhs.as_number() & rhs.as_number());
    }

    if (expr.op == "|") {
        return Value(lhs.as_number() | rhs.as_number());
    }

    if (expr.op == "%") {
        return Value(lhs.as_number() % rhs.as_number());
    }

    if (expr.op == "==") {
        return Value(lhs == rhs);
    }

    if (expr.op == "!=") {
        return Value(lhs != rhs);
    }

    if (expr.op == ">") {
        return Value(lhs.as_number() > rhs.as_number());
    }

    if (expr.op == "<") {
        return Value(lhs.as_number() < rhs.as_number());
    }

    if (expr.op == "<=") {
        return Value(lhs.as_number() <= rhs.as_number());
    }

    if (expr.op == ">=") {
        return Value(lhs.as_number() >= rhs.as_number());
    }

    if (expr.op == "&&" || expr.op == "||") {
        return evaluate_logical_expr(expr);
    }

    if (expr.op == "+") {
        return evaluate_addition(expr);
    }

    throw std::runtime_error("Unsupported operator");
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
    throw std::runtime_error("Function call expr not implemented");
}

Value Interpreter::visit_nil_expr(const NilExpr &expr) {
    return Value();
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

    // TODO: ADD SUPPORT FOR ARRAYS
    throw std::runtime_error("Assignment not implemented for statement");
}

void Interpreter::visit_return_stmnt(const ReturnStmnt &stmnt) {

}

void Interpreter::visit_if_stmnt(const IfStmnt &stmnt) {

}

void Interpreter::visit_while_stmnt(const WhileStmnt &stmnt) {

}

void Interpreter::visit_print_stmnt(const PrintStmnt &stmnt) {
    std::cout << evaluate(stmnt.expr);
}

void Interpreter::visit_function_decl(const FunctionDecl &func) {

}

void Interpreter::visit_program(const ProgramDecl &program) {
    for (const auto& func_decl : program.declarations) {
        func_decl->accept(*this);
    }

    for (const auto& stmnt : program.body) {
        execute(stmnt);
    }
}



