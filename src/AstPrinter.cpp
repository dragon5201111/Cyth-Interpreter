#include "AstPrinter.h"

#include <iostream>

Value AstPrinter::visit_array_literal_expr(const ArrayLiteralExpr &expr) {
   writer->write("[");
    for (const auto& e: expr.elements) {
        e->accept(*this);
        writer->write(",");
    }
    writer->write("]");
    return Value();
}

Value AstPrinter::visit_array_access_expr(const ArrayAccessExpr &expr) {
    expr.array->accept(*this);
    writer->write("[");
    expr.index->accept(*this);
    writer->write("]");
    return Value();
}

Value AstPrinter::visit_identifier_expr(const IdentifierExpr &expr) {
    writer->write(expr.name);
    return Value();
}

Value AstPrinter::visit_unary_expr(const UnaryExpr &expr) {
   writer->write(expr.op);
    expr.rhs->accept(*this);
    return Value();
}

Value AstPrinter::visit_binary_expr(const BinaryExpr &expr) {
    writer->write("(");
    expr.lhs->accept(*this);
    writer->write(" " + expr.op + " ");
    expr.rhs->accept(*this);
    writer->write(")");
    return Value();
}

Value AstPrinter::visit_string_expr(const StringExpr &expr) {
    return Value();
}

Value AstPrinter::visit_bool_expr(const BoolExpr &expr) {
    writer->write(expr.value ? "true" : "false");
    return Value();
}

Value AstPrinter::visit_constant_expr(const ConstantExpr &expr) {
    writer->write(std::to_string(expr.value));
    return Value();
}

Value AstPrinter::visit_function_call_expr(const FunctionCallExpr &expr) {
   writer->write("call " + expr.name + "(");
    for (const auto& e : expr.args) {
        e->accept(*this);
        writer->write(",");
    }
    writer->write(")");
    return Value();
}

Value AstPrinter::visit_nil_expr(const NilExpr &expr) {
   writer->write("nil");
    return Value();
}

void AstPrinter::visit_variable_decl_stmnt(const VariableDeclStmnt &stmnt) {
    writer->write("decl " + stmnt.name);
    if (stmnt.initializer) {
       writer->write(" = ");
        stmnt.initializer->accept(*this);
    }
}

void AstPrinter::visit_variable_assign_stmnt(const AssignStmnt &stmnt) {
    stmnt.lhs->accept(*this);
    writer->write(" = ");
    stmnt.rhs->accept(*this);
}

void AstPrinter::visit_return_stmnt(const ReturnStmnt &stmnt) {
    writer->write("return ");
    stmnt.value->accept(*this);
}

void AstPrinter::visit_if_stmnt(const IfStmnt &stmnt) {
    writer->write("if (");
    stmnt.condition->accept(*this);
    writer->write("){");
    for (const auto& s : stmnt.then_branch) {
        writer->write("\n");
        s->accept(*this);
    }
    writer->write("\n}");
    std::cout << "else{" << std::endl;
    for (const auto& s : stmnt.else_branch) {
        s->accept(*this);
        writer->write("\n");
    }
    std::cout << "}" << std::endl;
}

void AstPrinter::visit_while_stmnt(const WhileStmnt &stmnt) {
    writer->write("while (");
    stmnt.condition->accept(*this);
    writer->write("){\n");
    for (const auto& s : stmnt.body) {
        s->accept(*this);
        writer->write("\n");
    }
    writer->write("}");
}

void AstPrinter::visit_print_stmnt(const PrintStmnt &stmnt) {
    writer->write("print(");
    stmnt.expr->accept(*this);
    writer->write(")");
}

void AstPrinter::visit_function_decl(const FunctionDecl &func) {
    writer->write("func " + func.name + "(");
    for (const auto& param : func.parameters) {
        writer->write(param + ",");
    }
    writer->write("){\n");
    for (const auto& stmnt : func.body) {
        stmnt->accept(*this);
        writer->write("\n");
    }
    writer->write("}");
}

void AstPrinter::visit_program(const ProgramDecl &program) {
    for (const auto& func_decl : program.declarations) {
        func_decl->accept(*this);
        writer->write("\n");
    }

    writer->write("main {\n");
    for (const auto& stmnt : program.body) {
        stmnt->accept(*this);
        writer->write("\n");
    }
    writer->write("}\n");
}

void AstPrinter::visit_function_call_stmnt(const FunctionCallStmnt &stmnt) {
    stmnt.function_call_expr->accept(*this);
}
