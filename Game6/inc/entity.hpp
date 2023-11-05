#pragma once
#include "componentPool.hpp"
#include <string>
#include <stdint.h>

class Entity{
    std::size_t id;
public:
    Entity(std::size_t id);
    uint32_t get_id();
    const std::string &getTag(size_t id);

    template<typename T>
    T& getComponent(size_t id) {
        return ComponentPool::Instance().getComponent<T>(id);
    }
};