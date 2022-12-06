/*
* Copyright 2021 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/

#include "Utils.h"
#include "Window.h"
#include "Teapot.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Torus.h"


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

    auto *shader = new Shader("assets/shader/shader.vert", "assets/shader/shader.frag");

    auto* box = new Box(shader, glm::vec3(0.7f, 0.1f, 0.2f), 1.3f, 2.0f, 1.3f);
    box->init();
    box->setRotation(0, glm::radians(45.0), 0);
    window->getCamaraSystem()->addDrawable(box);

    auto* cylinder = new Cylinder(shader, glm::vec3(0.2f, 0.8f, 0.4f), 0.6f, 2, 18);
    cylinder->init();
    cylinder->setPosition(2.2f, 0, 0);
    window->getCamaraSystem()->addDrawable(cylinder);

    auto* sphere = new Sphere(shader, glm::vec3(0.4f, 0.3f, 0.7f), 0.6, 18, 8);
    sphere->init();
    sphere->setScale(1, 1.7f, 1);
    sphere->setPosition(-2.2f, 0, 0);
    window->getCamaraSystem()->addDrawable(sphere);

    auto* torus = new Torus(shader, glm::vec3(1.0f, 0.3f, 0.0f), 4.5f, 0.5f, 32, 18);
    torus->init();
    torus->setScale(1, 0.6f, 1);
    window->getCamaraSystem()->addDrawable(torus);

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
