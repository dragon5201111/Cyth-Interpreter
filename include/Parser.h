#pragma once
#include <memory>
#include <functional>
#include "Expr.h"
#include "Prog.h"
#include "Stmnt.h"
#include "Token.h"
#include "Tokenizer.h"

class Parser {
    Tokenizer& tokenizer;
    // Statements
    std::unique_ptr<Stmnt> parse_variable_decl();
    std::unique_ptr<Stmnt> parse_assignment();

    std::unique_ptr<ReturnStmnt> parse_return();

    std::unique_ptr<Stmnt> parse_if();
    std::unique_ptr<Stmnt> parse_while();
    std::unique_ptr<Stmnt> parse_for();
    std::vector<std::unique_ptr<Stmnt>> parse_branch();
    std::vector<std::unique_ptr<Stmnt>> parse_stmnts(const std::function<bool()>& should_continue);

    std::vector<std::string> parse_identifiers(const std::function<bool()>& should_continue, const std::string& what);

    // Expressions
    std::unique_ptr<Expr> parse_binary_expr();
    std::unique_ptr<Expr> parse_array_literal_expr();
    std::unique_ptr<Expr> parse_set_literal_expr();
    std::unique_ptr<Expr> parse_map_literal_expr();

    std::unique_ptr<Expr> parse_identifier(const Token& token);
    std::unique_ptr<Expr> parse_unary_expr(const Token& token);
    std::unique_ptr<Expr> parse_function_call_expr();

    std::vector<std::unique_ptr<Expr>> parse_expression_list(TokenType end_type);
    std::vector<std::unique_ptr<Expr>> parse_expression_list_and_consume(TokenType end_type, const std::string &end_name);

    void check_operator(const Token &token, const std::string& expected_op);
    void check_token_type(const Token &token, TokenType expected, const std::string& expected_message);
public:
    std::unique_ptr<ProgramDecl> parse_program_decl();
    std::unique_ptr<FunctionDecl> parse_function_decl();
    std::unique_ptr<Stmnt> parse_stmnt();
    std::unique_ptr<Expr> parse_expr();
    explicit Parser(Tokenizer&  tokenizer) : tokenizer(tokenizer) {}
};
