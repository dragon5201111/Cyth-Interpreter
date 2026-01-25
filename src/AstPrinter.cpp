#include "AstPrinter.h"

#include <iostream>

Value AstPrinter::visit_array_literal_expr(const ArrayLiteralExpr &expr) {
    std::cout << "[";
    for (const auto& e: expr.elements) {
        e->accept(*this);
        std::cout << ",";
    }
    std::cout << "]";
    return Value();
}

Value AstPrinter::visit_array_access_expr(const ArrayAccessExpr &expr) {
    expr.array->accept(*this);
    std::cout << "[";
    expr.index->accept(*this);
    std::cout << "]";
    return Value();
}

Value AstPrinter::visit_identifier_expr(const IdentifierExpr &expr) {
    std::cout << expr.name;
    return Value();
}

Value AstPrinter::visit_unary_expr(const UnaryExpr &expr) {
    std::cout << expr.op;
    expr.rhs->accept(*this);
    return Value();
}

Value AstPrinter::visit_binary_expr(const BinaryExpr &expr) {
    std::cout << "(";
    expr.lhs->accept(*this);
    std::cout << " " + expr.op + " ";
    expr.rhs->accept(*this);
    std::cout << ")";
    return Value();
}

Value AstPrinter::visit_string_expr(const StringExpr &expr) {
    return Value();
}

Value AstPrinter::visit_bool_expr(const BoolExpr &expr) {
    std::cout << (expr.value ? "true" : "false");
    return Value();
}

Value AstPrinter::visit_constant_expr(const ConstantExpr &expr) {
    std::cout << std::to_string(expr.value);
    return Value();
}

Value AstPrinter::visit_function_call_expr(const FunctionCallExpr &expr) {
    std::cout << "call " + expr.name + "(";
    for (const auto& e : expr.args) {
        e->accept(*this);
        std::cout << ",";
    }
    std::cout << ")";
    return Value();
}

Value AstPrinter::visit_nil_expr(const NilExpr &expr) {
    std::cout << "nil";
    return Value();
}
