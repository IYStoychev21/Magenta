#include "Magenta.h"
#include <glm/glm.hpp>
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
    SandBoxLayer(Magenta::Renderer* renderer = nullptr) : Magenta::MagentaLayer(renderer)
    {

    }

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
        m_Renderer->DrawTriangle2D(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.5f), glm::vec2(0.5f, -0.5f), glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));

        m_Renderer->ClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    }
};

Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();

    Renderer* renderer = Renderer::CreateRenderer();
    app->PushLayer(new SandBoxLayer(renderer));
    app->InitWindow(1280, 720, "SandBox");

    return app;
}