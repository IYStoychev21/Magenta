#include "Buffer.h"

namespace Magenta
{
    VertexBuffer::VertexBuffer()
    {

    }

    VertexBuffer::~VertexBuffer()
    {

    }

    void VertexBuffer::Bind()
    {        
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::SetData(float* verticies, uint32_t size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_DYNAMIC_DRAW);
    }
}