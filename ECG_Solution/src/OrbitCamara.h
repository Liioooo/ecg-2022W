//
// Created by preis on 07/12/2022.
//

#ifndef ECG_SOLUTION_ORBITCAMARA_H
#define ECG_SOLUTION_ORBITCAMARA_H


#include "CamaraSystem.h"
#include "glm/trigonometric.hpp"

class OrbitCamara : public CamaraSystem {
public:
    OrbitCamara(InputManager* inputManager, INIReader* iniReader);

    void update() override;
    glm::mat4 getVpMatrix() const override;

private:
    glm::vec3 camaraCenter = glm::vec3(0, 0, 0);
    glm::vec3 camaraDirection{};
    glm::mat4 projection;
    glm::mat4 viewProjection = glm::mat4(1.0f);
    glm::vec3 worldUp = glm::normalize(glm::vec3(0, 1, 0));
    float orbitRadius = 6;
    float pitch = glm::radians(0.0f);
    float yaw = glm::radians(90.0f);
    float sensitivity = 0.008f;
    bool camaraDirty = true;

    void calculateViewProjectionMatrix();
};


#endif //ECG_SOLUTION_ORBITCAMARA_H
