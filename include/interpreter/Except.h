#pragma once
#include "../value/Value.h"

class ReturnException : public std::exception {
public:
    Value value;
    explicit ReturnException(Value v) : value(std::move(v)) {}
};

class BreakException : public std::exception {
public:
    explicit BreakException() = default;
};

class ContinueException : public std::exception {
public:
    explicit ContinueException() = default;
};