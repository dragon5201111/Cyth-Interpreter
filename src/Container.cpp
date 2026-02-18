#include "Container.h"

template<typename C>
bool BaseContainer<C>::empty() const {
    return container.empty();
}

template<typename C>
size_t BaseContainer<C>::size() const {
    return container.size();
}

template<typename C>
bool BaseContainer<C>::equals(const AbstractContainer &other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }

    const auto& other_container = static_cast<const BaseContainer<C>&>(other).container;
    return container == other_container;
}

template<typename C>
std::string BaseContainer<C>::to_string() const {
    std::string result = left_closing;

    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it != container.begin())
            result += ", ";

        result += it->to_string();
    }

    result += right_closing;
    return result;
}
