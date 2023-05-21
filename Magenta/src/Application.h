#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>
#include <memory>

#include "Layer.h"
#include "Renderer.h"

namespace Magenta
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void InitWindow(uint32_t width, uint32_t height, const char* title);

        void PushLayer(Layer* layer);

        uint32_t GetWidth() { return m_Width; }
        uint32_t GetHeight() { return m_Height; }

        std::shared_ptr<Renderer> GetRenderer() { return m_Renderer; }

    private:
        bool WindowShouldClose();

    private:
        GLFWwindow* m_Window = nullptr;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;

        std::vector<std::unique_ptr<Layer>> m_Layers;

        std::shared_ptr<Renderer> m_Renderer;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}