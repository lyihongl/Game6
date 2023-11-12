#pragma once
#include <glm/glm.hpp>
#include "ComponentBase.hpp"
#include "physics2d.hpp"

class Position2D : Component2D {
   public:
    float x, y, rad;
    Position2D();
    Position2D(float, float, float);
    Position2D& operator+=(const Physics2D&);
    Position2D& operator=(const glm::vec2&&);
    virtual void reset();
};
