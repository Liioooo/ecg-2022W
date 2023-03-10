//
// Created by preis on 09/10/2022.
//
#ifndef ECG_SOLUTION_CAMARASYSTEM_H
#define ECG_SOLUTION_CAMARASYSTEM_H

#include <vector>
#include "INIReader.h"
#include "glm/detail/type_mat4x4.hpp"
#include "InputManager.h"

class CamaraSystem {
public:
    CamaraSystem(InputManager* inputManager, INIReader* iniReader) : inputManager(inputManager), iniReader(iniReader) {};

    virtual void update() = 0;
    virtual glm::vec3 getCamaraEyePos() const = 0;
    virtual glm::mat4 getViewMatrix() const = 0;
    virtual glm::mat4 getProjectionMatrix() const = 0;

protected:
    InputManager* inputManager;
    INIReader* iniReader;

};

#endif // ECG_SOLUTION_CAMARASYSTEM_H
