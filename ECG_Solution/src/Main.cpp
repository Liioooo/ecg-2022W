/*
* Copyright 2021 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/

#include "Utils.h"
#include "Window.h"
#include "drawable/objects/Box.h"
#include "OrbitCamara.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"
#include "drawable/objects/Sphere.h"
#include "drawable/objects/Cylinder.h"
#include "drawable/objects/Torus.h"
#include "lights/SpotLight.h"


/* --------------------------------------------- */
// Prototypes
/* --------------------------------------------- */

/* --------------------------------------------- */
// Global variables
/* --------------------------------------------- */

/* --------------------------------------------- */
// Main
/* --------------------------------------------- */

int main(int argc, char **argv) {

    // init reader for ini files
    auto* reader = new INIReader("assets/settings.ini");


    /* --------------------------------------------- */
    // Init framework
    /* --------------------------------------------- */

    auto* window = new Window(reader);
    window->setCamaraSystem<OrbitCamara>();

    if (!initFramework()) {
        EXIT_WITH_ERROR("Failed to init framework")
    }

    window->getInputManager()->addKeyListener(GLFW_KEY_ESCAPE, [window]() {
        window->setShouldClose();
    });
    window->getInputManager()->addKeyListener(GLFW_KEY_F1, [window]() {
        window->setWireframeMode(!window->isWireframe);
    });
    window->getInputManager()->addKeyListener(GLFW_KEY_F2, [window]() {
        window->setBackfaceCulling(!window->isBackfaceCulling);
    });
    window->getInputManager()->addKeyListener(GLFW_KEY_F3, [window]() {
        window->getRenderer()->setDebugNormals(!window->getRenderer()->isDebugNormals);
    });

    window->getRenderer()->setSkyboxTexture(new CubeTexture({
        "assets/textures/cubemap/posx.dds",
        "assets/textures/cubemap/negx.dds",
        "assets/textures/cubemap/posy.dds",
        "assets/textures/cubemap/negy.dds",
        "assets/textures/cubemap/posz.dds",
        "assets/textures/cubemap/negz.dds"
    }));

    auto *phongShader = new Shader("assets/shader/shader_phong.vert", "assets/shader/shader_phong.frag");

    auto* box = new Box(phongShader, new Material(new Texture("assets/textures/wood_texture.dds"), 0.1f, 0.7f, 0.1f, 2.0f), 1.5f, 1.5f, 1.5f);
    box->init();
    box->setPosition(-1.4f, -1.0f, 0.0f);
    window->getRenderer()->addDrawable(box);

    auto* cylinder = new Cylinder(phongShader, new Material(new Texture("assets/textures/tiles_diffuse.dds"), new Texture("assets/textures/tiles_specular.dds"), 0.1f, 0.7f, 8.0f), 1.0f, 1.3f, 32);
    cylinder->init();
    cylinder->setPosition(1.4f, -1.0f, 0);
    window->getRenderer()->addDrawable(cylinder);

    auto* sphereTL = new Sphere(phongShader, new Material(new Texture("assets/textures/tiles_diffuse.dds"), new Texture("assets/textures/tiles_specular.dds"), 0.1f, 0.7f, 8.0f), 1, 64, 32);
    sphereTL->init();
    sphereTL->setPosition(0, 1.4f, 0);
    window->getRenderer()->addDrawable(sphereTL);

    auto* torus = new Torus(phongShader, new Material(glm::vec3(0.6, 0.6, 0.8), 0.1f, 0.5f, 0.3f, 2.0f), 4.5f, 0.5f, 48, 18);
    torus->init();
    torus->setPosition(0, 0, -4);
    torus->setScale(1, 0.9f, 1);
    window->getRenderer()->addDrawable(torus);

    window->getRenderer()->addLight(new DirectionalLight(glm::vec3(0, -1, -1), glm::vec3(0.8, 0.8, 0.8)));
    window->getRenderer()->addLight(new PointLight(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1, 0.4, 0.1));
    window->getRenderer()->addLight(new PointLight(glm::vec3(0, 0, -5), glm::vec3(1, 0.4, 0.4), 0.5, 0.2, 0.05));
    window->getRenderer()->addLight(new SpotLight(glm::vec3(0, 0, -4), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::radians(55.0f), 1, 0.4, 0.1));
    window->getRenderer()->addLight(new SpotLight(glm::vec3(0, 0, -4), glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0), glm::radians(55.0f), 1, 0.4, 0.1));
    window->getRenderer()->addLight(new SpotLight(glm::vec3(0, 0, -4), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::radians(45.0f), 1, 0.4, 0.1));
    window->getRenderer()->addLight(new SpotLight(glm::vec3(0, 0, -4), glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), glm::radians(45.0f), 1, 0.4, 0.1));

    /* --------------------------------------------- */
    // Initialize scene and render loop
    /* --------------------------------------------- */
    {
        while (!window->shouldClose()) {
            window->onNextFrame();
            window->printPerformanceStats();

            if (argc > 1 && std::string(argv[1]) == "--run_headless") {
                saveScreenshot("screenshot", window->width, window->height);
                break;
            }
        }
    }

    /* --------------------------------------------- */
    // Destroy framework
    /* --------------------------------------------- */

    destroyFramework();

    /* --------------------------------------------- */
    // Destroy context and exit
    /* --------------------------------------------- */
    delete window;
    return EXIT_SUCCESS;
}
