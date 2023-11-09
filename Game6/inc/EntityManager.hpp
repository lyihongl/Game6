#pragma once
#include <vector>
#include "inc/entity.hpp"

class EntityManager
{
public:
	Entity addEntity(const std::string& tag);
	std::vector<Entity> entities;
};

