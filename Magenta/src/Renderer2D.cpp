#include "Renderer2D.h"
#include <iostream>

namespace Magenta
{
    extern uint32_t screenWidth;
    extern uint32_t screenHeight;

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
    }

    Renderer2D::Renderer2D()
    {

    }

    Renderer2D::~Renderer2D()
    {

    }

    void Renderer2D::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer2D::ClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer2D::DrawTriangle2D(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC, glm::vec4 color)
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
        
        std::unique_ptr<Magenta::VertexBuffer> vertexBuffer = std::make_unique<Magenta::VertexBuffer>();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        std::unique_ptr<Magenta::IndexBuffer> indexBuffer = std::make_unique<Magenta::IndexBuffer>();
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
				(const void*)i.Offset);
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

    void Renderer2D::DrawBox2D(glm::vec2 position, glm::vec2 size, glm::vec4 color)
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
        
        std::unique_ptr<Magenta::VertexBuffer> vertexBuffer = std::make_unique<Magenta::VertexBuffer>();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        std::unique_ptr<Magenta::IndexBuffer> indexBuffer = std::make_unique<Magenta::IndexBuffer>();
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
				(const void*)i.Offset);
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

    void Renderer2D::DrawCirle2D(glm::vec2 position, float radius, glm::vec4 color)
    {
        float vertices[360 * 2];
        uint32_t indices[360 * 3];

        for (int i = 0; i < 360; i++)
        {
            vertices[i * 2] = position.x + radius * cos(i);
            vertices[i * 2 + 1] = position.y + radius * sin(i);
        }

        for (int i = 0; i < 360; i++)
        {
            indices[i * 3] = 0;
            indices[i * 3 + 1] = i;
            indices[i * 3 + 2] = i + 1;
        }

        BufferLayout layout(
            {
                {"a_Position", ShaderDataType::Float2}
            }
        );
        
        std::unique_ptr<Magenta::VertexBuffer> vertexBuffer = std::make_unique<Magenta::VertexBuffer>();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        std::unique_ptr<Magenta::IndexBuffer> indexBuffer = std::make_unique<Magenta::IndexBuffer>();
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
                (const void*)i.Offset);
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

        glDrawElements(GL_TRIANGLES, 360 * 3, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawLine2D(glm::vec2 pointA, glm::vec2 pointB, float thickness, glm::vec4 color)
    {
        float vertices[] = {
            pointA.x, pointA.y,
            pointB.x, pointB.y
        };

        uint32_t indices[] = {
            0, 1
        };

        BufferLayout layout(
            {
                {"a_Position", ShaderDataType::Float2}
            }
        );
        
        std::unique_ptr<Magenta::VertexBuffer> vertexBuffer = std::make_unique<Magenta::VertexBuffer>();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        std::unique_ptr<Magenta::IndexBuffer> indexBuffer = std::make_unique<Magenta::IndexBuffer>();
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
                (const void*)i.Offset);
            index++;
        }

        std::string vertSource = R"(
            #version 450

            layout(location = 0) in vec2 a_Position;

            void main()
            {
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

        glLineWidth(thickness);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawImage2D(glm::vec2 position, glm::vec2 size, std::shared_ptr<Image> image)
    {
        float vertices[4 * 4] = 
        {
            position.x, position.y, 0.0f, 0.0f,
            position.x + size.x, position.y, 1.0f, 0.0f,
            position.x + size.x, position.y + size.y, 1.0f, 1.0f, 
            position.x, position.y + size.y, 0.0f, 1.0f
        };

        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        BufferLayout layout(
            std::vector<BufferElement>{
                BufferElement("a_Position", ShaderDataType::Float2),
                BufferElement("a_TextCoord", ShaderDataType::Float2)
            }
        );
        
        std::unique_ptr<Magenta::VertexBuffer> vertexBuffer = std::make_unique<Magenta::VertexBuffer>();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        std::unique_ptr<Magenta::IndexBuffer> indexBuffer = std::make_unique<Magenta::IndexBuffer>();
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
                (const void*)i.Offset);
            index++;
        }

        std::string vertSource = R"(
            #version 450

            layout(location = 0) in vec2 a_Position;
            layout(location = 1) in vec2 a_TextCoord;

            out vec2 v_TextCoord;

            void main()
            {
                v_TextCoord = a_TextCoord;
                gl_Position = vec4(a_Position, 1.0, 1.0);
            }
        )";

        std::string fragSource = R"(
            #version 450

            layout(location = 0) uniform sampler2D u_Texture;

            out vec4 color;

            in vec2 v_TextCoord;

            void main()
            {
                color = texture(u_Texture, v_TextCoord);
            }
        )";

        std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertSource, fragSource);
        shader->Bind();
        shader->SetUniform(ShaderDataType::Int, "u_Texture", 0);

        image->Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}