#include "Interpreter.h"

#include <stdexcept>

Value Interpreter::evaluate(const std::unique_ptr<Expr>& expr) {
    return expr->accept(*this);
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
    throw std::runtime_error("Identifier expr not implemented");
}

Value Interpreter::visit_unary_expr(const UnaryExpr &expr) {
    throw std::runtime_error("Unary expr not implemented");
}

Value Interpreter::visit_binary_expr(const BinaryExpr &expr) {
    throw std::runtime_error("Binary expr not implemented");
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

}

void Interpreter::visit_variable_assign_stmnt(const AssignStmnt &stmnt) {

}

void Interpreter::visit_return_stmnt(const ReturnStmnt &stmnt) {

}

void Interpreter::visit_if_stmnt(const IfStmnt &stmnt) {

}

void Interpreter::visit_while_stmnt(const WhileStmnt &stmnt) {

}

void Interpreter::visit_print_stmnt(const PrintStmnt &stmnt) {

}




