#include "inc/components/Position2D.hpp"

Position2D &Position2D::operator+=(const Physics2D &other) {
    x += other.vx;
    y += other.vy;
    rad += other.vrad;
    return *this;
}
