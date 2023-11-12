#pragma once
#include "ComponentBase.hpp"
struct Physics2D : Component2D{
    float x, y;
    float vx, vy;
    float ax, ay;
    float rad, vrad, arad;

    public:
    Physics2D();
    void reset();
};