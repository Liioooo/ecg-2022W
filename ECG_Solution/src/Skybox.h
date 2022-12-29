//
// Created by preis on 29/12/2022.
//

#ifndef ECG_SOLUTION_SKYBOX_H
#define ECG_SOLUTION_SKYBOX_H


#include "CubeTexture.h"

class Skybox {
public:
    Skybox();

    void render(CubeTexture* texture, const glm::mat4 &view, const glm::mat4 &projection);

private:
    unsigned int vao{};
    Shader* skyboxShader;
};


#endif //ECG_SOLUTION_SKYBOX_H
