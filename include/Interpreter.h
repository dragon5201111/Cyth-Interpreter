#pragma once
#include "Env.h"
#include "Prog.h"
#include "Stmnt.h"

class Interpreter :
        public ExprVisitor,
        public StmntVisitor,
        public  DeclVisitor{
    std::shared_ptr<Env> global_env;
    std::shared_ptr<Env> local_env;
public:
    explicit Interpreter() {
        global_env = std::make_shared<Env>();
        local_env = global_env;
    }

    Value evaluate(const std::unique_ptr<Expr> &expr);
    void execute(const std::unique_ptr<Stmnt> &stmnt);

    Value visit_array_literal_expr(const ArrayLiteralExpr &expr) override;
    Value visit_array_access_expr(const ArrayAccessExpr &expr) override;
    Value visit_identifier_expr(const IdentifierExpr &expr) override;
    Value visit_unary_expr(const UnaryExpr &expr) override;
    Value visit_binary_expr(const BinaryExpr &expr) override;
    Value visit_string_expr(const StringExpr &expr) override;
    Value visit_bool_expr(const BoolExpr &expr) override;
    Value visit_constant_expr(const ConstantExpr &expr) override;
    Value visit_function_call_expr(const FunctionCallExpr &expr) override;
    Value visit_nil_expr(const NilExpr &expr) override;

    void visit_variable_decl_stmnt(const VariableDeclStmnt &stmnt) override;
    void visit_variable_assign_stmnt(const AssignStmnt &stmnt) override;
    void visit_return_stmnt(const ReturnStmnt &stmnt) override;
    void visit_if_stmnt(const IfStmnt &stmnt) override;
    void visit_while_stmnt(const WhileStmnt &stmnt) override;
    void visit_print_stmnt(const PrintStmnt &stmnt) override;

    void visit_function_decl(const FunctionDecl &func) override;
    void visit_program(const ProgramDecl &program) override;
};
