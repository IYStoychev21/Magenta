#pragma once
#include "Renderer2D.h"

namespace Magenta
{
    class Application;
    
    class Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
    };

    class MagentaLayer : public Layer
    {
    public:
        MagentaLayer(Application* app) {m_Application = app;} 
        ~MagentaLayer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;

    protected:
        Application* m_Application = nullptr;
    };
}