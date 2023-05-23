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

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
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

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        m_Renderer.reset(Renderer2D::CreateRenderer2D());

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
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    

        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init("#version 450");

        while (!WindowShouldClose())
        {

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            
            ImGui::Begin("Hello, world!");
            ImGui::Text("This is some useful text.");
            ImGui::End();

            ImGui::Begin("Another Window");
            ImGui::Text("Hello");
            ImGui::End();

            ImGui::Render();

            m_Renderer->Clear();

            for(auto& layer : m_Layers)
            {
                layer->OnUpdate();
            }

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }
}