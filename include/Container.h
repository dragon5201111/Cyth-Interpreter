#pragma once
#include <stdexcept>
#include <utility>
#include <deque>
#include <set>
#include "Value.h"

class AbstractContainer : public Printable {
protected:
    std::string left_closing;
    std::string right_closing;

    AbstractContainer(std::string left, std::string right)
        : left_closing(std::move(left)),
          right_closing(std::move(right)) {}

public:
    ~AbstractContainer() override = default;

    [[nodiscard]] virtual bool empty() const = 0;
    [[nodiscard]] virtual size_t size() const = 0;

    [[nodiscard]] virtual Value& operator[](size_t index) = 0;
    [[nodiscard]] virtual Value& operator[](const Value& index) = 0;

    [[nodiscard]] virtual bool equals(const AbstractContainer& other) const = 0;
    [[nodiscard]] bool operator==(const AbstractContainer& other) const { return equals(other); }

    [[nodiscard]] std::string to_string() const override = 0;
};

template<typename C>
class BaseContainer : public AbstractContainer {
protected:
    C container;
public:
    BaseContainer(C c, std::string left, std::string right)
        : AbstractContainer(std::move(left), std::move(right)),
          container(std::move(c)) {}

    [[nodiscard]] bool empty() const override;
    [[nodiscard]] size_t size() const override;

    [[nodiscard]] bool equals(const AbstractContainer &other) const override;
    [[nodiscard]] std::string to_string() const override;
};

class ArrayContainer final : public BaseContainer<std::deque<Value>> {
public:
    explicit ArrayContainer() : BaseContainer({}, "[", "]") {}
    explicit ArrayContainer(const std::deque<Value> &array) : BaseContainer(array, "[", "]") {}

    Value& operator[](const size_t index) override { return container[index]; }
    Value& operator[](const Value&) override { throw std::out_of_range("Array Value index unimplemented."); }
};

class SetContainer final : public BaseContainer<std::set<Value>> {
public:
    explicit SetContainer() : BaseContainer({}, "{", "}") {}
    explicit SetContainer(const std::set<Value> &set) : BaseContainer(set, "{", "}") {}

    Value& operator[](size_t) override { throw std::out_of_range("Cannot index a set"); }
    Value& operator[](const Value&) override { throw std::out_of_range("Set Value index unimplemented."); }
};
