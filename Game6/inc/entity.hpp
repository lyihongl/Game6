#pragma once
#include "componentPool.hpp"
#include <string>
#include <stdint.h>

class Entity{
    std::size_t id;
public:
    Entity(std::size_t id);
    std::size_t get_id();
    const std::string &getTag(size_t id);

    template<typename T>
    T& getComponent() const {
        return ComponentPool::Instance().getComponent<T>(id);
    }

    template<typename T>
    bool hasComponent() const {
        return ComponentPool::Instance().getComponentActive<T>(id);
    }
    
    template<typename T>
    void setComponent(const T& c) {
        ComponentPool::Instance().setComponent<T>(id, c);
    }

    template<typename T>
    void setComponent(const T&& c) {
        ComponentPool::Instance().setComponent<T>(id, std::forward<const T>(c));
    }

};