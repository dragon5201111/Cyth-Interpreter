#pragma once

#include <string>

#include "Print.h"
#include "TokenType.h"

class Token : public Printable {
    TokenType type;
    std::string value;
public:
    explicit Token (const TokenType type) : type(type) {}
    explicit Token (const TokenType type, std::string value) : type(type), value(std::move(value)) {}

    [[nodiscard]] std::string get_value() const { return value; }
    [[nodiscard]] TokenType get_type() const { return type; }

    [[nodiscard]] std::string to_string() const override {
        std::string string_rep;
        switch (type) {
            case TokenType::IF: string_rep = "IF"; break;
            case TokenType::WHILE: string_rep = "WHILE"; break;
            case TokenType::RETURN: string_rep = "RETURN"; break;
            case TokenType::DECL: string_rep = "DECL"; break;
            case TokenType::PRINT: string_rep = "PRINT"; break;
            case TokenType::CALL: string_rep = "CALL"; break;
            case TokenType::FUNC: string_rep = "FUNC"; break;
            case TokenType::TRUE: string_rep = "TRUE"; break;
            case TokenType::FALSE: string_rep = "FALSE"; break;
            case TokenType::NUMBER: string_rep = "NUMBER"; break;
            case TokenType::STRING: string_rep = "STRING"; break;
            case TokenType::IDENTIFIER: string_rep = "IDENTIFIER"; break;
            case TokenType::ASSIGN: string_rep = "ASSIGN"; break;
            case TokenType::OPERATOR: string_rep = "OPERATOR"; break;
            case TokenType::LEFT_PAREN: string_rep = "LEFT_PAREN"; break;
            case TokenType::RIGHT_PAREN: string_rep = "RIGHT_PAREN"; break;
            case TokenType::LEFT_BRACE: string_rep = "LEFT_BRACE"; break;
            case TokenType::RIGHT_BRACE: string_rep = "RIGHT_BRACE"; break;
            case TokenType::COMMA: string_rep = "COMMA"; break;
            case TokenType::END_OF_FILE: string_rep = "END_OF_FILE"; break;
            default: string_rep = "UNKNOWN";
        }
        return "TYPE:" + string_rep + " [value=\"" + value + "\"]";
    }
};
