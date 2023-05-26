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
        Int, Int2, Int3, Int4,
        Mat4
    };

    uint32_t GetComponentCount(ShaderDataType type);
    GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);
    uint32_t GetShaderTypeSize(ShaderDataType type);

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;

		BufferElement(const char* name, ShaderDataType type) : Name(name), Type(type), Size(GetShaderTypeSize(type)), Offset(0)
		{
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(std::vector<BufferElement> elements);
		inline const std::vector<BufferElement>& GetBufferElements() const { return m_BufferElements; }
		inline const uint32_t& GetStride() const { return m_Stride; }

	private:
		void CalculateStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;

			for (auto& element : m_BufferElements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_BufferElements;
		uint32_t m_Stride = 0;
	};


    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void Bind();
        void SetData(float* verticies, uint32_t size);

        inline void SetBufferLayout(BufferLayout layout) { m_BufferLayout = layout; }
		inline BufferLayout GetBufferLayout() { return m_BufferLayout; };

    private:
        uint32_t m_RendererID;
        BufferLayout m_BufferLayout;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void Bind();
        void SetData(uint32_t* indicies, uint32_t size);

    private:
        uint32_t m_RendererID;
    };
}