//
// Created by preis on 09/10/2022.
//
#pragma once


#include <vector>
#include "Drawable.h"
#include "INIReader.h"
#include "glm/trigonometric.hpp"
#include "InputManager.h"

class CamaraSystem {
public:
    CamaraSystem(Shader* shader, InputManager* inputManager, INIReader iniReader);

    void addDrawable(Drawable* drawable);
    void updateCamara();
    void drawObjects();

private:
    Shader* shader;
    InputManager* inputManager;
    glm::vec3 camaraCenter = glm::vec3(0, 0, 0);
    glm::vec3 camaraDirection{};
    glm::vec3 worldUp = glm::normalize(glm::vec3(0, 1, 0));
    float orbitRadius = 6;
    std::vector<Drawable*> drawables;
    float pitch = glm::radians(0.0f);
    float yaw = glm::radians(90.0f);
    float sensitivity = 0.008f;
    bool camaraDirty = true;

    void calculateViewMatrix() const;
};
