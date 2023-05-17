#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <cstdint>

namespace Magenta
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void InitWindow(uint32_t width, uint32_t height, const char* title);

    private:
        bool WindowShouldClose();

    private:
        GLFWwindow* m_Window = nullptr;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}