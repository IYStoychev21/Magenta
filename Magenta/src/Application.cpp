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
        for(auto& layer : m_MagentaLayers)
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

        SetUpImGui();

        m_Spec.reset(new FrameBufferSpecification{m_Width, m_Height});
        m_FrameBuffer.reset(new FrameBuffer(m_Spec));

        m_InputManager = std::make_shared<InputManager>(m_Window);
    }

    bool Application::WindowShouldClose()
    {
        bool shouldClose = false; 
        shouldClose = glfwWindowShouldClose(m_Window);

        return shouldClose;
    }

    void Application::SetUpImGui()
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    

        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }

    void Application::Run()
    {  

        for(auto& layer : m_MagentaLayers)
        {
            layer->OnAttach();
        }

        int32_t newWidth = 0;
        int32_t newHeight = 0;

        while (!WindowShouldClose())
        {
            glfwPollEvents();
            
            glfwGetFramebufferSize(m_Window, &newWidth, &newHeight);

            if(newWidth != m_Width || newHeight != m_Height)
            {
                m_Width = newWidth;
                m_Height = newHeight;

                m_Spec->width = m_Width;
                m_Spec->height = m_Height;

                m_FrameBuffer->Resize();
            }

            m_FrameBuffer->Bind();

            glClear(GL_COLOR_BUFFER_BIT);

            for(auto& layer : m_MagentaLayers)
            {
                layer->OnUpdate();
            }
            
            m_FrameBuffer->Unbind();
            
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            for(auto& layer : m_MagentaLayers)
            {
                layer->OnUIRender();
            }

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);

            glfwSwapBuffers(m_Window);
        }
    }
}