#pragma once
class Collider2D {
    float x, y;
    float leftBound, rightBound, topBound, bottomBound;

    public:
    Collider2D();
    void reset();
};