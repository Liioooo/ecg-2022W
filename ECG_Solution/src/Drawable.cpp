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

void Drawable::addRotation(float angle, float x, float y, float z) {
    Rotation rot = Rotation();
    rot.angle = glm::radians(angle);
    rot.axis = glm::vec3(x, y, z);
    rotations.push_back(rot);
    modelMatrixDirty = true;
}

void Drawable::clearRotations() {
    rotations.clear();
    modelMatrixDirty = true;
}

void Drawable::updateModelMatrix() {
    if (modelMatrixDirty) {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        for (const auto &rot: rotations) {
            modelMatrix = glm::rotate(modelMatrix, rot.angle, rot.axis);
        }
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrixDirty = false;
    }
}

void Drawable::applyModelMatrix() const {
    shader->setMat4("model", modelMatrix);
}

Shader* Drawable::getShader() const {
    return shader;
}
