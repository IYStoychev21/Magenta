#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>
#include <memory>

#include "Layer.h"
#include "buffer.h"
#include "Shader.h"
#include "Image.h"
#include "FrameBuffer.h"
#include "Input.h"

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

        uint32_t GetWidth() { return m_Width; }
        uint32_t GetHeight() { return m_Height; }

        std::shared_ptr<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }
        std::shared_ptr<InputManager> GetInputManager() { return m_InputManager; }

        void CloseWindow() { glfwSetWindowShouldClose(m_Window, true); }

    private:
        bool WindowShouldClose();
        void SetUpImGui();

    private:
        GLFWwindow* m_Window = nullptr;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;

        std::shared_ptr<FrameBuffer> m_FrameBuffer;
        std::shared_ptr<FrameBufferSpecification> m_Spec;
        std::shared_ptr<InputManager> m_InputManager;

        std::vector<std::shared_ptr<MagentaLayer>> m_MagentaLayers;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}