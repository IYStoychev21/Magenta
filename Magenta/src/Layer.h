#pragma once

namespace Magenta
{
    class Application;

    class MagentaLayer
    {
    public:
        MagentaLayer(Application* app) {m_Application = app;} 
        ~MagentaLayer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnUIRender() = 0;

    protected:
        Application* m_Application = nullptr;
    };
}