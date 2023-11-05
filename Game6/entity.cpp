#include "inc/entity.hpp"

Entity::Entity(std::size_t id) : id(id)
{
}

uint32_t Entity::get_id()
{
	return id;
}

const std::string& Entity::getTag(size_t id)
{
	return ComponentPool::Instance().getTag(id);
}
