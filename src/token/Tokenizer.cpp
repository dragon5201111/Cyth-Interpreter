#include "../../include/token/Tokenizer.h"

#include <iostream>
#include <algorithm>
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
        case ':': current++; return Token(TokenType::COLON, current_line);
        case '+': current++; return Token(TokenType::OPERATOR,"+", current_line);
        case '~': current++; return Token(TokenType::OPERATOR,"~", current_line);
        case '-': current++; return Token(TokenType::OPERATOR, "-", current_line);
        case '*': current++; return Token(TokenType::OPERATOR, "*", current_line);
        case '/': current++; return Token(TokenType::OPERATOR, "/", current_line);
        case '%': current++; return Token(TokenType::OPERATOR, "%", current_line);
        case '^': current++; return Token(TokenType::OPERATOR, "^", current_line);
        case '<':
            return match_operator("<", {"=", "<"}, {"<=", "<<"});
        case '>':
            return match_operator(">", {"=", ">"}, {">=", ">>"});
        case '!':
            return match_operator("!", {"="}, {"!="});
        case '=':
            return match_operator("=", {"="}, {"=="});
        case '&':
            return match_operator("&", {"&"}, {"&&"});
        case '|':
            return match_operator("|", {"|"}, {"||"});
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
    bool in_multi_line_comment = false;
    while (current < input_size) {
        const char current_char = input[current];

        if (input_has_substr(current, MULTI_LINE_COMMENT_BEGIN)) {
            in_multi_line_comment = true;
            current += static_cast<int>(MULTI_LINE_COMMENT_BEGIN.size());
            continue;
        }

        if (input_has_substr(current, MULTI_LINE_COMMENT_END)) {
            in_multi_line_comment = false;
            current += static_cast<int>(MULTI_LINE_COMMENT_END.size());
            continue;
        }

        if (!in_multi_line_comment && input_has_substr(current, SINGLE_LINE_COMMENT)) {
            while (current < input_size && input[current] != '\n') {
                current++;
            }
            continue;
        }

        if (current_char == '\n') {
            current_line++;
        }

        if (std::isspace(current_char) || in_multi_line_comment) {
            current++;
            continue;
        }

        break;
    }

    if (in_multi_line_comment) {
        throw std::runtime_error("Unterminated multi-line comment");
    }
}

// Checks from pos if pos + substr length is substr
bool Tokenizer::input_has_substr(const int pos, const std::string& substr) const {
    const auto substr_size = substr.size();
    if (pos + (substr_size - 1) < input_size) {
        return input.substr(pos, substr_size) == substr;
    }
    return false;
}

Token Tokenizer::get_string() {
    current++; // skip opening quote
    std::string string;

    while (current < input_size && input[current] != '\"') {
        if (input[current] == '\\' && current + 1 < input_size) {
            switch (input[current + 1]) {
                case 'b': string += '\b'; break;
                case 'r': string += '\r'; break;
                case 't': string += '\t'; break;
                case 'n': string += '\n'; break;
                case '"': string += '"'; break;
                case '\'': string += '\''; break;
                case '\\': string += '\\'; break;
                default: throw std::runtime_error("Invalid escape sequence");
            }
            current += 2;
        }else {
            string += input[current];
            current++;
        }
    }

    if (current >= input_size) {
        throw std::runtime_error("Unterminated string literal");
    }

    current++; // skip closing quote
    return Token(TokenType::STRING, string, current_line);
}

Token Tokenizer::match_operator(const std::string& current_char, const std::vector<std::string> &expected, const std::vector<std::string> &match) {
    const size_t expected_size = expected.size();
    std::vector<std::pair<std::string, int>> matches;

    for (int i = 0; i < expected_size; i++) {
        if (match_next(expected[i])) {
            matches.emplace_back(match[i], static_cast<int>(match[i].size()));
        }
    }

    // Could be multiple matches, find one with the biggest size
    if (!matches.empty()) {
        const auto max_token = max_element(matches.begin(), matches.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second;
        });

        current += max_token->second;
        return Token(TokenType::OPERATOR, max_token->first, current_line);
    }

    current++;
    return Token(TokenType::OPERATOR, current_char, current_line);
}

bool Tokenizer::match_next(const std::string& expected) const {
    const auto expected_size = expected.size();
    if (current + expected_size < input_size && input.substr(current + 1, expected_size) == expected) {
        return true;
    }
    return false;
}


Token Tokenizer::get_number() {
    auto number = std::string(1, input[current++]);
    // Loop until we encounter character not in the set of possible characters for a number
    while (current < input_size && char_in_number(input[current])) {
        number += input[current++];
    }

    // Double has similar pattern to float, must check for float first as it requires a suffix
    if (std::regex_match(number, FLOAT_PATTERN)) {
        return Token(TokenType::FLOAT, number, current_line);
    }

    if (std::regex_match(number, DOUBLE_PATTERN)) {
        return Token(TokenType::DOUBLE, number, current_line);
    }

    if (std::regex_match(number, INTEGER_PATTERN)) {
        return Token(TokenType::INTEGER, number, current_line);
    }

    if (std::regex_match(number, HEX_PATTERN)) {
        return Token(TokenType::HEX, number, current_line);
    }


    throw std::runtime_error("Invalid number " + number + " on line: " + std::to_string(current_line));
}

bool Tokenizer::char_in_number(const char c) {
    return std::isdigit(c) || std::isxdigit(c) || c == '.' || std::tolower(c) == 'x';
}

Token Tokenizer::get_identifier() {
    const int sub_start = current++;
    while (current < input_size && (std::isalnum(input[current]) || input[current] == '_')) {
        current++;
    }

    const std::string fragment = input.substr(sub_start, current - sub_start);
    if (FRAGMENT_MAP.contains(fragment)) {
        return Token(FRAGMENT_MAP.at(fragment), current_line);
    }

    return Token(TokenType::IDENTIFIER, fragment, current_line);
}

void Tokenizer::reset(std::string source) {
    input_size = source.size();
    input = std::move(source);
    current = 0;
    current_line = 1;
    cached.reset();
    previous.reset();
}

std::string Tokenizer::get_input() {
    return input;
}




