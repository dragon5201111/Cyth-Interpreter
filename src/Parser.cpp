#include <functional>
#include <stdexcept>

#include "parser.h"
#include "Stmnt.h"
#include "Token.h"
#include "TokenType.h"
#include "Tokenizer.h"

std::unique_ptr<Stmnt> Parser::parse_stmnt() {
    switch (const Token token = tokenizer.next(); token.get_type()) {
        case TokenType::END_OF_FILE: throw std::runtime_error("No expression to parse, end of file.");
        case TokenType::DECL: return parse_variable_decl();
        case TokenType::IDENTIFIER: return parse_assignment();
        case TokenType::RETURN: return std::make_unique<ReturnStmnt>(parse_expr());
        case TokenType::IF: return parse_if();
        case TokenType::PRINT: return parse_print();
        default: throw std::runtime_error("Token " + token.to_string() + " is not a valid start of a statement.");
    }
}

std::unique_ptr<Stmnt> Parser::parse_variable_decl() {
    const auto identifier = tokenizer.next();
    check_token_type(identifier, TokenType::IDENTIFIER, "identifier");

    if (const Token next_token = tokenizer.peek(); next_token.get_type() == TokenType::OPERATOR) {
        check_operator(tokenizer.next(), "=");
        return std::make_unique<VariableDeclStmnt>(identifier.get_value(), parse_expr());
    }

    // Empty initializer
    return std::make_unique<VariableDeclStmnt>(identifier.get_value());
}

std::unique_ptr<Stmnt> Parser::parse_assignment() {
    std::unique_ptr<Expr> lhs = parse_identifier(tokenizer.last());
    check_operator(tokenizer.next(), "=");
    return std::make_unique<AssignStmnt>(std::move(lhs), parse_expr());
}

std::unique_ptr<Stmnt> Parser::parse_if() {
    check_token_type(tokenizer.next(), TokenType::LEFT_PAREN, "left parenthesis");
    std::unique_ptr<Expr> condition = parse_expr();
    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");

    std::vector<std::unique_ptr<Stmnt>> then_branch = parse_branch();

    std::vector<std::unique_ptr<Stmnt>> else_branch;
    if (tokenizer.peek().get_type() == TokenType::ELSE) {
        check_token_type(tokenizer.next(), TokenType::ELSE, "else");
        else_branch = std::move(parse_branch());
    }

    return std::make_unique<IfStmnt>(std::move(condition), std::move(then_branch), std::move(else_branch));
}

std::vector<std::unique_ptr<Stmnt>> Parser::parse_branch() {
    check_token_type(tokenizer.next(), TokenType::LEFT_BRACE, "left brace");

    std::vector<std::unique_ptr<Stmnt>> branch = parse_stmnts([this] {
        const Token token = tokenizer.peek();
        return token.get_type() != TokenType::RIGHT_BRACE;
    });

    check_token_type(tokenizer.next(), TokenType::RIGHT_BRACE, "right brace");
    return branch;
}

std::vector<std::unique_ptr<Stmnt>> Parser::parse_stmnts(
     const std::function<bool()>& should_continue) {
    std::vector<std::unique_ptr<Stmnt>> stmnts;
    while (should_continue()) {
        stmnts.push_back(parse_stmnt());
    }
    return stmnts;
}

std::unique_ptr<Stmnt> Parser::parse_print() {
    check_token_type(tokenizer.next(), TokenType::LEFT_PAREN, "left parenthesis");
    std::unique_ptr<Expr> expr = parse_expr();
    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");
    return std::make_unique<PrintStmnt>(std::move(expr));
}

