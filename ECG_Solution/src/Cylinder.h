//
// Created by preis on 06/11/2022.
//
#pragma once

#include "DrawableMesh.h"
#include "glm/ext/scalar_constants.hpp"

class Cylinder : public DrawableMesh {
public:
    Cylinder(Shader* shader, glm::vec3 color, float radius, float height, int segments) :
    DrawableMesh(shader), color(color), radius(radius), height(height), segments(segments) {}

    void draw() override {
        DrawableMesh::draw();
        shader->setVec3("color", color);
        drawMesh();
    }

protected:
    void generateMesh() override {
        vertices.emplace_back(0.0f, height / 2, 0);
        vertices.emplace_back(0.0f, -height / 2, 0);

        float pi2 = 2 * glm::pi<float>();
        float theta = 0;
        while (theta < pi2) {
            vertices.emplace_back(radius * sin(theta), height / 2, radius * cos(theta));
            theta += pi2 / (float)segments;
        }

        for (int i = 2; i < segments + 2; i++) {
            glm::vec3 vertex = vertices[i];
            vertices.emplace_back(vertex.x, -height / 2, vertex.z);
        }

        for (int i = 0; i < segments; i++) {
            indices.push_back(0);
            indices.push_back(i + 2);
            if (i == segments - 1) {
                indices.push_back(2);
            } else {
                indices.push_back(i + 3);
            }
        }

        for (int i = segments; i < 2 * segments; i++) {
            indices.push_back(1);
            if (i == 2 * segments - 1) {
                indices.push_back(segments + 2);
            } else {
                indices.push_back(i + 3);
            }
            indices.push_back(i + 2);
        }

        for (int i = 0; i < segments; i++) {
            indices.push_back(i + 2);
            indices.push_back(segments + i + 2);
            if (i == segments - 1) {
                indices.push_back(2);
            } else {
                indices.push_back(i + 3);
            }

            indices.push_back(segments + i + 2);
            if (i == segments - 1) {
                indices.push_back(segments + 2);
                indices.push_back(2);
            } else {
                indices.push_back(segments + i + 3);
                indices.push_back(i + 3);
            }
        }

    }

private:
    glm::vec3 color;
    float radius;
    float height;
    int segments;

};
