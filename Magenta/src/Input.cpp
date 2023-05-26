#include "Input.h"

namespace Magenta{
    InputManager::InputManager(GLFWwindow* window)
    {
        m_Window = window;
    }

    InputManager::~InputManager()
    {
        
    }

    bool InputManager::IsKeyPressed(KeyCode key)
    {
        return glfwGetKey(m_Window, (int)key) == GLFW_PRESS;
    }

    bool InputManager::IsKeyReleased(KeyCode key)
    {
        return glfwGetKey(m_Window, (int)key) == GLFW_RELEASE;
    }

    bool InputManager::IsKeyDown(KeyCode key)
    {
        return glfwGetKey(m_Window, (int)key) == GLFW_REPEAT;
    }
}