//
// Created by preis on 10/10/2022.
//
#ifndef ECG_SOLUTION_INPUTMANAGER_H
#define ECG_SOLUTION_INPUTMANAGER_H

#include <functional>
#include "GLFW/glfw3.h"
#include "glm/detail/type_vec1.hpp"
#include "glm/vec2.hpp"

struct KeyListener {
    int key;
    std::function<void()> listenerFunc;
};

class InputManager {
public:
    InputManager(GLFWwindow* glfwWindow);

    void addKeyListener(int key, const std::function<void()> &listener);
    void addScrollListener(const std::function<void(double xOffset, double yOffset)> &listener);
    void updateMousePos();
    glm::vec2 getMousePosDelta() const;

    const bool& leftMouseButtonPressed = _leftMouseButtonPressed;
    const bool& rightMouseButtonPressed = _rightMouseButtonPressed;

private:
    GLFWwindow* glfwWindow;
    std::vector<KeyListener> keyListeners;
    std::vector<std::function<void(double xOffset, double yOffset)>> scrollListeners;
    bool _leftMouseButtonPressed = false;
    bool _rightMouseButtonPressed = false;
    glm::vec2 currMousePos;
    glm::vec2 prevMousePos;

    void key_callback(int key, int action);
    void mouse_callback(int button, int action);
    void scroll_callback(double xOffset, double yOffset);
};

#endif // ECG_SOLUTION_INPUTMANAGER_H
