#pragma once

#include <glm/glm.hpp>

namespace Physics {

glm::dvec2 evaluate(double target, const glm::dvec2& y, const glm::dvec2& dy,
                    double t, double dt);
glm::dvec2 RK4(double target, const glm::dvec2& state, const glm::dvec2& d0,
               double t, double dt);

glm::dvec2 implicitEuler(double target, const glm::dvec2& state, double t,
                         double dt);

int relativeDir(const glm::vec2&, const glm::vec2&, const glm::vec2&);
};  // namespace Physics
