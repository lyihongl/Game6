#pragma once
#include "ComponentBase.hpp"
class Collider2D : Component2D{
    float x, y;
    float leftBound, rightBound, topBound, bottomBound;

    public:
    Collider2D();
    virtual void reset();
};