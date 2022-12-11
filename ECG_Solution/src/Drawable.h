//
// Created by preis on 08/10/2022.
//
#ifndef ECG_SOLUTION_DRAWABLE_H
#define ECG_SOLUTION_DRAWABLE_H

#include "Shader.h"
#include "glm/detail/type_vec3.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "Material.h"
#include <GLFW/glfw3.h>
#include <vector>

class Drawable {
public:
    explicit Drawable(Shader* shader, Material* material) : shader(shader), material(material) {}

    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setRotation(float x, float y, float z);
    Shader* getShader() const;
    virtual void draw();

protected:
    Shader* shader;

private:
    Material* material;
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    bool modelMatrixDirty = true;

    void updateModelMatrix();
    void applyModelMatrix() const;
};

#endif // ECG_SOLUTION_DRAWABLE_H