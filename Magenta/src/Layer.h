#pragma once

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
        MagentaLayer() = default;
        ~MagentaLayer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
    };
}