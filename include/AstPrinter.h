#pragma once
#include "Expr.h"

class AstPrinter final : public ExprVisitor {
public:
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
};