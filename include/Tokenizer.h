#pragma once

#include <optional>
#include <unordered_map>
#include <vector>

#include "./Token.h"

class Tokenizer {
    const std::unordered_map<std::string, TokenType> fragment_map = {
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"while", TokenType::WHILE},
        {"return", TokenType::RETURN},
        {"decl", TokenType::DECL},
        {"call", TokenType::CALL},
        {"func", TokenType::FUNC},
        {"true", TokenType::TRUE},
        {"false", TokenType::FALSE},
        {"nil", TokenType::NIL},
        {"main", TokenType::MAIN}
    };

    std::string input;
    std::string::size_type input_size;

    int current;
    int current_line;
    std::optional<Token> cached;
    std::optional<Token> previous;

    Token advance_current();
    void skip_whitespace();
    Token get_string();
    Token get_number();
    Token get_identifier();
    Token match_operator(char current_char, char expected, const std::string &two_char);
public:
    explicit Tokenizer(std::string input) {
        this->input = std::move(input);
        input_size = this->input.size();
        current = 0;
        current_line = 1;
    }

    Token last();
    Token peek();
    Token next();
    std::vector<Token> collect();
    void reset();
};
