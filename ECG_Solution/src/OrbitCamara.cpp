//
// Created by preis on 07/12/2022.
//

#include "OrbitCamara.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

OrbitCamara::OrbitCamara(InputManager *inputManager, INIReader *iniReader) : CamaraSystem(inputManager, iniReader) {
    float fovy = glm::radians(iniReader->GetReal("camera", "fov", 60.0f));
    float aspect = iniReader->GetReal("window", "width", 800) / iniReader->GetReal("window", "height", 800);
    float zNear = iniReader->GetReal("camera", "near", 0.1f);
    float zFar = iniReader->GetReal("camera", "far", 10.0f);
    projection = glm::perspective(fovy, aspect, zNear, zFar);

    camaraDirection = glm::normalize(glm::vec3(cos(pitch) * cos(yaw),sin(pitch),cos(pitch) * sin(yaw)));
    camaraEyePos = camaraCenter - camaraDirection * orbitRadius;

    inputManager->addScrollListener([this](double xOffset, double yOffset) {
        orbitRadius -= yOffset;
        if (orbitRadius < 2) orbitRadius = 2;
        camaraDirty = true;
    });
}

void OrbitCamara::update() {
    if (inputManager->leftMouseButtonPressed || inputManager->rightMouseButtonPressed) {
        glm::vec2 mousePosDelta = inputManager->getMousePosDelta();

        if (inputManager->leftMouseButtonPressed) {
            yaw -= std::fmod(mousePosDelta.x * sensitivity, glm::radians(360.0f));

            pitch -= mousePosDelta.y * sensitivity;
            if (pitch > glm::radians(89.5f)) pitch = glm::radians(89.5f);
            if (pitch < -glm::radians(89.5f)) pitch = -glm::radians(89.5f);

            camaraDirection = glm::normalize(glm::vec3(cos(pitch) * cos(yaw),sin(pitch),cos(pitch) * sin(yaw)));
        }

        if (inputManager->rightMouseButtonPressed) {
            glm::vec3 camaraX = glm::normalize(glm::cross(camaraDirection, worldUp));

            glm::mat4 camaraTranslation = glm::mat4(1.0f);
            camaraTranslation = glm::translate(camaraTranslation, camaraX * mousePosDelta.x * sensitivity);
            camaraTranslation = glm::translate(camaraTranslation, glm::cross(camaraX, camaraDirection) * mousePosDelta.y * sensitivity);

            camaraCenter = camaraTranslation * glm::vec4(camaraCenter, 1.0f);
        }

        camaraDirty = true;
    }

    if (camaraDirty) {
        camaraEyePos = camaraCenter - camaraDirection * orbitRadius;
        calculateViewMatrix();
        camaraDirty = false;
    }
}

glm::vec3 OrbitCamara::getCamaraEyePos() const {
    return camaraEyePos;
}

glm::mat4 OrbitCamara::getViewMatrix() const {
    return view;
}

glm::mat4 OrbitCamara::getProjectionMatrix() const {
    return projection;
}

void OrbitCamara::calculateViewMatrix() {
    glm::vec3 camaraX = glm::normalize(glm::cross(worldUp, camaraDirection));
    glm::vec3 camaraY = glm::cross(camaraDirection, camaraX);

    glm::mat4 translation = glm::mat4(1.0f);
    translation = glm::translate(translation, camaraEyePos);

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = camaraX.x;
    rotation[1][0] = camaraX.y;
    rotation[2][0] = camaraX.z;
    rotation[0][1] = camaraY.x;
    rotation[1][1] = camaraY.y;
    rotation[2][1] = camaraY.z;
    rotation[0][2] = camaraDirection.x;
    rotation[1][2] = camaraDirection.y;
    rotation[2][2] = camaraDirection.z;

    view = rotation * translation;
}
