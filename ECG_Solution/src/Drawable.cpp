//
// Created by preis on 08/10/2022.
//

#include "Drawable.h"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_transform.hpp"

void Drawable::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
}

void Drawable::setScale(float x, float y, float z) {
    scale = glm::vec3(x, y, z);
}

void Drawable::addRotation(float angle, float x, float y, float z) {
    Rotation* rot = new Rotation();
    rot->angle = glm::radians(angle);
    rot->axis = glm::vec3(x, y, z);
    rotations.push_back(rot);
}

void Drawable::clearRotations() {
    rotations.clear();
}

void Drawable::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(this->modelMatrix, this->position);
    for (const auto &rot: this->rotations) {
        this->modelMatrix = glm::rotate(this->modelMatrix, rot->angle, rot->axis);
    }
    modelMatrix = glm::scale(this->modelMatrix, this->scale);
}

void Drawable::applyModelMatrix() {
    shader->setMat4("model", modelMatrix);
}
