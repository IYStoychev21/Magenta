#include "Magenta.h"
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

class SandBoxLayer : public Magenta::Layer
{
public:
    void OnAttach() override
    {
        std::cout << "OnAttach" << std::endl;
    }

    void OnDetach() override
    {
        std::cout << "OnDetach" << std::endl;
    }

    void OnUpdate() override
    {
        std::cout << "OnUpdate" << std::endl;
    }
};

Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();

    app->PushLayer(new SandBoxLayer());
    app->InitWindow(1280, 720, "SandBox");

    return app;
}