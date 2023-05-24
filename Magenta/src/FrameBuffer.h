#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

namespace Magenta{
    struct FrameBufferSpecification
    {
        uint32_t width;
        uint32_t height;
    };

    class FrameBuffer
    {
    public:
        FrameBuffer(FrameBufferSpecification spec);
        ~FrameBuffer();

        void Bind();
        void Unbind();

        void Resize();

        uint32_t GetColorAttachment() { return m_ColorAttachment; }

    private:
        uint32_t m_RendererID;
        FrameBufferSpecification m_Specification;
        uint32_t m_ColorAttachment;
        uint32_t m_DepthAttachment;
    };
}