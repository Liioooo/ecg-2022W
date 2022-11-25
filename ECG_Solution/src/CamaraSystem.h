//
// Created by preis on 09/10/2022.
//
#ifndef ECG_SOLUTION_CAMARASYSTEM_H
#define ECG_SOLUTION_CAMARASYSTEM_H

#include <vector>
#include "Drawable.h"
#include "INIReader.h"
#include "glm/trigonometric.hpp"
#include "InputManager.h"

class CamaraSystem {
public:
    CamaraSystem(InputManager* inputManager, INIReader* iniReader);

    void addDrawable(Drawable* drawable);
    void updateCamara();
    void drawObjects();

private:
    InputManager* inputManager;
    glm::vec3 camaraCenter = glm::vec3(0, 0, 0);
    glm::vec3 camaraDirection{};
    glm::mat4 projection;
    glm::mat4 viewProjection = glm::mat4(1.0f);
    glm::vec3 worldUp = glm::normalize(glm::vec3(0, 1, 0));
    float orbitRadius = 6;
    std::vector<Drawable*> drawables;
    float pitch = glm::radians(0.0f);
    float yaw = glm::radians(90.0f);
    float sensitivity = 0.008f;
    bool camaraDirty = true;

    void calculateViewProjectionMatrix();
};

#endif // ECG_SOLUTION_CAMARASYSTEM_H
