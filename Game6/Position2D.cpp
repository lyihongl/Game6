#include "inc/components/Position2D.hpp"

Position2D::Position2D() {
    x = 0;
    y = 0;
    rad = 0;
}

Position2D::Position2D(float x, float y, float rad) : x(x), y(y), rad(rad) {
    
}

void Position2D::reset() {
    x = 0;
    y = 0;
    rad = 0;
}

Position2D &Position2D::operator+=(const Physics2D &other) {
    x += other.vx;
    y += other.vy;
    rad += other.vrad;
    return *this;
}

Position2D &Position2D::operator=(const glm::vec2 &&other) {
    x = other.x;
    y = other.y;
    return *this;
}
