#include "Tokenizer.h"

#include <stdexcept>

Token Tokenizer::last() {
    if (previous.has_value()) {
        return previous.value();
    }

    throw std::runtime_error("No previous token avaliable!");
}

Token Tokenizer::peek() {
    if (!cached.has_value()) {
        cached = advance_current();
    }
    return cached.value();
}

Token Tokenizer::next() {
    if (!cached.has_value()) {
        Token next = advance_current();
        previous = next;
        return next;
    }

    Token temp = cached.value();
    cached.reset();
    previous = temp;
    return temp;
}

Token Tokenizer::advance_current() {
    skip_whitespace();

    if (current >= input_size) {
        return Token(TokenType::END_OF_FILE, current_line);
    }

    switch (const char current_char = input[current]) {
        case '(': current++; return Token(TokenType::LEFT_PAREN, current_line);
        case ')': current++; return Token(TokenType::RIGHT_PAREN, current_line);
        case '{': current++; return Token(TokenType::LEFT_BRACE, current_line);
        case '}': current++; return Token(TokenType::RIGHT_BRACE, current_line);
        case '[': current++; return Token(TokenType::LEFT_BRACKET, current_line);
        case ']': current++; return Token(TokenType::RIGHT_BRACKET, current_line);
        case ',': current++; return Token(TokenType::COMMA, current_line);
        case '+': current++; return Token(TokenType::OPERATOR,"+", current_line);
        case '-': current++; return Token(TokenType::OPERATOR, "-", current_line);
        case '*': current++; return Token(TokenType::OPERATOR, "*", current_line);
        case '/': current++; return Token(TokenType::OPERATOR, "/", current_line);
        case '%': current++; return Token(TokenType::OPERATOR, "%", current_line);
        case '<':
            return match_operator('<', '=', "<=");
        case '>':
            return match_operator('>', '=', ">=");
        case '!':
            return match_operator('!', '=', "!=");
        case '=':
            return match_operator('=', '=', "==");
        case '&':
            return match_operator('&', '&', "&&");
        case '|':
            return match_operator('|', '|', "||");
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


void Tokenizer::skip_whitespace() {
    while (current < input_size) {
        const char current_char = input[current];
        if (current_char == '#') {
            while (current < input_size && input[current] != '\n') {
                current++;
            }
            continue;
        }

        if (current_char == '\n') {
            current_line++;
        }

        if (std::isspace(current_char)) {
            current++;
            continue;
        }

        break;
    }
}

// TODO: fix to handle escape characters
Token Tokenizer::get_string() {
    const int sub_start = ++current;
    while (current < input_size && input[current] != '\"') {
        current++;
    }
    return Token(TokenType::STRING, input.substr(sub_start, current++ - sub_start), current_line);
}

Token Tokenizer::match_operator(const char current_char, const char expected, const std::string& two_char) {
    if (current + 1 < input_size && input[current + 1] == expected) {
        current += 2;
        return Token(TokenType::OPERATOR, two_char, current_line);
    }
    current++;
    return Token(TokenType::OPERATOR, std::string(1, current_char), current_line);
}

Token Tokenizer::get_number() {
    const int sub_start = current++;
    while (current < input_size && std::isdigit(input[current])) {
        current++;
    }
    return Token(TokenType::NUMBER, input.substr(sub_start, current - sub_start), current_line);
}

Token Tokenizer::get_identifier() {
    const int sub_start = current++;
    while (current < input_size && (std::isalnum(input[current]) || input[current] == '_')) {
        current++;
    }

    const std::string fragment = input.substr(sub_start, current - sub_start);
    if (fragment_map.count(fragment)) {
        return Token(fragment_map.at(fragment), current_line);
    }

    return Token(TokenType::IDENTIFIER, fragment, current_line);
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



