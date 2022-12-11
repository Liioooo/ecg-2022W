//
// Created by preis on 11/12/2022.
//

#ifndef ECG_SOLUTION_DIRECTIONALLIGHT_H
#define ECG_SOLUTION_DIRECTIONALLIGHT_H

#include "Light.h"
#include "glm/vec3.hpp"

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 direction, glm::vec3 color) : direction(direction), color(color) {};

    void setUniforms(Shader *shader, int arrayPos) const override {
        shader->setVec3("dirLights[" + std::to_string(arrayPos) + "].direction", direction);
        shader->setVec3("dirLights[" + std::to_string(arrayPos) + "].color", color);
        shader->setFloat("dirLights[" + std::to_string(arrayPos) + "].t44", 1.0);
    }

    std::string getLightAmountUniformName() const override {
        return "dirLightCount";
    }

private:
    glm::vec3 direction;
    glm::vec3 color;
};

#endif //ECG_SOLUTION_DIRECTIONALLIGHT_H
