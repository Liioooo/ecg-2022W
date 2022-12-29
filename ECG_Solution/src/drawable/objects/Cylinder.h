//
// Created by preis on 06/11/2022.
//
#pragma once

#include "../DrawableMesh.h"
#include "glm/ext/scalar_constants.hpp"

class Cylinder : public DrawableMesh {
public:
    Cylinder(Shader* shader, Material* material, float radius, float height, int segments) :
    DrawableMesh(shader, material), radius(radius), height(height), segments(segments) {}

protected:
    void generateMesh() override {
        vertices.emplace_back(0.0f, height / 2, 0, 0, 1, 0, 0.5, 0.5);
        vertices.emplace_back(0.0f, -height / 2, 0, 0, -1, 0, 0.5, 0.5);

        // Top
        for (int i = 0; i < segments; ++i) {
            float theta = 2 * glm::pi<float>() * i / segments;
            vertices.emplace_back(
                    radius * sin(theta),
                    height / 2,
                    radius * cos(theta),
                    0,
                    1,
                    0,
                    sin(theta) + 0.5,
                    cos(theta) + 0.5
            );
        }

        // Bottom
        for (int i = 0; i < segments; ++i) {
            float theta = 2 * glm::pi<float>() * i / segments;
            vertices.emplace_back(
                    radius * sin(theta),
                    -height / 2,
                    radius * cos(theta),
                    0,
                    -1,
                    0,
                    sin(theta) + 0.5,
                    cos(theta) + 0.5
            );
        }

        // Around Top
        for (int i = 0; i < segments; i++) {
            float theta = 2 * glm::pi<float>() * i / segments;
            glm::vec3 vertexPos(radius * sin(theta), height / 2, radius * cos(theta));
            if (i == (int)((segments + 1) / 2)) {
                vertices.emplace_back(
                        vertexPos.x,
                        vertexPos.y,
                        vertexPos.z,
                        vertexPos.x,
                        0,
                        vertexPos.z,
                        1 + atan2(vertexPos.x, vertexPos.z) / glm::two_pi<float>() + 0.5f,
                        1
                );
            }
            vertices.emplace_back(
                    vertexPos.x,
                    vertexPos.y,
                    vertexPos.z,
                    vertexPos.x,
                    0,
                    vertexPos.z,
                    atan2(vertexPos.x, vertexPos.z) / glm::two_pi<float>() + 0.5f,
                    1
            );
        }

        // Around Bottom
        for (int i = 0; i < segments; i++) {
            float theta = 2 * glm::pi<float>() * i / segments;
            glm::vec3 vertexPos(radius * sin(theta), -height / 2, radius * cos(theta));
            if (i == (int)((segments + 1) / 2)) {
                vertices.emplace_back(
                        vertexPos.x,
                        vertexPos.y, vertexPos.z,
                        vertexPos.x,
                        0,
                        vertexPos.z,
                        1 + atan2(vertexPos.x, vertexPos.z) / glm::two_pi<float>() + 0.5f,
                        0
                );
            }
            vertices.emplace_back(
                    vertexPos.x,
                    vertexPos.y, vertexPos.z,
                    vertexPos.x,
                    0,
                    vertexPos.z,
                    atan2(vertexPos.x, vertexPos.z) / glm::two_pi<float>() + 0.5f,
                    0
            );
        }

        for (int i = 2; i < 2 + segments; i++) {
            indices.push_back(0);
            indices.push_back(i);
            if (i == 1 + segments) {
                indices.push_back(2);
            } else {
                indices.push_back(i + 1);
            }
        }

        for (int i = 2 + segments; i < 2 + 2 * segments; i++) {
            indices.push_back(1);
            if (i == 1 + 2 * segments) {
                indices.push_back(2 + segments);
            } else {
                indices.push_back(i + 1);
            }
            indices.push_back(i);
        }

        for (int i = 2 + 2 * segments; i < 3 + 3 * segments; i++) {
            indices.push_back(i);
            indices.push_back(segments + i + 1);
            if (i == 2 + 3 * segments) {
                indices.push_back(2 + 2 * segments);
            } else {
                indices.push_back(i + 1);
            }

            indices.push_back(segments + i + 1);
            if (i == 2 + 3 * segments) {
                indices.push_back(3 + 2 * segments + segments);
                indices.push_back(2 + 2 * segments);
            } else {
                indices.push_back(segments + i + 2);
                indices.push_back(i + 1);
            }
            if (i + 1 == 2 + 2 * segments + (int)((segments + 1) / 2)) {
                i++;
            }
        }

    }

private:
    float radius;
    float height;
    int segments;

};
