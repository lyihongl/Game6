#include "inc/PhysicsProcess.hpp"

double accel(double x, double dx, double y, double dy, double t, double c1,
             double c2, double c3) {
    return (x + c3 * dx - y - c1 * dy) / c2;
}

glm::dvec2 Physics::evaluate(double target, const glm::dvec2 &y,
                            const glm::dvec2 &dy, double t, double dt) {
    // clang-format off
    glm::dvec2 state = { 
        y[0] + dy[0] * dt,
        y[0] + dy[0] * dt
    };
    glm::dvec2 output = {
        state[1],
        accel(target, 0, y[0], y[1], t+dt, 0.003, 0.002, 0)
    };
    // clang-format on
    return output;
}

glm::dvec2 Physics::RK4(double target, const glm::vec2 &state, const glm::vec2 &d0, double t, double dt) {
    glm::dvec2 k1, k2, k3, k4;
    k1 = evaluate(target, state, d0, t, dt);
    k2 = evaluate(target, state, k1, t, dt*0.5f);
    k3 = evaluate(target, state, k2, t, dt*0.5f);
    k4 = evaluate(target, state, k3, t, dt);

    double dxdt = dt / 6.0 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);
    double dvdt = dt / 6.0 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]);
    return {state[0] + dxdt, state[1] + dvdt};
}
