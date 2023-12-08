#pragma once
#include <vector>
#include "inc/entity.hpp"

class EntityManager {
    public:
    Entity addEntity(const std::string &tag);
    std::size_t removeEntity(std::size_t id);
    std::vector<Entity> entities;
    std::vector<Entity> particles;
};
