#pragma once
#include "physics2d.hpp"
#include <glm/glm.hpp>

class Position2D {
    public:
    float x, y, rad;
    Position2D &operator+=(const Physics2D&);
    Position2D &operator=(const glm::vec2&&);
};
