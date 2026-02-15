#include "Assembler.h"

void Assembler_x86_64_Intel::visit_variable_assign_stmnt(const AssignStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_variable_decl_stmnt(const VariableDeclStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_function_call_stmnt(const FunctionCallStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_if_stmnt(const IfStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_for_stmnt(const ForStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_while_stmnt(const WhileStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_break_stmnt(const BreakStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_continue_stmnt(const ContinueStmnt &stmnt) {

}

void Assembler_x86_64_Intel::visit_return_stmnt(const ReturnStmnt &stmnt) {

}

Value Assembler_x86_64_Intel::visit_binary_expr(const BinaryExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_postfix_expr(const PostfixExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_unary_expr(const UnaryExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_identifier_expr(const IdentifierExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_set_literal_expr(const SetLiteralExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_array_literal_expr(const ArrayLiteralExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_string_expr(const StringExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_bool_expr(const BoolExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_double_expr(const DoubleExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_float_expr(const FloatExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_integer_expr(const IntegerExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_nil_expr(const NilExpr &expr) {
    return Value();
}

Value Assembler_x86_64_Intel::visit_function_call_expr(const FunctionCallExpr &expr) {
    return Value();
}

void Assembler_x86_64_Intel::visit_program(const ProgramDecl &program) {
    writer->write_ln("default rel");
    writer->write_ln("bits 64\n");
    writer->write_ln("section .text");
    writer->write_ln("global _start");
    writer->write_ln("_start:");
}

void Assembler_x86_64_Intel::visit_function_decl(const FunctionDecl &func) {
}







