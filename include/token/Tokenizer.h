#pragma once

#include <optional>
#include <regex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "./Token.h"

class Tokenizer {
    const std::string SINGLE_LINE_COMMENT = "#";
    const std::string MULTI_LINE_COMMENT_BEGIN = "/*";
    const std::string MULTI_LINE_COMMENT_END = "*/";

    std::regex INTEGER_PATTERN = std::regex(R"([0-9]+)");
    std::regex DOUBLE_PATTERN = std::regex(R"([0-9]+\.[0-9]*)");
    std::regex FLOAT_PATTERN = std::regex(R"([0-9]+\.[0-9]*[fF])");
    std::regex HEX_PATTERN = std::regex(R"(0[xX][0-9a-fA-F]*)");

    const std::unordered_map<std::string, TokenType> FRAGMENT_MAP = {
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"while", TokenType::WHILE},
        {"for", TokenType::FOR},
        {"break", TokenType::BREAK},
        {"continue", TokenType::CONTINUE},
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
    std::string::size_type input_size{};

    int current{};
    int current_line{};
    std::optional<Token> cached;
    std::optional<Token> previous;

    Token advance_current();
    void skip_whitespace();
    bool input_has_substr(int pos, const std::string &substr) const;
    Token get_string();
    Token get_number();
    bool char_in_number(char c);

    Token get_identifier();
    Token match_operator(const std::string& current_char, const std::vector<std::string> &expected, const std::vector<std::string> &match);
    bool match_next(const std::string&) const;
public:
    explicit Tokenizer(std::string input = {}) {
        reset(std::move(input));
    }

    Token last();
    Token peek();
    Token next();

    void reset(std::string source); // Initializes all fields
    std::string get_input();
};