std::unique_ptr<Expr> Parser::parse_expr() {
    switch (const Token& token = tokenizer.next(); token.get_type()) {
        case TokenType::END_OF_FILE: throw std::runtime_error("No expression to parse, end of file.");
        case TokenType::LEFT_PAREN: return parse_binary_expr();
        case TokenType::LEFT_BRACKET: return parse_array_literal_expr();
        case TokenType::NUMBER: return std::make_unique<ConstantExpr>(static_cast<uint64_t>(std::stoul(token.get_value())));
        case TokenType::TRUE: return std::make_unique<BoolExpr>(true);
        case TokenType::FALSE: return std::make_unique<BoolExpr>(false);
        case TokenType::STRING: return std::make_unique<StringExpr>(token.get_value());
        case TokenType::IDENTIFIER: return parse_identifier(token);
        case TokenType::NIL: return std::make_unique<NilExpr>();
        case TokenType::OPERATOR: return parse_unary_expr(token);
        case TokenType::CALL: return parse_function_call_expr();
        default: throw std::runtime_error("Token " + token.to_string() + " is not a valid start of an expression.");
    }
}

std::unique_ptr<Expr> Parser::parse_binary_expr() {
    std::unique_ptr<Expr> lhs = parse_expr();

    const Token op = tokenizer.next();
    check_token_type(op, TokenType::OPERATOR, "operator");

    std::unique_ptr<Expr> rhs = parse_expr();
    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");

    return std::make_unique<BinaryExpr>(std::move(lhs), op.get_value(), std::move(rhs));
}

std::unique_ptr<Expr> Parser::parse_array_literal_expr() {
    std::vector<std::unique_ptr<Expr>> expr_list = parse_expression_list_and_consume(TokenType::RIGHT_BRACKET, "right parenthesis");
    return std::make_unique<ArrayLiteralExpr>(std::move(expr_list));
}


std::unique_ptr<Expr> Parser::parse_identifier(const Token &token) {
    std::unique_ptr<Expr> expr = std::make_unique<IdentifierExpr>(token.get_value());

    while (tokenizer.peek().get_type() == TokenType::LEFT_BRACKET) {
        tokenizer.next();
        std::unique_ptr<Expr> index = parse_expr();
        check_token_type(tokenizer.next(), TokenType::RIGHT_BRACKET, "right bracket");
        expr = std::make_unique<ArrayAccessExpr>(std::move(expr), std::move(index));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::parse_unary_expr(const Token& token) {
    if (std::string op = token.get_value(); op == "!") {
        return std::make_unique<UnaryExpr>(op, parse_expr());
    }

    throw std::runtime_error("Token " + token.to_string() + " is not a valid start of an expression.");
}

std::unique_ptr<Expr> Parser::parse_function_call_expr() {
    const Token identifier = tokenizer.next();
    check_token_type(identifier, TokenType::IDENTIFIER, "identifier");
    check_token_type(tokenizer.next(), TokenType::LEFT_PAREN, "left parenthesis");

    std::vector<std::unique_ptr<Expr>> args = parse_expression_list_and_consume(TokenType::RIGHT_PAREN, "right parenthesis");
    return std::make_unique<FunctionCallExpr>(identifier.get_value(), std::move(args));
}


std::vector<std::unique_ptr<Expr>> Parser::parse_expression_list(const TokenType end_type) {
    std::vector<std::unique_ptr<Expr>> expr_list;

    if (tokenizer.peek().get_type() == end_type) {
        return expr_list;
    }

    expr_list.push_back(parse_expr());

    while (tokenizer.peek().get_type() == TokenType::COMMA) {
        tokenizer.next();
        expr_list.push_back(parse_expr());
    }

    return expr_list;
}

std::vector<std::unique_ptr<Expr>> Parser::parse_expression_list_and_consume(const TokenType end_type, const std::string &end_name) {
    auto expr_list = parse_expression_list(end_type);
    check_token_type(tokenizer.next(), end_type, end_name);
    return expr_list;
}


void Parser::check_operator(const Token &token, const std::string& expected_op) {
    if (token.get_value() != expected_op) {
        throw std::runtime_error("Expected operator " + expected_op + ", got " + token.get_value());
    }
}

void Parser::check_token_type(const Token &token, const TokenType expected, const std::string& expected_message) {
    if (token.get_type() != expected) {
        throw std::runtime_error("Expected " + expected_message + ", got " + token.to_string());
    }
}
