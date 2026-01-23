#include "Tokenizer.h"

#include <stdexcept>

Token Tokenizer::peek() {
    if (!cached.has_value()) {
        cached = advance_current();
    }
    return cached.value();
}

Token Tokenizer::next() {
    if (!cached.has_value()) {
        return advance_current();
    }
    Token temp = cached.value();
    cached.reset();
    return temp;
}

Token Tokenizer::advance_current() {
    while (current < input_size && isspace(input[current])) {
        current++;
    }

    if (current >= input_size) {
        return Token(TokenType::END_OF_FILE);
    }

    switch (const char current_char = input[current]) {
        case '(': current++; return Token(TokenType::LEFT_PAREN);
        case ')': current++; return Token(TokenType::RIGHT_PAREN);
        case '{': current++; return Token(TokenType::LEFT_BRACE);
        case '}': current++; return Token(TokenType::RIGHT_BRACE);
        case ',': current++; return Token(TokenType::COMMA);

        case '+': current++; return Token(TokenType::OPERATOR, "+");
        case '-': current++; return Token(TokenType::OPERATOR, "-");
        case '*': current++; return Token(TokenType::OPERATOR, "*");
        case '/': current++; return Token(TokenType::OPERATOR, "/");
        case '%': current++; return Token(TokenType::OPERATOR, "%");
        case '<':
            return match_operator('<', "<=", TokenType::OPERATOR);
        case '>':
            return match_operator('>', ">=", TokenType::OPERATOR);
        case '!':
            return match_operator('!', "!=", TokenType::OPERATOR);
        case '=':
            return match_operator('=', "==", TokenType::ASSIGN);

        case '\"':
            return get_string();

        default:
            if (std::isdigit(current_char)) {
                return get_number();
            }

            if (std::isalpha(current_char) || current_char == '_') {
                return get_identifier();
            }

            throw std::invalid_argument("Unsupported character: " + std::string(1, current_char));
    }
}

Token Tokenizer::get_string() {
    const int sub_start = ++current;
    while (current < input_size && input[current] != '\"') {
        current++;
    }
    return Token(TokenType::STRING, input.substr(sub_start, current++ - sub_start));
}

Token Tokenizer::match_operator(const char current_char, std::string value, const TokenType default_type) {
    if (current + 1 < input_size && input[current + 1] == '=') {
        current += 2;
        return Token(TokenType::OPERATOR, std::move(value));
    }
    current++;
    return Token(default_type, std::string(1, current_char));
}

Token Tokenizer::get_number() {
    const int sub_start = current++;
    while (current < input_size && std::isdigit(input[current])) {
        current++;
    }
    return Token(TokenType::NUMBER, input.substr(sub_start, current - sub_start));
}

Token Tokenizer::get_identifier() {
    const int sub_start = current++;
    while (current < input_size && (std::isalnum(input[current]) || input[current] == '_')) {
        current++;
    }

    const std::string fragment = input.substr(sub_start, current - sub_start);
    if (fragment_map.count(fragment)) {
        return fragment_map.at(fragment);
    }

    return Token(TokenType::IDENTIFIER, fragment);
}

std::vector<Token> Tokenizer::collect() {
    std::vector<Token> tokens;
    Token token = peek();
    do {
        token = next();
        tokens.push_back(token);
    } while (token.get_type() != TokenType::END_OF_FILE);
    return tokens;
}

void Tokenizer::reset() {
    current = 0;
    cached.reset();
}



