#pragma once
#include <stdexcept>
#include <utility>
#include <deque>
#include <fstream>
#include <map>
#include <set>
#include "./Container.h"
#include "../io/Print.h"

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
    virtual void remove(const Value& index) = 0;
    virtual void put(const Value& index, const Value& value) = 0;
    [[nodiscard]] virtual bool operator==(const AbstractContainer& other) const = 0;
    [[nodiscard]] virtual bool operator<(const AbstractContainer& other) const = 0;
    [[nodiscard]] std::string to_string() const override = 0;
};

class FileContainer final : public AbstractContainer {
    std::fstream f_stream;
    std::string file_name;

    std::ios_base::openmode get_openmode(const std::string& openmode) {
        std::ios_base::openmode mode = {};
        for (const char c : openmode) {
            switch (c) {
                case 'a':
                    mode |= std::ios_base::ate;
                    break;
                case 'b':
                    mode |= std::ios_base::binary;
                    break;
                case 'r':
                    mode |= std::ios_base::in;
                    break;
                case 'w':
                    mode |= std::ios_base::out;
                    break;
                case 'x':
                    mode |= std::ios_base::trunc;
                    break;
                default:
                    throw std::invalid_argument("Invalid mode: " +  std::string(1, c) + ".");
            }
        }
        return mode;
    }

public:
    explicit FileContainer() : AbstractContainer("<file ", ">") {}

    void open(const std::string& f_name, const std::string& openmode) {
        if (f_stream.is_open()) {
            throw std::ios_base::failure("File already open: " + file_name + ".");
        }

        file_name = f_name;
        f_stream.open(f_name, get_openmode(openmode));

        if (!f_stream.is_open()) {
            throw std::ios_base::failure("Failed to open file: " + f_name + ".");
        }
    }

    void close() {
        if (f_stream.is_open()) {
            f_stream.close();
        }
    }

    ~FileContainer() override {
        close();
    }

    bool is_open() {
        return f_stream.is_open();
    }

    bool empty() const override {
        throw std::runtime_error("FileContainer::empty() called");
    }

    [[nodiscard]] size_t size() const override {
        throw std::runtime_error("FileContainer::size() called");
    }

    [[nodiscard]] Value& operator[](const Value& index) override {
        throw std::runtime_error("FileContainer::operator[]() called");
    }

    void remove(const Value &index) override {
        throw std::runtime_error("FileContainer::remove() called");
    }

    void put(const Value &index, const Value &value) override {
        throw std::runtime_error("FileContainer::insert() called");
    }

    [[nodiscard]] bool operator==(const AbstractContainer& other) const override {
        return this == &other;
    }

    [[nodiscard]] bool operator<(const AbstractContainer& other) const override {
        return this < &other;
    }

    [[nodiscard]] std::string to_string() const override {
        return left_closing + file_name + right_closing;
    }
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

    bool operator==(const AbstractContainer& other) const override {
        if (!same_container_type(other)) {
            return false;
        }
        const auto& other_container = static_cast<const BaseContainer&>(other).container;
        return container == other_container;
    }

    bool operator<(const AbstractContainer& other) const override {
        if (!same_container_type(other)) {
            return false;
        }

        const auto& other_container = static_cast<const BaseContainer&>(other).container;
        return container < other_container;
    }

    [[nodiscard]] bool same_container_type(const AbstractContainer& other) const {
        return typeid(*this) == typeid(other);
    }

    [[nodiscard]] std::string to_string() const override {
        std::string result = left_closing;

        for (auto it = container.begin(); it != container.end(); ++it) {
            if (it != container.begin())
                result += ", ";

            if constexpr (requires { it->to_string(); }) {
                result += it->to_string();
            }else {
                result += it->first.to_string() + " : " + it->second.to_string();
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
    void remove(const Value &index) override{ container.erase(container.begin() + static_cast<int64_t>(index.as_number()));}
    void put(const Value &index, const Value &value) override { container.insert(container.begin() + static_cast<int64_t>(index.as_number()), value); }
};

class SetContainer final : public BaseContainer<std::set<Value>> {
public:
    explicit SetContainer() : BaseContainer({}, "{", "}") {}
    explicit SetContainer(const std::set<Value> &set) : BaseContainer(set, "{", "}") {}

    Value& operator[](const Value&) override { throw std::out_of_range("Cannot index a set."); }
    void remove(const Value &index) override { container.erase(index); }
    void put(const Value &index, const Value &value) override {
        auto idx = container.begin();
        const auto num_increments =  static_cast<int64_t>(value.as_number());
        for (int64_t increments = 0; increments < num_increments; ++increments) {
            ++idx;
        }
        container.insert(idx, value);
    }
};

class MapContainer final : public BaseContainer<std::map<Value, Value>> {
public:
    explicit MapContainer() : BaseContainer({}, "{{", "}}") {}
    explicit MapContainer(const std::map<Value, Value> &map) : BaseContainer(map, "{{", "}}") {}

    Value& operator[](const Value& value) override { return container[value]; }
    void remove(const Value &index) override { container.erase(index); }
    void put(const Value &index, const Value &value) override { container.insert({index, value}); }
};