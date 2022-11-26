//
// Created by preis on 08/10/2022.
//
#ifndef ECG_SOLUTION_DRAWABLE_H
#define ECG_SOLUTION_DRAWABLE_H

#include "Shader.h"
#include "glm/detail/type_vec3.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include <GLFW/glfw3.h>
#include <vector>

struct Rotation {
    float angle;
    glm::vec3 axis;
};

class Drawable {
public:
    explicit Drawable(Shader* shader) : shader(shader) {}

    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void addRotation(float angle, float x, float y, float z);
    void clearRotations();
    void updateModelMatrix();
    void applyModelMatrix() const;
    Shader* getShader() const;
    virtual void draw() const = 0;

protected:
    Shader* shader;

private:
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    std::vector<Rotation> rotations;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    bool modelMatrixDirty = true;
};

#endif // ECG_SOLUTION_DRAWABLE_H