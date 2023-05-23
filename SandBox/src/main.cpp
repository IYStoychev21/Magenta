#include "Magenta.h"
#include <glm/glm.hpp>
#include <memory>
#include "iostream"

class SandBox : public Magenta::Application
{
public:
    SandBox()
    {

    }

    ~SandBox()
    {

    }
};

class SandBoxLayer : public Magenta::MagentaLayer
{
public:
    using MagentaLayer::MagentaLayer; 

    void OnAttach() override
    {

    }

    void OnDetach() override
    {

    }

    void OnUpdate() override
    {
        m_Renderer2D->DrawBox2D(glm::vec2(m_Application->GetWidth() / 2 - 200.0f, m_Application->GetHeight() / 2 - 100.0f), glm::vec2(200.0f, 200.0f), glm::vec4(0.3f, 0.8f, 0.2f, 1.0f));

        m_Renderer2D->DrawBox2D(glm::vec2(m_Application->GetWidth() / 2, m_Application->GetHeight() / 2 - 100.0f), glm::vec2(200.0f, 200.0f), glm::vec4(0.3f, 0.2f, 0.8f, 1.0f));

        m_Renderer2D->ClearColor(0.22f, 0.22f, 0.22f, 1.0f);
    }

private:
    std::shared_ptr<Magenta::Renderer2D> m_Renderer2D = m_Application->GetRenderer2D();
};

Magenta::Application* Magenta::CreateApplication()
{
    // Create a new application
    SandBox* app = new SandBox();

    // Push all layers
    app->PushLayer(new SandBoxLayer(app));

    // Initialize the window
    app->InitWindow(1280, 720, "SandBox");

    return app;
}