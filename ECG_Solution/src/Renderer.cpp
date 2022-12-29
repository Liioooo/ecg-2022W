//
// Created by preis on 06/12/2022.
//

#include <unordered_set>
#include "Renderer.h"

void Renderer::setCamaraSystem(CamaraSystem *camaraSystem) {
    this->camaraSystem = camaraSystem;
}

void Renderer::setDebugNormals(const bool &enabled) {
    _debugNormals = enabled;
    if (normalDebugShader == nullptr) {
        normalDebugShader = new Shader("assets/shader/shader_normal.vert", "assets/shader/shader_normal.frag", "assets/shader/shader_normal.geom");
    }
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

void Renderer::setSkyboxTexture(CubeTexture *texture) {
    skyboxTexture = texture;
    if (skybox == nullptr) {
        skybox = new Skybox();
    }
}

void Renderer::renderScene() {
    std::unordered_set<Shader*> setUpShaders;

    camaraSystem->update();

    for (const auto &drawable: drawables) {
        auto* shader = drawable->getShader();
        shader->use();
        if (setUpShaders.count(shader) == 0) {
            setUpShaders.insert(shader);
            shader->setMat4("view", camaraSystem->getViewMatrix());
            shader->setMat4("projection", camaraSystem->getProjectionMatrix());
            shader->setVec3("eyePos", camaraSystem->getCamaraEyePos());
            shader->setFloat("ia", ambientLightIntensity);
            setupLightsForShader(shader);

            if (skyboxTexture != nullptr) {
                skyboxTexture->bindTexture(shader, 3, "skyboxTexture");
            }
            shader->setBool("hasSkyboxTexture", skyboxTexture != nullptr);
        }
        drawable->draw();
    }
    if (_debugNormals) {
        normalDebugShader->use();
        normalDebugShader->setMat4("view", camaraSystem->getViewMatrix());
        normalDebugShader->setMat4("projection", camaraSystem->getProjectionMatrix());
        for (const auto &drawable: drawables) {
            drawable->drawDebug(normalDebugShader);
        }
    }
    if (skybox != nullptr) {
        skybox->render(skyboxTexture, camaraSystem->getViewMatrix(), camaraSystem->getProjectionMatrix());
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
