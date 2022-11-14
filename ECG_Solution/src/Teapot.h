//
// Created by preis on 08/10/2022.
//
#pragma once

#include "Drawable.h"
#include "Utils.h"

class Teapot : public Drawable {
public:
    Teapot(Shader* shader, glm::vec3 color) : Drawable(shader), color(color) {}

    void draw() const override  {
        Drawable::draw();
        shader->setVec3("color", color);
        drawTeapot();
    }
private:
    glm::vec3 color;
};
