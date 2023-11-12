#include "inc/render.hpp"
#include <ranges>
#include <glad/glad.h>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Render::Render(float screen_w, float screen_h) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    this->screen_w = screen_w;
    this->screen_h = screen_h;
}
Render::~Render() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Render::updateRes(float screen_w, float screen_h) {
    this->screen_w = screen_w;
    this->screen_h = screen_h;
}

void Render::renderQuad(const std::vector<Quad> &quad, const Shader &sProgram) {
    // verticies
    std::vector<float> vertices;
    uint32_t draw_N = 0;

    for (const Quad &q : quad) {
        // vertices.push_back(q.topLeft().first);
        // vertices.push_back(q.topLeft().second);
        // vertices.push_back(q.x);
        // vertices.push_back(q.y);
        // vertices.push_back(q.rad);

        // vertices.push_back(q.topRight().first);
        // vertices.push_back(q.topRight().second);
        // vertices.push_back(q.x);
        // vertices.push_back(q.y);
        // vertices.push_back(q.rad);

        // vertices.push_back(q.bottomLeft().first);
        // vertices.push_back(q.bottomLeft().second);
        // vertices.push_back(q.x);
        // vertices.push_back(q.y);
        // vertices.push_back(q.rad);

        // vertices.push_back(q.bottomRight().first);
        // vertices.push_back(q.bottomRight().second);
        // vertices.push_back(q.x);
        // vertices.push_back(q.y);
        // vertices.push_back(q.rad);

        // vertices.push_back(q.topRight().first);
        // vertices.push_back(q.topRight().second);
        // vertices.push_back(q.x);
        // vertices.push_back(q.y);
        // vertices.push_back(q.rad);

        // vertices.push_back(q.bottomLeft().first);
        // vertices.push_back(q.bottomLeft().second);
        // vertices.push_back(q.x);
        // vertices.push_back(q.y);
        // vertices.push_back(q.rad);
        // draw_N+=2;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(3);
    sProgram.Use();
    // std::cout<<"screen_w: "<<screen_w<<std::endl;
    glUniform1i(glGetUniformLocation(sProgram.ID, "h"), screen_h);
    glUniform1i(glGetUniformLocation(sProgram.ID, "w"), screen_w);
    glDrawArrays(GL_TRIANGLES, 0, draw_N * 3);
}

void Render::renderEntity(const std::vector<Entity> &entities,
                          const Shader &program, const glm::vec2& cameraOffset) {
    std::vector<float> data;

    // clang-format off
    std::vector<glm::vec2> corners = {
        {-1.f, -1.f}, 
        {-1.f, +1.f}, 
        {+1.f, -1.f}, 
        {-1.f, +1.f}, 
        {+1.f, -1.f}, 
        {+1.f, +1.f}
    };
    // clang-format on
    int vertices = 0;
    for (const Entity &e : entities | std::views::reverse) {
        if (e.hasComponent<Sprite>() && e.hasComponent<Quad>() &&
            e.hasComponent<Position2D>()) {
            for (const auto &corner : corners) {
                //if (e.getComponent<Position2D>().x < 0 ||
                //    e.getComponent<Position2D>().x >= screen_w ||
                //    e.getComponent<Position2D>().y < 0 ||
                //    e.getComponent<Physics2D>().y >= screen_h) {
                //    continue;
                //}
                data.push_back(corner.x); // x offset
                data.push_back(corner.y); // y offset

                data.push_back(e.getComponent<Quad>().w);
                data.push_back(e.getComponent<Quad>().h);

                data.push_back(e.getComponent<Position2D>().x);
                data.push_back(e.getComponent<Position2D>().y);
                data.push_back(e.getComponent<Position2D>().rad);

                data.push_back(e.getComponent<Sprite>().x);
                data.push_back(e.getComponent<Sprite>().y);
                data.push_back(e.getComponent<Sprite>().w);
                data.push_back(e.getComponent<Sprite>().h);

                data.push_back(static_cast<float>(
                    e.getComponent<Sprite>().sheet.lock()->width));
                data.push_back(static_cast<float>(
                    e.getComponent<Sprite>().sheet.lock()->height));
                // std::cout << "w: " << e.getComponent<Sprite>().w
                //           << " h: " << e.getComponent<Sprite>().h << "\n"
                //           << "sheet w: "
                //           << e.getComponent<Sprite>().sheet.lock()->width
                //           << "sheet h: "
                //           << e.getComponent<Sprite>().sheet.lock()->height
                //           << "\n";
                vertices += 2;
            }
        }
    }
    GLuint dataSize = 13;
    glBindTexture(GL_TEXTURE_2D,
                  entities[0].getComponent<Sprite>().sheet.lock()->textureId);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(),
                 GL_STATIC_DRAW);
    // x offset y offset
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, dataSize * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // width height
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, dataSize * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // x y center, rad
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, dataSize * sizeof(float),
                          (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // sprite selection
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, dataSize * sizeof(float),
                          (void *)(7 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, dataSize * sizeof(float),
                          (void *)(11 * sizeof(float)));
    glEnableVertexAttribArray(4);
    program.Use();
    // std::cout<<"screen_w: "<<screen_w<<std::endl;
    glUniform1f(glGetUniformLocation(program.ID, "h"), screen_h);
    glUniform1f(glGetUniformLocation(program.ID, "w"), screen_w);
    glUniform2fv(glGetUniformLocation(program.ID, "cameraOffset"), 1, glm::value_ptr(cameraOffset));
    //std::cout << "update res: " << screen_h << "\n";
    glDrawArrays(GL_TRIANGLES, 0, vertices * 3);
}
