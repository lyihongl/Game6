#pragma once

#include <utility>

class Quad {
    public:
    float w;
    float h;
    float x;
    float y;
    float rad;
    Quad(float w, float h, float x, float y, float rad);
    std::pair<float, float> topLeft() const;
    std::pair<float, float> topRight() const; 
    std::pair<float, float> bottomRight() const; 
    std::pair<float, float> bottomLeft() const; 
};