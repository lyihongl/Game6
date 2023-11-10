#include <glm/glm.hpp>
#pragma once
class Kinematics2D {
    public:
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float rad, vrad, arad;
    Kinematics2D();
    Kinematics2D &withVelocity(const glm::vec2&);
    Kinematics2D &withAcceleration(const glm::vec2&);
    Kinematics2D &withRad(float rad);
    Kinematics2D &withOmega(float vrad);
    Kinematics2D &withAlpha(float arad);
};
