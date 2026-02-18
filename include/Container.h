#pragma once
#include <stdexcept>
#include <utility>
#include "Value.h"

class Container : public Printable {
protected:
    std::string left_closing;
    std::string right_closing;

    Container(std::string left, std::string right)
        : left_closing(std::move(left)),
          right_closing(std::move(right)) {}

public:
    ~Container() override = default;
    [[nodiscard]] virtual bool is_empty() const = 0;
    [[nodiscard]] virtual bool equals(const Container& other) const = 0;
    [[nodiscard]] bool operator==(const Container& other) const {
        return equals(other);
    }
    [[nodiscard]] std::string to_string() const override = 0;
};

template<typename C>
class BaseContainer : public Container {
protected:
    C container;
public:
    BaseContainer(C c, std::string left, std::string right)
        : Container(std::move(left), std::move(right)),
          container(std::move(c)) {}

    [[nodiscard]] bool is_empty() const override {
        return container.empty();
    }

    [[nodiscard]] bool equals(const Container &other) const override {
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

    Value& operator[](const std::size_t index) {
        return container[index];
    }
};

class SetContainer : public BaseContainer<std::set<Value>> {
public:
    SetContainer() : BaseContainer({}, "{", "}") {}

    Value& operator[](const std::size_t _) const {
        throw std::out_of_range("Cannot index a set");
    }
};
