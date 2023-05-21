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
        // std::cout << "OnAttach" << std::endl;
    }

    void OnDetach() override
    {
        // std::cout << "OnDetach" << std::endl;
    }

    void OnUpdate() override
    {
        m_Renderer->DrawBox2D(glm::vec2(-0.375f, -0.375f), glm::vec2(0.75f, 0.75f), glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
        // m_Renderer->DrawTexture2D(glm::vec2(-0.375f, -0.375f), glm::vec2(0.75f, 0.75f), "assets/board.png");

        m_Renderer->ClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    }

private:
    std::shared_ptr<Magenta::Renderer2D> m_Renderer = m_Application->GetRenderer2D();
};

Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();
    app->PushLayer(new SandBoxLayer(app));
    app->InitWindow(1280, 720, "SandBox");

    return app;
}