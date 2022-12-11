//
// Created by preis on 06/12/2022.
//

#include <unordered_set>
#include <typeindex>
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

void Renderer::setAmbientLightIntensity(float ia) {
    ambientLightIntensity = ia;
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
            shader->setVec3("eyePos", camaraSystem->getCamaraEyePos());
            shader->setFloat("ia", ambientLightIntensity);
            setupLightsForShader(shader);
        }
        drawable->draw();
    }
}

void Renderer::setupLightsForShader(Shader *shader) {
    std::unordered_map<std::string, int> lightTypeCount;
    for (const auto &light: lights) {
        const std::string lightAmountUnifName = light->getLightAmountUniformName();

        if (lightTypeCount.count(lightAmountUnifName) == 0) {
            lightTypeCount[lightAmountUnifName] = 1;
            light->setUniforms(shader, 0);
        } else {
            light->setUniforms(shader, lightTypeCount[lightAmountUnifName]);
            lightTypeCount[lightAmountUnifName] = lightTypeCount[lightAmountUnifName] + 1;
        }
    }
    for (const auto &item: lightTypeCount) {
        shader->setInt(item.first, item.second);
    }
}
