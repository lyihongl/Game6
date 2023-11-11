#pragma once
#include "physics2d.hpp"

class Position2D {
    public:
    float x, y, rad;
    Position2D &operator+=(const Physics2D&);
};
