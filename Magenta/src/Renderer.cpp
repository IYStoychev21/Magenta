#include "Renderer.h"
#include <iostream>

namespace Magenta
{
    extern uint32_t screenWidth;
    extern uint32_t screenHeight;

    Renderer::Renderer()
    {

    }

    Renderer::~Renderer()
    {

    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::ClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer::DrawTriangle2D(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC, glm::vec4 color)
    {
        float vertices[] = {
            pointA.x, pointA.y,
            pointB.x, pointB.y,
            pointC.x, pointC.y
        };

        uint32_t indices[] = {
            0, 1, 2
        };

        BufferLayout layout(
            {
                {"a_Position", ShaderDataType::Float2}
		    }
        );
        
        Magenta::VertexBuffer* vertexBuffer = Magenta::VertexBuffer::CreateVertexBuffer();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        Magenta::IndexBuffer* indexBuffer = Magenta::IndexBuffer::CreateIndexBuffer();
        indexBuffer->Bind();
        indexBuffer->SetData(indices, sizeof(indices));


        vertexBuffer->SetBufferLayout(layout);
		
		uint16_t index = 0;
		for (auto i : layout.GetBufferElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				GetComponentCount(i.Type), 
				ShaderDataTypeToOpenGLBaseType(i.Type), 
				GL_FALSE, 
				layout.GetStride(),
				0);
			index++;
		}


        std::string vertSource = R"(
            #version 450

            layout(location = 0) in vec2 a_Position;

            out vec2 v_Position;

            void main()
            {
                v_Position = a_Position;

                gl_Position = vec4(a_Position.x, a_Position.y, 1.0, 1.0);
            }
        )";

        std::string fragSource = R"(
            #version 450

            layout(location = 0) uniform vec4 u_Color;

            out vec4 color;

            void main()
            {
                color = vec4(u_Color);
            }
        )";

        std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertSource, fragSource);
        shader->Bind();
        shader->SetUniform(ShaderDataType::Float4, "u_Color", color);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::DrawBox2D(glm::vec2 position, glm::vec2 size, glm::vec4 color)
    {
        float vertices[] = {
            position.x, position.y,
            position.x + size.x, position.y,
            position.x + size.x, position.y + size.y,
            position.x, position.y + size.y
        };

        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        BufferLayout layout(
            {
                {"a_Position", ShaderDataType::Float2}
            }
        );
        
        Magenta::VertexBuffer* vertexBuffer = Magenta::VertexBuffer::CreateVertexBuffer();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        Magenta::IndexBuffer* indexBuffer = Magenta::IndexBuffer::CreateIndexBuffer();
        indexBuffer->Bind();
        indexBuffer->SetData(indices, sizeof(indices));

        vertexBuffer->SetBufferLayout(layout);
		
		uint16_t index = 0;
		for (auto i : layout.GetBufferElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				GetComponentCount(i.Type), 
				ShaderDataTypeToOpenGLBaseType(i.Type), 
				GL_FALSE, 
				layout.GetStride(),
				0);
			index++;
		}


        std::string vertSource = R"(
            #version 450

            layout(location = 0) in vec2 a_Position;

            out vec2 v_Position;

            void main()
            {
                v_Position = a_Position;

                gl_Position = vec4(a_Position, 1.0, 1.0);
            }
        )";

        std::string fragSource = R"(
            #version 450

            layout(location = 0) uniform vec4 u_Color;

            out vec4 color;

            void main()
            {
                color = vec4(u_Color);
            }
        )";

        std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertSource, fragSource);
        shader->Bind();
        shader->SetUniform(ShaderDataType::Float4, "u_Color", color);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}