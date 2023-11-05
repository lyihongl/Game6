#include "inc/resource.hpp"

Resource::Resource(const std::string &name) : name(name) {};
std::string Resource::getName() const {
    return name;
}