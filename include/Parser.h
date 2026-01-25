#pragma once
#include <memory>
#include "Expr.h"
#include "Stmnt.h"
#include "Token.h"
#include "Tokenizer.h"

class Parser {
    Tokenizer tokenizer;
    // Statements
    std::unique_ptr<Stmnt> parse_variable_decl();
    std::unique_ptr<Stmnt> parse_assignment();
    // Expressions
    std::unique_ptr<Expr> parse_binary_expr();
    std::unique_ptr<Expr> parse_array_literal_expr();
    std::unique_ptr<Expr> parse_identifier(const Token& token);
    std::unique_ptr<Expr> parse_unary_expr(const Token& token);
    std::unique_ptr<Expr> parse_function_call_expr();

    std::vector<std::unique_ptr<Expr>> parse_expression_list(TokenType end_type);
    std::vector<std::unique_ptr<Expr>> parse_expression_list_and_consume(TokenType end_type, const std::string &end_name);

    void check_operator(const Token &token, const std::string& expected_op);
    void check_token_type(const Token &token, TokenType expected, const std::string& expected_message);
public:
    std::unique_ptr<Stmnt> parse_stmnt();
    std::unique_ptr<Expr> parse_expr();
    explicit Parser(Tokenizer tokenizer) : tokenizer(std::move(tokenizer)) {}
};
