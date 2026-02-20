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
        define_primitives();
    }

    void define_primitives() const;

    Value evaluate(const std::unique_ptr<Expr> &expr);
    void execute(const std::unique_ptr<Stmnt> &stmnt);
    void execute_stmnts(const std::vector<std::unique_ptr<Stmnt>>& stmnts);

    void execute_stmnt_in_new_env(const std::unique_ptr<Stmnt> &stmnt, const std::shared_ptr<Env> &new_env);
    void execute_stmnts_in_new_env(const std::vector<std::unique_ptr<Stmnt>>& stmnts, const std::shared_ptr<Env>& new_env);
    void execute_action_in_new_env(const std::function<void()> &action, const std::shared_ptr<Env> &new_env);

    Value visit_array_literal_expr(const ArrayLiteralExpr &expr) override;
    Value visit_set_literal_expr(const SetLiteralExpr &expr) override;
    Value visit_map_literal_expr(const MapLiteralExpr &expr) override;
    Value visit_postfix_expr(const PostfixExpr &expr) override;

    Value visit_identifier_expr(const IdentifierExpr &expr) override;
    Value visit_unary_expr(const UnaryExpr &expr) override;

    Value visit_binary_expr(const BinaryExpr &expr) override;
    Value evaluate_logical_expr(const BinaryExpr &expr);
    Value evaluate_addition(const BinaryExpr & expr);

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
