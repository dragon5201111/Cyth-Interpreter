#pragma once
#include <stdexcept>
#include <utility>
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
    [[nodiscard]] virtual Value& operator[](Value index) = 0;

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

    [[nodiscard]] bool empty() const override {
        return container.empty();
    }

    [[nodiscard]] size_t size() const override {
        return container.size();
    }

    [[nodiscard]] bool equals(const AbstractContainer &other) const override {
        if (typeid(*this) != typeid(other)) {
            return false;
        }

        const auto& other_container = dynamic_cast<const BaseContainer&>(other).container;
        return container == other_container;
    }

    [[nodiscard]] std::string to_string() const override {
        std::string result = left_closing;

        for (auto it = container.begin(); it != container.end(); ++it) {
            if (it != container.begin())
                result += ", ";

            result += it->to_string();
        }

        result += right_closing;
        return result;
    }
};

class ArrayContainer : public BaseContainer<std::deque<Value>> {
public:
    ArrayContainer() : BaseContainer({}, "[", "]") {}

    Value& operator[](const std::size_t index) override {
        return container[index];
    }

    Value& operator[](const Value& _) const {
        throw std::out_of_range("Array Value index unimplemented.");
    }
};

class SetContainer : public BaseContainer<std::set<Value>> {
public:
    SetContainer() : BaseContainer({}, "{", "}") {}

    Value& operator[](const std::size_t _) const {
        throw std::out_of_range("Cannot index a set");
    }

    Value& operator[](const Value& _) const {
        throw std::out_of_range("Set Value index unimplemented.");
    }
};
