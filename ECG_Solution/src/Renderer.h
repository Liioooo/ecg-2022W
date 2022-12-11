//
// Created by preis on 06/12/2022.
//

#ifndef ECG_SOLUTION_RENDERER_H
#define ECG_SOLUTION_RENDERER_H


#include "Drawable.h"
#include "CamaraSystem.h"
#include "Light.h"

class Renderer {
public:
    Renderer() {};

    void setCamaraSystem(CamaraSystem* camaraSystem);
    void addDrawable(Drawable* drawable);
    void addLight(Light* light);
    void setAmbientLightIntensity(float ia);
    void renderScene();

private:
    CamaraSystem* camaraSystem;
    std::vector<Drawable*> drawables;
    std::vector<Light*> lights;
    float ambientLightIntensity = 1;

    void setupLightsForShader(Shader* shader);
};


#endif //ECG_SOLUTION_RENDERER_H
