//
// Created by preis on 11/12/2022.
//

#ifndef ECG_SOLUTION_POINTLIGHT_H
#define ECG_SOLUTION_POINTLIGHT_H

#include "Light.h"
#include "glm/vec3.hpp"
#include "Shader.h"

class PointLight : public Light {
public:
    PointLight(glm::vec3 position, const glm::vec3 color, float aConstant, float aLinear, float aQuadratic) :
    position(position), color(color), aConstant(aConstant), aLinear(aLinear), aQuadratic(aQuadratic) {};

    void setUniforms(Shader* shader, int arrayPos) const override {
        shader->setVec3("pointLights[" + std::to_string(arrayPos) + "].position", position);
        shader->setVec3("pointLights[" + std::to_string(arrayPos) + "].color", color);
        shader->setFloat("pointLights[" + std::to_string(arrayPos) + "].aConstant", aConstant);
        shader->setFloat("pointLights[" + std::to_string(arrayPos) + "].aLinear", aLinear);
        shader->setFloat("pointLights[" + std::to_string(arrayPos) + "].aQuadratic", aQuadratic);
    }

    std::string getLightAmountUniformName() const override {
        return "pointLightCount";
    }

private:
    glm::vec3 position;
    glm::vec3 color;
    float aConstant;
    float aLinear;
    float aQuadratic;

};

#endif //ECG_SOLUTION_POINTLIGHT_H
