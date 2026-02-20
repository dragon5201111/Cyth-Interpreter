#pragma once
#include <stdexcept>
#include <utility>
#include <deque>
#include <map>
#include <set>
#include "Value.h"
#include "Print.h"

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

    [[nodiscard]] bool empty() const override { return container.empty(); };
    [[nodiscard]] size_t size() const override { return container.size(); };

    [[nodiscard]] bool equals(const AbstractContainer &other) const override {
        if (typeid(*this) != typeid(other)) {
            return false;
        }
        const auto& other_container = static_cast<const BaseContainer&>(other).container;
        return container == other_container;
    }

    [[nodiscard]] std::string to_string() const override {
        std::string result = left_closing;

        for (auto it = container.begin(); it != container.end(); ++it) {
            if (it != container.begin())
                result += ", ";

            // TODO: fix this line
            if constexpr (requires { it->to_string(); }) {
                result += it->to_string();
            }
        }

        result += right_closing;
        return result;
    }
};

class ArrayContainer final : public BaseContainer<std::deque<Value>> {
public:
    explicit ArrayContainer() : BaseContainer({}, "[", "]") {}
    explicit ArrayContainer(const std::deque<Value> &array) : BaseContainer(array, "[", "]") {}

    Value& operator[](const Value& value) override { return container[static_cast<int64_t>(value.as_number())]; }
};

class SetContainer final : public BaseContainer<std::set<Value>> {
public:
    explicit SetContainer() : BaseContainer({}, "{", "}") {}
    explicit SetContainer(const std::set<Value> &set) : BaseContainer(set, "{", "}") {}

    Value& operator[](const Value&) override { throw std::out_of_range("Cannot index a set."); }
};

class MapContainer final : public BaseContainer<std::map<Value, Value>> {
public:
    explicit MapContainer() : BaseContainer({}, "{", "}") {}
    explicit MapContainer(const std::map<Value, Value> &map) : BaseContainer(map, "{", "}") {}

    Value& operator[](const Value& value) override { return container[value]; }

    // TODO: implement to_string
    [[nodiscard]] std::string to_string() const override {
        throw std::runtime_error("Unimplemented to_string for map");
    }
};