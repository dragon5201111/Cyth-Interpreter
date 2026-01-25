#pragma once

enum class TokenType {
    // Keywords
    IF,
    ELSE,
    WHILE,
    RETURN,
    DECL,
    PRINT,
    CALL,
    FUNC,
    TRUE,
    FALSE,
    NIL,
    MAIN,

    // Types
    NUMBER,
    STRING,
    IDENTIFIER,

    // Operators
    OPERATOR,

    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    END_OF_FILE,
};