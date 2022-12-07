//
// Created by preis on 06/12/2022.
//

#ifndef ECG_SOLUTION_RENDERER_H
#define ECG_SOLUTION_RENDERER_H


#include "Drawable.h"
#include "CamaraSystem.h"

class Renderer {
public:
    Renderer() {};

    void setCamaraSystem(CamaraSystem* camaraSystem);
    void addDrawable(Drawable* drawable);
    void addLight();
    void renderScene();

private:
    CamaraSystem* camaraSystem;
    std::vector<Drawable*> drawables;
};


#endif //ECG_SOLUTION_RENDERER_H
