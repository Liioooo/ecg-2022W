//
// Created by preis on 08/11/2022.
//
#pragma once

#include "DrawableMesh.h"
#include "glm/ext/scalar_constants.hpp"

class Torus : public DrawableMesh {
public:
    Torus(Shader* shader, glm::vec3 color, float centerRadius, float tubeRadius, int ts, int cts) :
    DrawableMesh(shader), color(color), centerRadius(centerRadius), tubeRadius(tubeRadius), ts(ts), cts(cts) {}

    void draw() const override {
        shader->setVec3("color", color);
        drawMesh();
    }

protected:
    void generateMesh() override {
        for (int i = 0; i < ts; i++) {
            float phi = 2 * glm::pi<float>() * i / ts;
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);

            for (int j = 0; j < cts; ++j) {
                float theta = 2 * glm::pi<float>() * j / cts;
                float crPlusTrCosTheta = centerRadius + tubeRadius * cos(theta);
                vertices.emplace_back(crPlusTrCosTheta * cosPhi, crPlusTrCosTheta * sinPhi, tubeRadius * sin(theta));
            }
        }

        for (int i = 0; i < ts; i++) {
            for (int j = i * cts; j < (i + 1) * cts; j++) {
                if (i == ts - 1) {
                    indices.push_back(j - i * cts);
                } else {
                    indices.push_back(j + cts);
                }
                if (j == (i + 1) * cts - 1) {
                    indices.push_back(i * cts);
                } else {
                    indices.push_back(j + 1);
                }
                indices.push_back(j);


                if (i == ts - 1) {
                    indices.push_back(j - i * cts);
                } else {
                    indices.push_back(j + cts);
                }
                if (j == (i + 1) * cts - 1) {
                    if (i == ts - 1) {
                        indices.push_back(0);
                    } else {
                        indices.push_back(j + 1);
                    }
                    indices.push_back(i * cts);
                } else if (i == ts - 1) {
                    indices.push_back(j - i * cts + 1);
                    indices.push_back(j + 1);
                } else {
                    indices.push_back(j + cts + 1);
                    indices.push_back(j + 1);
                }

            }
        }


    }

private:
    glm::vec3 color;
    float centerRadius;
    float tubeRadius;
    int ts;
    int cts;
};
