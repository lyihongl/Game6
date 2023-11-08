#pragma once
#include <vector>
#include "inc/entity.hpp"

class EntityManager
{
	std::vector<Entity> entities;
public:
	Entity addEntity(const std::string& tag);
};

