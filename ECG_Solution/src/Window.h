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

class Window {
public:
    Window(INIReader* reader);
    ~Window();

    void setVsync(const bool &enabled);
    void setWireframeMode(const bool &enabled);
    void setBackfaceCulling(const bool &enabled);
    InputManager* getInputManager() const;
    CamaraSystem* getCamaraSystem() const;
    void setShouldClose();
    bool shouldClose();
    void onNextFrame();
    void printPerformanceStats();

    const bool& isWireframe = _isWireframe;
    const bool& isBackfaceCulling = _isBackfaceCulling;
    const int& width = _width;
    const int& height = _height;

private:
    GLFWwindow* window;
    GLFWmonitor* monitor = nullptr;
    InputManager* inputManager;
    CamaraSystem* camaraSystem;
    bool _isWireframe;
    bool _isBackfaceCulling;
    int _width;
    int _height;
    double perfLastFrameTime = 0;
    double perfLastPrintTime = 0;
};

#endif // ECG_SOLUTION_WINDOW_H