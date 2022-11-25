//
// Created by preis on 10/10/2022.
//

#include "InputManager.h"

InputManager::InputManager(GLFWwindow* glfwWindow) : glfwWindow(glfwWindow) {
    glfwSetWindowUserPointer(glfwWindow, this);

    glfwSetKeyCallback(glfwWindow, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(glfwWindow))->key_callback(key, action);
    });
    glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* glfwWindow, int button, int action, int mods) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(glfwWindow))->mouse_callback(button, action);
    });
    glfwSetScrollCallback(glfwWindow, [](GLFWwindow* glfwWindow, double xOffset, double yOffset) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(glfwWindow))->scroll_callback(xOffset, yOffset);
    });
}

void InputManager::addKeyListener(int key, const std::function<void()> &listenerFunc) {
    auto* listener = new KeyListener();
    listener->key = key;
    listener->listenerFunc = listenerFunc;
    keyListeners.push_back(listener);
}

void InputManager::addScrollListener(const std::function<void(double, double)> &listener) {
    scrollListeners.push_back(listener);
}

void InputManager::updateMousePos() {
    prevMousePos = currMousePos;
    double mouseX, mouseY;
    glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
    currMousePos = glm::vec2(mouseX, mouseY);
}

glm::vec2 InputManager::getMousePosDelta() const {
    return prevMousePos - currMousePos;
}

void InputManager::key_callback(int key, int action) {
    if (action == GLFW_PRESS) {
        for (const auto &listener: keyListeners) {
            if (listener->key == key) {
                listener->listenerFunc();
            }
        }
    }
}

void InputManager::mouse_callback(int button, int action) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS) {
                _leftMouseButtonPressed = true;
            } else if (action == GLFW_RELEASE) {
                _leftMouseButtonPressed = false;
            }
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_PRESS) {
                _rightMouseButtonPressed = true;
            } else if (action == GLFW_RELEASE) {
                _rightMouseButtonPressed = false;
            }
            break;
    }
}

void InputManager::scroll_callback(double xOffset, double yOffset) {
    for (const auto &listener: scrollListeners) {
        listener(xOffset, yOffset);
    }
}
