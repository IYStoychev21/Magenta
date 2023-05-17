#include "Application.h"

extern Magenta::Application* Magenta::CreateApplication();

int main()
{
    auto app = Magenta::CreateApplication();
    app->Run();
    delete app;
}