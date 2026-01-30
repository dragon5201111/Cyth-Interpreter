#pragma once

#include <string>

#include "Print.h"
#include "TokenType.h"

class Token : public Printable {
    TokenType type;
    std::string value;
    int line_number;
public:
    explicit Token (const TokenType type, const int line_number) : type(type), line_number(line_number) {}
    explicit Token (const TokenType type, std::string value, const int line_number) : type(type), value(std::move(value)), line_number(line_number) {}

    [[nodiscard]] std::string get_value() const { return value; }
    [[nodiscard]] TokenType get_type() const { return type; }
    [[nodiscard]] int get_line_number() const { return line_number; }

    [[nodiscard]] std::string to_string() const override {
        std::string string_rep;
        switch (type) {
            case TokenType::IF: string_rep = "IF"; break;
            case TokenType::ELSE: string_rep = "ELSE"; break;
            case TokenType::WHILE: string_rep = "WHILE"; break;
            case TokenType::FOR: string_rep = "FOR"; break;
            case TokenType::BREAK: string_rep = "BREAK"; break;
            case TokenType::RETURN: string_rep = "RETURN"; break;
            case TokenType::DECL: string_rep = "DECL"; break;
            case TokenType::CALL: string_rep = "CALL"; break;
            case TokenType::FUNC: string_rep = "FUNC"; break;
            case TokenType::TRUE: string_rep = "TRUE"; break;
            case TokenType::FALSE: string_rep = "FALSE"; break;
            case TokenType::NIL: string_rep = "NIL"; break;
            case TokenType::NUMBER: string_rep = "NUMBER"; break;
            case TokenType::STRING: string_rep = "STRING"; break;
            case TokenType::IDENTIFIER: string_rep = "IDENTIFIER"; break;
            case TokenType::OPERATOR: string_rep = "OPERATOR"; break;
            case TokenType::LEFT_PAREN: string_rep = "LEFT_PAREN"; break;
            case TokenType::RIGHT_PAREN: string_rep = "RIGHT_PAREN"; break;
            case TokenType::LEFT_BRACE: string_rep = "LEFT_BRACE"; break;
            case TokenType::RIGHT_BRACE: string_rep = "RIGHT_BRACE"; break;
            case TokenType::COMMA: string_rep = "COMMA"; break;
            case TokenType::END_OF_FILE: string_rep = "END_OF_FILE"; break;
            default: string_rep = "UNKNOWN";
        }
        return "TYPE:" + string_rep + " [value=\"" + value + "\", line_number=" + std::to_string(line_number) + "]";
    }
};
