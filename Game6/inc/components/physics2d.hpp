#pragma once
struct Physics2D{
    float x, y;
    float vx, vy;
    float ax, ay;
    float rad;
public:
    Physics2D();
    void reset();
};