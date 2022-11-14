//
// Created by preis on 10/10/2022.
//
#pragma once


#include <functional>
#include "GLFW/glfw3.h"
#include "glm/detail/type_vec1.hpp"
#include "glm/vec2.hpp"

struct KeyListener {
    int key;
    std::function<void(GLFWwindow* window)> listenerFunc;
};

class InputManager {
public:
    InputManager(GLFWwindow* window);

    void addKeyListener(int key, std::function<void(GLFWwindow* window)> listener);
    void addScrollListener(std::function<void(GLFWwindow* window,  double xOffset, double yOffset)> listener);
    void updateMousePos();
    glm::vec2 getMousePosDelta() const;

    const bool& leftMouseButtonPressed = _leftMouseButtonPressed;
    const bool& rightMouseButtonPressed = _rightMouseButtonPressed;

private:
    GLFWwindow* window;
    std::vector<KeyListener*> keyListeners;
    std::vector<std::function<void(GLFWwindow* window, double xOffset, double yOffset)>> scrollListeners;
    bool _leftMouseButtonPressed = false;
    bool _rightMouseButtonPressed = false;
    glm::vec2 currMousePos;
    glm::vec2 prevMousePos;

    void key_callback(GLFWwindow *window, int key, int action);
    void mouse_callback(GLFWwindow* window, int button, int action);
    void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
};
