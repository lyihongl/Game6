#include "inc/render.hpp"
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Render::Render(uint32_t screen_w, uint32_t screen_h) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    this->screen_w = screen_w;
    this->screen_h = screen_h;
}
Render::~Render(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Render::renderQuad(const std::vector<Quad> &quad, const Shader &sProgram) {
    // verticies
    std::vector<float> vertices;
    uint32_t draw_N = 0;

    for (const Quad &q : quad) {
        vertices.push_back(q.topLeft().first);
        vertices.push_back(q.topLeft().second);
        vertices.push_back(q.x);
        vertices.push_back(q.y);
        vertices.push_back(q.rad);

        vertices.push_back(q.topRight().first);
        vertices.push_back(q.topRight().second);
        vertices.push_back(q.x);
        vertices.push_back(q.y);
        vertices.push_back(q.rad);

        vertices.push_back(q.bottomLeft().first);
        vertices.push_back(q.bottomLeft().second);
        vertices.push_back(q.x);
        vertices.push_back(q.y);
        vertices.push_back(q.rad);


        vertices.push_back(q.bottomRight().first);
        vertices.push_back(q.bottomRight().second);
        vertices.push_back(q.x);
        vertices.push_back(q.y);
        vertices.push_back(q.rad);

        vertices.push_back(q.topRight().first);
        vertices.push_back(q.topRight().second);
        vertices.push_back(q.x);
        vertices.push_back(q.y);
        vertices.push_back(q.rad);

        vertices.push_back(q.bottomLeft().first);
        vertices.push_back(q.bottomLeft().second);
        vertices.push_back(q.x);
        vertices.push_back(q.y);
        vertices.push_back(q.rad);
        draw_N+=2;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(4*sizeof(float)));
    glEnableVertexAttribArray(3);
    sProgram.Use();
    // std::cout<<"screen_w: "<<screen_w<<std::endl;
    glUniform1i(glGetUniformLocation(sProgram.ID, "h"), screen_h);
    glUniform1i(glGetUniformLocation(sProgram.ID, "w"), screen_w);
    glDrawArrays(GL_TRIANGLES, 0, draw_N*3);
}