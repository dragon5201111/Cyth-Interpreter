#pragma once

#include <optional>
#include <unordered_map>
#include <vector>

#include "./Token.h"

class Tokenizer {
    const std::unordered_map<std::string, Token> fragment_map = {
        {"if", Token(TokenType::IF)},
        {"while", Token(TokenType::WHILE)},
        {"return", Token(TokenType::RETURN)},
        {"decl", Token(TokenType::DECL)},
        {"print", Token(TokenType::PRINT)},
        {"call", Token(TokenType::CALL)},
        {"func", Token(TokenType::FUNC)},
        {"true", Token(TokenType::TRUE)},
        {"false", Token(TokenType::FALSE)}
    };

    std::string input;
    std::string::size_type input_size;

    int current;
    std::optional<Token> cached;

    Token advance_current();
    Token get_string();
    Token get_number();
    Token get_identifier();
    Token match_operator(char current_char, char expected, const std::string &two_char);
public:
    explicit Tokenizer(std::string input) {
        this->input = std::move(input);
        input_size = this->input.size();
        current = 0;
    }

    Token peek();
    Token next();
    std::vector<Token> collect();
    void reset();
};
