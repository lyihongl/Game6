#pragma once
#include <glm/glm.hpp>
class SecondOrder {
   public:
    double k1, k2, k3;
    glm::dvec2 previousTarget;
    glm::dvec2 x, dx;

    void Update();

};
