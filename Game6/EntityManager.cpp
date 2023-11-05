#include "EntityManager.hpp"
#include "inc/componentPool.hpp"

Entity EntityManager::addEntity(const std::string& tag)
{
	std::size_t id = ComponentPool::Instance().addEntity(tag);
	Entity e(id);
	entities.push_back(e);
	
	return e;
}
