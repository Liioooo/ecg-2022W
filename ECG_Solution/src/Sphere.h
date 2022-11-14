//
// Created by preis on 08/11/2022.
//
#pragma once

#include "DrawableMesh.h"
#include "glm/ext/scalar_constants.hpp"

class Sphere : public DrawableMesh {
public:
    Sphere(Shader* shader, glm::vec3 color, float radius, int n, int m) :
    DrawableMesh(shader), color(color), radius(radius), n(n), m(m) {}

    void draw() const override {
        DrawableMesh::draw();
        shader->setVec3("color", color);
        drawMesh();
    }

protected:
    void generateMesh() override {

        vertices.emplace_back(0, radius, 0);
        vertices.emplace_back(0, -radius, 0);

        // latitude
        for (int i = 1; i < m; i++) {
            float latAngle = glm::pi<float>() * i / m;
            float xz = radius * sin(latAngle);
            float y = radius * cos(latAngle);

            // longitude
            for (int j = 0; j < n; j++) {
                float lonAngle = 2 * glm::pi<float>() * j / n; // 0 to 2pi
                vertices.emplace_back(xz * sin(lonAngle), y, xz * cos(lonAngle));
            }
        }

        for (int i = 2; i < 2 + n; i++) {
            indices.push_back(0);
            indices.push_back(i);
            if (i == 1 + n) {
                indices.push_back(2);
            } else {
                indices.push_back(i + 1);
            }
        }

        for (int i = 2 + (m - 2) * n; i < 2 + (m - 1) * n; i++) {
            indices.push_back(1);
            if (i == 1 + (m - 1) * n) {
                indices.push_back(2 + (m - 2) * n);
            } else {
                indices.push_back(i + 1);
            }
            indices.push_back(i);
        }

        for (int i = 0; i < m - 2; i++) {
            for (int j = 2 + i * n; j < 2 + i * n + n; j++) {
                indices.push_back(j);
                indices.push_back(j + n);
                if (j == 1 + i * n + n) {
                    indices.push_back(2 + i * n);
                } else {
                    indices.push_back(j + 1);
                }

                if (j == 1 + i * n + n) {
                    indices.push_back(j + n);
                    indices.push_back(2 + i * n + n);
                    indices.push_back(2 + i * n);
                } else {
                    indices.push_back(j + n);
                    indices.push_back(j + n + 1);
                    indices.push_back(j + 1);
                }
            }

        }

    }

private:
    glm::vec3 color;
    float radius;
    int n;
    int m;
};
