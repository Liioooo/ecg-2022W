//
// Created by preis on 10/10/2022.
//

#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window): window(window) {
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(window))->key_callback(window, key, action);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(window))->mouse_callback(window, button, action);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
        static_cast<InputManager*>(glfwGetWindowUserPointer(window))->scroll_callback(window, xOffset, yOffset);
    });
}

void InputManager::addKeyListener(int key, std::function<void(GLFWwindow*)> listenerFunc) {
    KeyListener* listener = new KeyListener();
    listener->key = key;
    listener->listenerFunc = listenerFunc;
    keyListeners.push_back(listener);
}

void InputManager::addScrollListener(std::function<void(GLFWwindow *, double, double)> listener) {
    scrollListeners.push_back(listener);
}

void InputManager::updateMousePos() {
    prevMousePos = currMousePos;
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    currMousePos = glm::vec2(mouseX, mouseY);
}

glm::vec2 InputManager::getMousePosDelta() const {
    return prevMousePos - currMousePos;
}

void InputManager::key_callback(GLFWwindow* window, int key, int action) {
    if (action == GLFW_PRESS) {
        for (const auto &listener: keyListeners) {
            if (listener->key == key) {
                listener->listenerFunc(window);
            }
        }
    }
}

void InputManager::mouse_callback(GLFWwindow* window, int button, int action) {
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

void InputManager::scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    for (const auto &listener: scrollListeners) {
        listener(window, xOffset, yOffset);
    }
}
