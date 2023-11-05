#pragma once
#include <string>
#include <functional>

class Resource {
    std::string name;

    public:
    Resource(const std::string &);
    std::string getName() const;
};

template <> struct std::hash<Resource> {
    std::size_t operator()(const Resource &s) const noexcept {
        return std::hash<std::string>{}(s.getName());
    }
};