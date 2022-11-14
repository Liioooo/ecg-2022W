//
// Created by preis on 06/11/2022.
//
#pragma once

#include "DrawableMesh.h"

class Box : public DrawableMesh {
public:
    Box(Shader* shader, glm::vec3 color, float width, float height, float depth) :
    DrawableMesh(shader), color(color), width(width), height(height), depth(depth) {}

    void draw() const override {
        Drawable::draw();
        shader->setVec3("color", color);
        drawMesh();
    }

protected:
    void generateMesh() override {
        vertices.emplace_back(-0.5f * width, 0.5f * height, 0.5f * depth); // left_top_front
        vertices.emplace_back(-0.5f * width,  -0.5f * height, 0.5f * depth ); // left_bottom_front
        vertices.emplace_back(0.5f * width, 0.5f * height, 0.5f * depth); // right_top_front
        vertices.emplace_back(0.5f * width, -0.5f * height, 0.5f * depth); // right_bottom_front
        vertices.emplace_back(-0.5f * width, 0.5f * height, -0.5f * depth); // left_top_back
        vertices.emplace_back(-0.5f * width, -0.5f * height, -0.5f * depth); // left_bottom_back
        vertices.emplace_back(0.5f * width, 0.5f * height, -0.5f * depth); // right_top_back
        vertices.emplace_back(0.5f * width, -0.5f * height, -0.5f * depth); // right_bottom_back

        // front
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(3);

        // right
        indices.push_back(0);
        indices.push_back(4);
        indices.push_back(1);

        indices.push_back(1);
        indices.push_back(4);
        indices.push_back(5);

        // left
        indices.push_back(6);
        indices.push_back(2);
        indices.push_back(3);

        indices.push_back(3);
        indices.push_back(7);
        indices.push_back(6);

        // back
        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(5);

        indices.push_back(5);
        indices.push_back(6);
        indices.push_back(7);

        // top
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(6);

        indices.push_back(0);
        indices.push_back(6);
        indices.push_back(4);

        // bottom
        indices.push_back(7);
        indices.push_back(3);
        indices.push_back(1);

        indices.push_back(5);
        indices.push_back(7);
        indices.push_back(1);
    }

private:
    glm::vec3 color;
    float width;
    float height;
    float depth;
};
