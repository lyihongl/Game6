#include "inc/quad.hpp"

Quad::Quad():x(0),y(0),w(0),h(0),rad(0)
{
}

Quad::Quad(float w, float h, float x, float y, float rad)
    : x(x), y(y), w(w), h(h), rad(rad) {
}

std::pair<float, float> Quad::topLeft() const {
    return {x - w / 2, y - h / 2};
}
std::pair<float, float> Quad::topRight() const {
    return {x + w / 2, y - h / 2};
}
std::pair<float, float> Quad::bottomRight() const {
    return {x + w / 2, y + h / 2};
}
std::pair<float, float> Quad::bottomLeft() const {
    return {x - w / 2, y + h / 2};
}