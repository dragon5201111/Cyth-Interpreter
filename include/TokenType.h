#pragma once

enum class TokenType {
    // Keywords
    IF,
    ELSE,
    WHILE,
    FOR,
    BREAK,
    CONTINUE,
    RETURN,
    DECL,
    CALL,
    FUNC,
    TRUE,
    FALSE,
    NIL,
    MAIN,

    // Types
    INTEGER,
    DOUBLE,
    HEX,
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