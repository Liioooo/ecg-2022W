/*
* Copyright 2021 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/


#include "Utils.h"
#include "OpenGLDebug.h"
#include "Shader.h"
#include "Teapot.h"
#include "CamaraSystem.h"
#include "InputManager.h"
#include "Box.h"
#include "Cylinder.h"
#include "Sphere.h"
#include <sstream>


/* --------------------------------------------- */
// Prototypes
/* --------------------------------------------- */

/* --------------------------------------------- */
// Global variables
/* --------------------------------------------- */

bool wireFrameMode = false;
bool backFaceCulling = true;

/* --------------------------------------------- */
// Main
/* --------------------------------------------- */

int main(int argc, char **argv) {
    /* --------------------------------------------- */
    // Load settings.ini
    /* --------------------------------------------- */

    // init reader for ini files
    INIReader reader("assets/settings.ini");

    // load values from ini file
    int width = reader.GetInteger("window", "width", 800);
    int height = reader.GetInteger("window", "height", 800);
    int refreshRate = reader.GetInteger("window", "refresh_rate", 60);
    std::string window_title = reader.Get("window", "title", "ECG 2022");

    /* --------------------------------------------- */
    // Init framework
    /* --------------------------------------------- */

    GLFWwindow *window;

    if (!glfwInit()) {
        EXIT_WITH_ERROR("Failed to init GLFW");
    }

#if _DEBUG
    // Create a debug OpenGL context or tell your OpenGL library (GLFW, SDL) to do so.
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

    window = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
    if (!window) {
        EXIT_WITH_ERROR("Failed to create window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = true;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        EXIT_WITH_ERROR(glewGetErrorString(glewErr));
    }

#if _DEBUG
    // Register your callback function.
    glDebugMessageCallback(DebugCallback, NULL);
    // Enable synchronous callback. This ensures that your callback function is called
    // right after an error has occurred.
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(1, 1, 1, 1);

    InputManager* inputManager = new InputManager(window);
    inputManager->addKeyListener(GLFW_KEY_ESCAPE, [](GLFWwindow * window) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    });
    inputManager->addKeyListener(GLFW_KEY_F1, [](GLFWwindow * window) {
        wireFrameMode = !wireFrameMode;
        if (wireFrameMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    });
    inputManager->addKeyListener(GLFW_KEY_F2, [](GLFWwindow * window) {
        backFaceCulling = !backFaceCulling;
        if (backFaceCulling) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }
    });

    Shader *shader = new Shader("assets/shader/shader.vert", "assets/shader/shader.frag");
    shader->use();

    CamaraSystem* camaraSystem = new CamaraSystem(shader, inputManager, reader);

//    Teapot* teapot1 = new Teapot(shader, glm::vec3(0.2f, 0.6f, 0.4f));
//    teapot1->addRotation(180, 0, 1, 0);
//    teapot1->setPosition(-1.5f, 1, 0);
//    teapot1->updateModelMatrix();
//    camaraSystem->addDrawable(teapot1);
//
//    Teapot* teapot2 = new Teapot(shader, glm::vec3(0.7f, 0.1f, 0.2f));
//    teapot2->setPosition(1.5f, -1, 0);
//    teapot2->setScale(1, 2, 1);
//    teapot2->updateModelMatrix();
//    camaraSystem->addDrawable(teapot2);

    Box* box = new Box(shader, glm::vec3(0.7f, 0.1f, 0.2f), 1, 1, 1);
    box->init();
    box->setPosition(3, 3, 3);
    box->updateModelMatrix();
    camaraSystem->addDrawable(box);

    Cylinder* cylinder = new Cylinder(shader, glm::vec3(0.7f, 0.1f, 0.2f), 1, 1, 10);
    cylinder->init();
    cylinder->updateModelMatrix();
    camaraSystem->addDrawable(cylinder);

    Sphere* sphere = new Sphere(shader, glm::vec3(0.4f, 0.3f, 0.7f), 1, 18, 8);
    sphere->init();
    sphere->setScale(1, 1.7f, 1);
    sphere->updateModelMatrix();
    camaraSystem->addDrawable(sphere);

    if (!initFramework()) {
        EXIT_WITH_ERROR("Failed to init framework");
    }

    /* --------------------------------------------- */
    // Initialize scene and render loop
    /* --------------------------------------------- */
    {
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwPollEvents();
            inputManager->updateMousePos();

            camaraSystem->updateCamara();
            camaraSystem->drawObjects();

            glfwSwapBuffers(window);

            if (argc > 1 && std::string(argv[1]) == "--run_headless") {
                saveScreenshot("screenshot", width, height);
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

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
