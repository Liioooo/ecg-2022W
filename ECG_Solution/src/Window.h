//
// Created by preis on 17/11/2022.
//
#ifndef ECG_SOLUTION_WINDOW_H
#define ECG_SOLUTION_WINDOW_H

#include "INIReader.h"
#include "OpenGLDebug.h"
#include "InputManager.h"
#include "CamaraSystem.h"
#include "Utils.h"
#include "Renderer.h"

class Window {
public:
    Window(INIReader* reader);
    ~Window();

    void setVsync(const bool &enabled);
    void setWireframeMode(const bool &enabled);
    void setBackfaceCulling(const bool &enabled);
    InputManager* getInputManager() const;
    Renderer* getRenderer() const;
    void setShouldClose() const;
    bool shouldClose() const;
    void onNextFrame();
    void printPerformanceStats();

    template<class System>
    void setCamaraSystem() {
        renderer->setCamaraSystem(new System(inputManager, iniReader));
    }

    const bool& isWireframe = _isWireframe;
    const bool& isBackfaceCulling = _isBackfaceCulling;
    const int& width = _width;
    const int& height = _height;

private:
    INIReader* iniReader;
    GLFWwindow* window;
    GLFWmonitor* monitor = nullptr;
    InputManager* inputManager;
    Renderer* renderer;
    bool _isWireframe;
    bool _isBackfaceCulling;
    int _width;
    int _height;
    double perfLastFrameTime = 0;
    double perfLastPrintTime = 0;
};

#endif // ECG_SOLUTION_WINDOW_H