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
        std::shared_ptr<Magenta::Image> image = std::make_unique<Magenta::Image>("SandBox/assets/vscode.png");
        m_Renderer2D->DrawImage2D(glm::vec2(m_Application->GetWidth() / 2 - 250.0f, m_Application->GetHeight() / 2 - 250.0f), glm::vec2(500.0f, 500.0f), image);

        m_Renderer2D->ClearColor(0.8f, 0.8f, 0.8f, 1.0f);
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