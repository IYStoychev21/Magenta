#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <memory>

namespace Magenta {
    struct FrameBufferSpecification
    {
        uint32_t width;
        uint32_t height;
    };

    class FrameBuffer
    {
    public:
        FrameBuffer(std::shared_ptr<FrameBufferSpecification> spec);
        ~FrameBuffer();

        void Bind();
        void Unbind();

        void Resize();

        uint32_t GetColorAttachment() { return m_ColorAttachment; }

    private:
        uint32_t m_RendererID;
        std::shared_ptr<FrameBufferSpecification> m_Specification;
        uint32_t m_ColorAttachment;
        uint32_t m_DepthAttachment;
    };
}