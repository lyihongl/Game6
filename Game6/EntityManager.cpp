#include "inc/EntityManager.hpp"
#include "inc/componentPool.hpp"

Entity EntityManager::addEntity(const std::string &tag) {
    std::size_t id = ComponentPool::Instance().addEntity(tag);
    Entity e(id);
    entities.push_back(e);

    return e;
}

std::size_t EntityManager::removeEntity(std::size_t id) {
    auto it = entities.begin();
    for (; it != entities.end(); it++) {
        if (it->get_id() == id) {
            break;
        }
    }
    std::size_t ret = it -> get_id();
    if (it != entities.end()) {
        entities.erase(it);
    }
    return ret;
}
