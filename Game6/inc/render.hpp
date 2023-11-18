#pragma once

#include "quad.hpp"
#include "entity.hpp"
#include "Particle.hpp"

#include <vector>
#include <shaders.hpp>
#include <glm/glm.hpp>

class Render {
    uint32_t VBO, VAO;
    glm::mat4 MVP;
    float screen_w, screen_h;
    glm::mat4 view;

    public:
    Render(float, float);
    ~Render();
    void updateRes(float, float);
    Render(Render &) = delete;
    Render(Render &&) = delete;
    Render operator=(Render &) = delete;
    void renderQuad(const std::vector<Quad> &, const Shader &);
    void renderEntity(const std::vector<Entity> &, const Shader &, const glm::vec2& cameraOffset);
    void renderParticle(const Particle&, const Shader&,
                        const glm::vec2& cameraOffset);
};