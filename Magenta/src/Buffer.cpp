#include "Buffer.h"

namespace Magenta
{
    uint32_t GetComponentCount(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float: return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Int: return 1;
        case ShaderDataType::Int2: return 2;
        case ShaderDataType::Int3: return 3;
        case ShaderDataType::Int4: return 4;
        default:
            break;
        }

        return 0;
    }
    
    GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch(type)
        {
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;
        default:
            break;
        }

        return 0;
    }
    
    uint32_t GetShaderTypeSize(ShaderDataType type)
    {
         switch (type)
         {
         case ShaderDataType::Float: return 4;
         case ShaderDataType::Float2: return 4 * 2;
         case ShaderDataType::Float3: return 4 * 3;
         case ShaderDataType::Float4: return 4 * 4;
         case ShaderDataType::Int: return 4;
         case ShaderDataType::Int2: return 4 * 2;
         case ShaderDataType::Int3: return 4 * 3;
         case ShaderDataType::Int4: return 4 * 4;
         default:
              break;
         }

         return 0;
    } 

    BufferLayout::BufferLayout(std::vector<BufferElement> elements)
    {
        m_BufferElements = elements;
        CalculateStride();
    }

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