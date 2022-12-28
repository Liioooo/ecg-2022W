//
// Created by preis on 08/10/2022.
//
#pragma once

#include "../Drawable.h"
#include "../../Utils.h"

class Teapot : public Drawable {
public:
    Teapot(Shader* shader, Material* material) : Drawable(shader, material) {}

    void draw() override {
        Drawable::draw();
        drawTeapot();
    }
};
