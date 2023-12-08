#include "./inc/Particle.hpp"

std::size_t Particle::getNextIndex() {
    std::size_t res = 0;
    for (; res < std::get<std::vector<bool>>(components).size(); res++) {
        if (!std::get<std::vector<bool>>(components)[res]) {
            return res;
        }
    }
    return std::get<std::vector<bool>>(components).size();
}

Particle::Particle(const Sprite& sprite, const Quad& quad) : sprite(sprite), quad(quad), count(0) {}

std::size_t Particle::addParticle(const Position2D& position,
                                  const Physics2D& physics, unsigned long long TTL) {
    std::size_t id = getNextIndex();
    std::get<std::vector<Position2D>>(components)[id] = position;
    std::get<std::vector<Physics2D>>(components)[id] = physics;
    std::get<std::vector<unsigned long long>>(components)[id] = TTL;
    std::get<std::vector<bool>>(components)[id] = true;
    count++;
    return id;
}

Position2D& Particle::getPosition2D(std::size_t id) {
    if (std::get<std::vector<bool>>(components)[id]) {
        return std::get<std::vector<Position2D>>(components)[id];
    } else {
        throw -1; 
    }
}

Physics2D& Particle::getPhysics2D(std::size_t id) {
    if (std::get<std::vector<bool>>(components)[id]) {
        return std::get<std::vector<Physics2D>>(components)[id];
    } else {
        throw -1; 
    }
}

unsigned long long Particle::getTTL(std::size_t id) {
    if (std::get<std::vector<bool>>(components)[id]) {
        return std::get<std::vector<unsigned long long>>(components)[id];
    } else {
        throw -1; 
    }
}

bool Particle::isActive(std::size_t id) {
    return std::get<std::vector<bool>>(components)[id];
}
