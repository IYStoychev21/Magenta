#pragma once
#include "Renderer.h"

namespace Magenta
{
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
        MagentaLayer(Renderer* renderer = nullptr) { m_Renderer = renderer; } 
        ~MagentaLayer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;

    protected:
        Renderer* m_Renderer = nullptr;
    };
}