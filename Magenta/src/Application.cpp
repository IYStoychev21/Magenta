#include "Application.h"
#include <iostream>

namespace Magenta
{
    uint32_t screenWidth = 0;
    uint32_t screenHeight = 0;

    Application::Application()
    {

    }

    Application::~Application()
    {
        for(auto& layer : m_Layers)
        {
            layer->OnDetach();
        }

        glfwTerminate();
    }

    void Application::InitWindow(uint32_t width, uint32_t height, const char* title)
    {
        m_Width = width;
        m_Height = height;

        screenWidth = width;
        screenHeight = height;

        glfwInit();

        m_Window = glfwCreateWindow(width, height, title, NULL, NULL);


        if (!m_Window)
        {
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);

        if(glewInit() != GLEW_OK)
        {
            glfwTerminate();
        }

        m_Renderer.reset(Renderer::CreateRenderer());

        for(auto& layer : m_Layers)
        {
            layer->OnAttach();
        }
    }

    bool Application::WindowShouldClose()
    {
        bool shouldClose = false; 
        shouldClose = glfwWindowShouldClose(m_Window);

        return shouldClose;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_Layers.push_back(std::unique_ptr<Layer>(layer));
    }

    void Application::Run()
    {
        while (!WindowShouldClose())
        {
            m_Renderer->Clear();

            for(auto& layer : m_Layers)
            {
                layer->OnUpdate();
            }

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }
}