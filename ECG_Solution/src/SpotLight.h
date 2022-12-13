//
// Created by preis on 11/12/2022.
//

#ifndef ECG_SOLUTION_SPOTLIGHT_H
#define ECG_SOLUTION_SPOTLIGHT_H

#include "Light.h"
#include "glm/vec3.hpp"
#include "Shader.h"

class SpotLight : public Light {
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, const glm::vec3 color, float cutOff, float aConstant, float aLinear, float aQuadratic) :
    position(position), direction(direction), color(color), cutOff(cutOff), aConstant(aConstant), aLinear(aLinear), aQuadratic(aQuadratic) {};

    void setUniforms(Shader* shader, int arrayPos) const override {
        shader->setVec3("spotLights[" + std::to_string(arrayPos) + "].position", position);
        shader->setVec3("spotLights[" + std::to_string(arrayPos) + "].direction", direction);
        shader->setVec3("spotLights[" + std::to_string(arrayPos) + "].color", color);
        shader->setFloat("spotLights[" + std::to_string(arrayPos) + "].cutOff", cutOff);
        shader->setFloat("spotLights[" + std::to_string(arrayPos) + "].aConstant", aConstant);
        shader->setFloat("spotLights[" + std::to_string(arrayPos) + "].aLinear", aLinear);
        shader->setFloat("spotLights[" + std::to_string(arrayPos) + "].aQuadratic", aQuadratic);
    }

    std::string getLightAmountUniformName() const override {
        return "spotLightCount";
    }

private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float cutOff;
    float aConstant;
    float aLinear;
    float aQuadratic;

};

#endif //ECG_SOLUTION_SPOTLIGHT_H
