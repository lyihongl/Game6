#include "inc/PhysicsProcess.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

double accel(double x, double dx, double y, double dy, double t, double c1,
             double c2, double c3) {
    // double z = (x + c3 * dx - y - c1 * dy) / c2;
    return (x + c3 * dx - y - c1 * dy) / c2;
}

glm::dvec2 Physics::evaluate(double target, const glm::dvec2& y,
                             const glm::dvec2& dy, double t, double dt) {
    // std::cout<<"d0: "<<glm::to_string(dy)<<std::endl;
    // clang-format off
    glm::dvec2 state = { 
        y[0] + dy[0] * dt,
        y[1] + dy[1] * dt
    };
    glm::dvec2 output = {
        state[1],
        accel(target, 0.005, y[0], y[1], t+dt, 0.01, 0.0001, 0)
    };
    //std::cout<<"accel: "<<glm::to_string(output)<<std::endl;
    // clang-format on
    return output;
}

glm::dvec2 Physics::RK4(double target, const glm::dvec2& state,
                        const glm::dvec2& d0, double t, double dt) {
    glm::dvec2 k1, k2, k3, k4;
    k1 = evaluate(target, state, d0, t, dt);
    k2 = evaluate(target, state, k1, t, dt * 0.5f);
    k3 = evaluate(target, state, k2, t, dt * 0.5f);
    k4 = evaluate(target, state, k3, t, dt);

    double dxdt = dt / 6.0 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);
    double dvdt = dt / 6.0 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]);
    return {dxdt, dvdt};
}
glm::dvec2 Physics::implicitEuler(double target, const glm::dvec2& state,
                                  double t, double dt) {

    double x = state[0] + dt * state[1];
    double dx = state[1] + dt * (target - x - 0.01 * state[1]) / 0.0001;
    return glm::dvec2{x, dx};
}

int Physics::relativeDir(const glm::vec2& a, const glm::vec2& b,
                         const glm::vec2& c) {
    float d = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    //std::cout << "d: " << d << std::endl;
    if (d > 0)
        return 1;
    if (d == 0)
        return 0;
    if (d < 0)
        return -1;
}
