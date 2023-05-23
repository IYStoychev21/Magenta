#pragma once
#include "Renderer2D.h"

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

    protected:
        Application* m_Application = nullptr;
    };

    class ImGuiLayer
    {
    public:
        ImGuiLayer() = default;
        ~ImGuiLayer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void Render() = 0;

        std::string GetName() { return m_Name; }
        void SetName(std::string name) { m_Name = name; }

    protected:
        std::string m_Name= "Layer";
    };
}