#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <cstdint>

namespace Magenta
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void Bind();
        void SetData(float* verticies, uint32_t size);

        static VertexBuffer* CreateVertexBuffer()
        {
            return new VertexBuffer();
        }

    private:
        uint32_t m_RendererID;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void Bind();
        void SetData(uint32_t* indicies, uint32_t size);

        static IndexBuffer* CreateIndexBuffer()
        {
            return new IndexBuffer();
        }

    private:
        uint32_t m_RendererID;
    };
}