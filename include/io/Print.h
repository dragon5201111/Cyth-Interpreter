#pragma once
#include <string>

class Printable {
public:
    virtual ~Printable() = default;
    [[nodiscard]] virtual std::string to_string() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Printable& printable) {
        return os << printable.to_string();
    }
};
