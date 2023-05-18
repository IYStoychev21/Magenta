#include "Buffer.h"

namespace Magenta
{
    // --------------------------- VERTEX BUFFER ---------------------------------------
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
    // -------------------------------------------------------------------------

    // --------------------------- INDEX BUFFER ---------------------------------------
    IndexBuffer::IndexBuffer()
    {

    }

    IndexBuffer::~IndexBuffer()
    {

    }

    void IndexBuffer::Bind()
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::SetData(uint32_t* indicies, uint32_t size)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_DYNAMIC_DRAW);
    }
    // -------------------------------------------------------------------------
}