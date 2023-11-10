#pragma once

#include <glm/glm.hpp>

namespace Physics {

    glm::dvec2 evaluate(double target, const glm::dvec2 &y,
                        const glm::dvec2 &dy, double t, double dt);
    glm::dvec2 RK4(double target, const glm::vec2 &state, const glm::vec2 &d0, double t, double dt);
}; // namespace Physics
