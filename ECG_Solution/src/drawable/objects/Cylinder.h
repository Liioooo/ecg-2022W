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
        vertices.emplace_back(0.0f, height / 2, 0, 0, 1, 0);
        vertices.emplace_back(0.0f, -height / 2, 0, 0, -1, 0);

        // Top
        for (int i = 0; i < segments; ++i) {
            float theta = 2 * glm::pi<float>() * i / segments;
            vertices.emplace_back(radius * sin(theta), height / 2, radius * cos(theta), 0, 1, 0);
        }

        // Bottom
        for (int i = 0; i < segments; ++i) {
            float theta = 2 * glm::pi<float>() * i / segments;
            vertices.emplace_back(radius * sin(theta), -height / 2, radius * cos(theta), 0, -1, 0);
        }

        // Around Top
        for (int i = 2; i < segments + 2; i++) {
            float theta = 2 * glm::pi<float>() * i / segments;
            glm::vec3 vertexPos(radius * sin(theta), height / 2, radius * cos(theta));
            vertices.emplace_back(vertexPos.x, vertexPos.y, vertexPos.z, vertexPos.x, 0, vertexPos.z);
        }

        // Around Bottom
        for (int i = 2; i < segments + 2; i++) {
            float theta = 2 * glm::pi<float>() * i / segments;
            glm::vec3 vertexPos(radius * sin(theta), -height / 2, radius * cos(theta));
            vertices.emplace_back(vertexPos.x, vertexPos.y, vertexPos.z, vertexPos.x, 0, vertexPos.z);
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

        for (int i = 2 + 2 * segments; i < 2 + 3 * segments; i++) {
            indices.push_back(i);
            indices.push_back(segments + i);
            if (i == 1 + 3 * segments) {
                indices.push_back(2 + 2 * segments);
            } else {
                indices.push_back(i + 1);
            }

            indices.push_back(segments + i);
            if (i == 1 + 3 * segments) {
                indices.push_back(2 + 3 * segments);
                indices.push_back(2 + 2 * segments);
            } else {
                indices.push_back(segments + i + 1);
                indices.push_back(i + 1);
            }
        }

    }

private:
    float radius;
    float height;
    int segments;

};
