#include "Magenta.h"

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

Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();
    
    app->InitWindow(1280, 720, "SandBox");

    return app;
}