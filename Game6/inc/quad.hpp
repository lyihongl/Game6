#pragma once

#include <utility>
#include "components/ComponentBase.hpp"

class Quad : Component2D {
   public:
    float w;
    float h;
    // float rad;
    Quad();
    Quad(float w, float h);
    virtual void reset();
    // std::pair<float, float> topLeft() const;
    // std::pair<float, float> topRight() const;
    // std::pair<float, float> bottomRight() const;
    // std::pair<float, float> bottomLeft() const;
};