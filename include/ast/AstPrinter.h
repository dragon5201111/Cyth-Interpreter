#pragma once
#include "./Expr.h"
#include "Prog.h"
#include "./Stmnt.h"
#include "../io/Writer.h"

class AstPrinter final :
    public ExprVisitor,
    public StmntVisitor,
    public DeclVisitor{

    std::shared_ptr<Writer> writer;
public:
    explicit AstPrinter(std::shared_ptr<Writer> writer) : writer(std::move(writer)) {}

    Value visit_array_literal_expr(const ArrayLiteralExpr &expr) override;
    Value visit_set_literal_expr(const SetLiteralExpr &expr) override;
    Value visit_map_literal_expr(const MapLiteralExpr &expr) override;
    Value visit_postfix_expr(const PostfixExpr &expr) override;
    Value visit_identifier_expr(const IdentifierExpr &expr) override;
    Value visit_unary_expr(const UnaryExpr &expr) override;
    Value visit_binary_expr(const BinaryExpr &expr) override;
    Value visit_string_expr(const StringExpr &expr) override;
    Value visit_bool_expr(const BoolExpr &expr) override;
    Value visit_integer_expr(const IntegerExpr &expr) override;
    Value visit_double_expr(const DoubleExpr &expr) override;
    Value visit_float_expr(const FloatExpr &expr) override;
    Value visit_function_call_expr(const FunctionCallExpr &expr) override;
    Value visit_nil_expr(const NilExpr &expr) override;

    void visit_break_stmnt(const BreakStmnt &stmnt) override;
    void visit_continue_stmnt(const ContinueStmnt &stmnt) override;
    void visit_variable_decl_stmnt(const VariableDeclStmnt &stmnt) override;
    void visit_variable_assign_stmnt(const AssignStmnt &stmnt) override;
    void visit_return_stmnt(const ReturnStmnt &stmnt) override;
    void visit_if_stmnt(const IfStmnt &stmnt) override;
    void visit_while_stmnt(const WhileStmnt &stmnt) override;
    void visit_for_stmnt(const ForStmnt &stmnt) override;
    void visit_function_call_stmnt(const FunctionCallStmnt &stmnt) override;

    void visit_function_decl(const FunctionDecl &func) override;
    void visit_program(const ProgramDecl &program) override;
};
