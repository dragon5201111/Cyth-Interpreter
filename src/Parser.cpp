#include <stdexcept>

#include "parser.h"
#include "Token.h"
#include "TokenType.h"
#include "Tokenizer.h"

std::unique_ptr<Expr> Parser::parse_expr() {
    switch (const Token& token = tokenizer.next(); token.get_type()) {
        case TokenType::END_OF_FILE: throw std::runtime_error("No expression to parse, end of file.");
        case TokenType::LEFT_PAREN: return parse_binary_expr();
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

    std::vector<std::unique_ptr<Expr>> args;
    if (tokenizer.peek().get_type() != TokenType::RIGHT_PAREN) {
        args.push_back(parse_expr());

        while (tokenizer.peek().get_type() == TokenType::COMMA) {
            tokenizer.next();
            args.push_back(parse_expr());
        }
    }

    // Consume right parenthesis
    check_token_type(tokenizer.next(), TokenType::RIGHT_PAREN, "right parenthesis");
    return std::make_unique<FunctionCallExpr>(identifier.get_value(), std::move(args));
}

void Parser::check_token_type(const Token &token, const TokenType expected, const std::string& expected_message) {
    if (token.get_type() != expected) {
        throw std::runtime_error("Expected " + expected_message + ", got " + token.to_string());
    }
}
