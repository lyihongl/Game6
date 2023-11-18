#pragma once
#include <tuple>
#include <vector>
#include "Sprite.hpp"
#include "components/Physics2D.hpp"
#include "components/Position2D.hpp"
#include "components/collider2d.hpp"
#include "quad.hpp"

class Particle {
    std::size_t getNextIndex();

   public:
    // clang-format off
    std::tuple< 
                std::vector<Position2D>, 
                std::vector<Physics2D>,
                std::vector<unsigned long long>, // TTL
                std::vector<bool>
              >
        components;
    // clang-format on

    std::size_t count;
    const Sprite& sprite;
    const Quad& quad;
    Particle(const Sprite&, const Quad&);
    std::size_t addParticle(const Position2D&, const Physics2D&,
                            unsigned long long);

    Position2D& getPosition2D(std::size_t id);
    Physics2D& getPhysics2D(std::size_t id);
    unsigned long long getTTL(std::size_t id);
    bool isActive(std::size_t id);
};
