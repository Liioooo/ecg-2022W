//
// Created by preis on 06/12/2022.
//

#include <unordered_set>
#include "Renderer.h"

void Renderer::setCamaraSystem(CamaraSystem *camaraSystem) {
    this->camaraSystem = camaraSystem;
}

void Renderer::addDrawable(Drawable *drawable) {
    drawables.push_back(drawable);
}

void Renderer::addLight(Light* light) {
    lights.push_back(light);
}

void Renderer::renderScene() {
    std::unordered_set<Shader*> setUpShaders;

    camaraSystem->update();

    for (const auto &drawable: drawables) {
        auto* shader = drawable->getShader();
        shader->use();
        if (setUpShaders.count(shader) == 0) {
            setUpShaders.insert(shader);
            shader->setMat4("vp", camaraSystem->getVpMatrix());
        }
        drawable->draw();
    }
}
