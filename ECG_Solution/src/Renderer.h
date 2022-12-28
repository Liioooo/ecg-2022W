//
// Created by preis on 06/12/2022.
//

#ifndef ECG_SOLUTION_RENDERER_H
#define ECG_SOLUTION_RENDERER_H


#include "drawable/Drawable.h"
#include "CamaraSystem.h"
#include "lights/Light.h"

class Renderer {
public:
    Renderer() {};

    void setCamaraSystem(CamaraSystem* camaraSystem);
    void setDebugNormals(const bool &enabled);
    void addDrawable(Drawable* drawable);
    void addLight(Light* light);
    void setAmbientLightIntensity(float ia);
    void renderScene();

    const bool& isDebugNormals = _debugNormals;

private:
    CamaraSystem* camaraSystem;
    std::vector<Drawable*> drawables;
    std::vector<Light*> lights;
    float ambientLightIntensity = 1;
    bool _debugNormals = false;
    Shader* normalDebugShader = nullptr;

    void setupLightsForShader(Shader* shader);
};


#endif //ECG_SOLUTION_RENDERER_H
