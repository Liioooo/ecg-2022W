//
// Created by preis on 29/12/2022.
//

#include "GL/glew.h"
#include "Skybox.h"
#include "glm/detail/type_mat4x4.hpp"

Skybox::Skybox() {
    GLuint vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);

    float vertices[] = {
        -1.0f, 1.0f, 1.0f, // left_top_front_0
        -1.0f, -1.0f, 1.0f, // left_bottom_front_1
        1.0f, 1.0f, 1.0f, // right_top_front_2
        1.0f, -1.0f, 1.0f, // right_bottom_front_3
        1.0f, 1.0f, -1.0f, // right_top_back_4
        1.0f, -1.0f, -1.0f, // right_bottom_back_5
        -1.0f, 1.0f, -1.0f, // left_top_back_6
        -1.0f, -1.0f, -1.0f, // left_bottom_back_7
    };

    unsigned int indices[] = {
        7, 5, 4,
        4, 6, 7,
        3, 2, 4,
        4, 5, 3,
        1, 7, 0,
        0, 7, 6,
        0, 2, 3,
        3, 1, 0,
        6, 4, 0,
        0, 4, 2,
        1, 3, 7,
        5, 7, 3
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    skyboxShader = new Shader("assets/shader/skybox.vert", "assets/shader/skybox.frag");
}

Skybox::~Skybox() {
    glDeleteVertexArrays(1, &vao);
    delete skyboxShader;
}

void Skybox::render(CubeTexture *texture, const glm::mat4 &view, const glm::mat4 &projection) {
    skyboxShader->use();
    glDepthFunc(GL_LEQUAL);

    glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
    skyboxShader->setMat4("view", skyboxView);
    skyboxShader->setMat4("projection", projection);

    glBindVertexArray(vao);
    texture->bindTexture(skyboxShader, 0, "skybox");
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    glDepthFunc(GL_LESS);
}
