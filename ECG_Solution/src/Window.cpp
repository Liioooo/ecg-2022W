//
// Created by preis on 17/11/2022.
//

#include "Window.h"

Window::Window(INIReader* reader) {
    _width = reader->GetInteger("window", "width", 800);
    _height = reader->GetInteger("window", "height", 800);
    int refreshRate = reader->GetInteger("window", "refresh_rate", 60);
    bool fullScreen = reader->GetBoolean("window", "fullscreen", false);
    std::string windowTitle = reader->Get("window", "title", "ECG 2022");

    glfwSetErrorCallback(GLFWErrorCallback);

    if (!glfwInit()) {
        EXIT_WITH_ERROR("Failed to init GLFW")
    }

    #if _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    #endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

    if (fullScreen) {
        monitor = glfwGetPrimaryMonitor();
    }

    window = glfwCreateWindow(_width, _height, windowTitle.c_str(), monitor, nullptr);

    if (!window) {
        EXIT_WITH_ERROR("Failed to create window")
    }

    glfwMakeContextCurrent(window);
    setVsync(true);

    glewExperimental = true;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        EXIT_WITH_ERROR(glewGetErrorString(glewErr))
    }

    #if _DEBUG
        glDebugMessageCallback(DebugCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    #endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(1, 1, 1, 1);

    inputManager = new InputManager(window);
    camaraSystem = new CamaraSystem(inputManager, reader);
}

Window::~Window() {
    delete inputManager;
    delete camaraSystem;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::setVsync(const bool &enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::setWireframeMode(const bool &enabled) {
    _isWireframe = !_isWireframe;
    if (_isWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Window::setBackfaceCulling(const bool &enabled) {
    _isBackfaceCulling = !_isBackfaceCulling;
    if (_isBackfaceCulling) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

InputManager* Window::getInputManager() const {
    return inputManager;
}

CamaraSystem *Window::getCamaraSystem() const {
    return camaraSystem;
}

void Window::setShouldClose() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::onNextFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();

    inputManager->updateMousePos();

    camaraSystem->updateCamara();
    camaraSystem->drawObjects();

    glfwSwapBuffers(window);
}
