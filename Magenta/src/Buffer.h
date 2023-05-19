#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>
#include <vector>

namespace Magenta
{
    enum class ShaderDataType
    {
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4
    };

    struct BufferElement
    {
        std::string name;
        ShaderDataType type;
        uint32_t offset = 0;
    };

    uint32_t GetComponentCount(ShaderDataType type);
    GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);
    uint32_t GetStride(const std::vector<BufferElement>& elements);

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