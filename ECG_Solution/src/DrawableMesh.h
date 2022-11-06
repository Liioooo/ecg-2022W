//
// Created by preis on 06/11/2022.
//
#pragma once

#include "Drawable.h"
#include "GL/glew.h"

class DrawableMesh : public Drawable {
public:
    DrawableMesh(Shader* shader) : Drawable(shader) {}

    /**
     * Calls generateMesh() and must be called before drawing the Drawable
     */
    void init();

protected:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    void drawMesh();
    virtual void generateMesh() = 0;

private:
    GLuint vao;
};
