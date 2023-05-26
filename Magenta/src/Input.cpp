#include "Input.h"

namespace Magenta{
    InputManager::InputManager(GLFWwindow* window)
    {
        m_Window = window;
    }

    InputManager::~InputManager()
    {
        
    }
    
    bool InputManager::IsKeyDown(KeyCode key)
    {
        int32_t state = glfwGetKey(m_Window, (int32_t)key);
        return state == (int32_t)KeyAction::Press || state == (int32_t)KeyAction::Repeat;
    }

    bool InputManager::IsMouseButtonDown(MouseButton button)
    {
        int32_t state = glfwGetMouseButton(m_Window, (int32_t)button);
        return state == (int32_t)KeyAction::Press;
    }

    glm::vec2 InputManager::GetMousePosition()
    {
        double x, y;
        glfwGetCursorPos(m_Window, &x, &y);
        return glm::vec2(x, y);
    }

    void InputManager::SetMousePosition(glm::vec2 position)
    {
        glfwSetCursorPos(m_Window, position.x, position.y);
    }
}