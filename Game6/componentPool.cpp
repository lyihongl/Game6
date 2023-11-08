#include "inc/componentPool.hpp"

ComponentPool::ComponentPool(size_t max_size) : numEntities(max_size), tags(max_size), active(max_size, false), componentActive(max_size) {
	pool = {
		std::vector<Physics2D>(max_size),
		std::vector<Collider2D>(max_size),
		std::vector<Quad>(max_size),
		std::vector<Sprite>(max_size)
	};
}

std::size_t ComponentPool::getNextIndex() const
{
	for (std::size_t i = 0; i < active.size(); i++) {
		if (!active[i]) {
			return i;
		}
	}
	return numEntities;
}

ComponentPool& ComponentPool::Instance() {
	static ComponentPool pool{ 200 };
	return pool;
}

const std::string& ComponentPool::getTag(std::size_t id) const {
	return tags[id];
}

std::size_t ComponentPool::addEntity(const std::string& tag)
{
	std::size_t index = getNextIndex();
	active[index] = true;
	return index;
}
