#include "Application.h"

namespace Magenta
{
    Application::Application()
    {

    }

    Application::~Application()
    {
        glfwTerminate();
    }

    void Application::InitWindow(uint32_t width, uint32_t height, const char* title)
    {
        m_Width = width;
        m_Height = height;

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
    }

    bool Application::WindowShouldClose()
    {
        bool shouldClose = false; 
        shouldClose = glfwWindowShouldClose(m_Window);

        return shouldClose;
    }

    void Application::Run()
    {
        while (!WindowShouldClose())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

            glfwSwapBuffers(m_Window);

            glfwPollEvents();
        }
    }
}