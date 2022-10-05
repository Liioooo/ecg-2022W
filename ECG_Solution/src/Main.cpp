/*
* Copyright 2021 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/


#include "Utils.h"
#include "OpenGLDebug.h"
#include <sstream>


/* --------------------------------------------- */
// Prototypes
/* --------------------------------------------- */

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

/* --------------------------------------------- */
// Global variables
/* --------------------------------------------- */


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

    window = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
    if (!window) {
        EXIT_WITH_ERROR("Failed to create window");
    }

    glfwSetKeyCallback(window, key_callback);
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

    glClearColor(1, 1, 1, 0);

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

            drawTeapot();

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

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
