#pragma once
#include <glm/glm.hpp>
#include "ComponentBase.hpp"
class Kinematics2D : Component2D {
    public:
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float vrad, arad;
    Kinematics2D();
    Kinematics2D &withVelocity(const glm::vec2&);
    Kinematics2D &withAcceleration(const glm::vec2&);
    Kinematics2D &withOmega(float vrad);
    Kinematics2D &withAlpha(float arad);
    virtual void reset();
};
