//
// Created by preis on 08/10/2022.
//

#include "Drawable.h"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_transform.hpp"

void Drawable::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    modelMatrixDirty = true;
}

void Drawable::setScale(float x, float y, float z) {
    scale = glm::vec3(x, y, z);
    modelMatrixDirty = true;
}

void Drawable::setRotation(float x, float y, float z) {
    rotation = glm::vec3(x, y, z);
    modelMatrixDirty = true;
}

void Drawable::updateModelMatrix() {
    if (modelMatrixDirty) {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrixDirty = false;
    }
}

Shader* Drawable::getShader() const {
    return shader;
}

void Drawable::draw() {
    updateModelMatrix();
    shader->setMat4("model", modelMatrix);
    material->setUniforms(shader);
}

void Drawable::drawDebug(Shader* shader) {
    updateModelMatrix();
    shader->setMat4("model", modelMatrix);
    material->setUniforms(shader);
}
