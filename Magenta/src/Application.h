#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>
#include <memory>

#include "Layer.h"
#include "Renderer2D.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Magenta
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void InitWindow(uint32_t width, uint32_t height, const char* title);

        void PushMagentaLayer(std::shared_ptr<MagentaLayer> layer) { m_MagentaLayers.push_back(layer);}
        void PushImGuiLayer(std::shared_ptr<ImGuiLayer> layer) { m_ImGuiLayers.push_back(layer);}

        uint32_t GetWidth() { return m_Width; }
        uint32_t GetHeight() { return m_Height; }

        std::shared_ptr<Renderer2D> GetRenderer2D() { return m_Renderer; }

    private:
        bool WindowShouldClose();
        void SetUpImGui();

    private:
        GLFWwindow* m_Window = nullptr;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;

        std::vector<std::shared_ptr<MagentaLayer>> m_MagentaLayers;
        std::vector<std::shared_ptr<ImGuiLayer>> m_ImGuiLayers;

        std::shared_ptr<Renderer2D> m_Renderer;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}