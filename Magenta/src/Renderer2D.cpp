#include "Renderer2D.h"
#include <iostream>

namespace Magenta
{
    extern uint32_t screenWidth;
    extern uint32_t screenHeight;

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

    void Renderer2D::DrawTriangle(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC, glm::vec4 color)
    {
        glm::mat4 mvp = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

        pointA = mvp * glm::vec4(pointA, 0.0f, 1.0f);
        pointB = mvp * glm::vec4(pointB, 0.0f, 1.0f);
        pointC = mvp * glm::vec4(pointC, 0.0f, 1.0f);

        float vertices[3 * 2] = {
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

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawBox(glm::vec2 position, glm::vec2 size, glm::vec4 color)
    {
        glm::mat4 mvp = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);

        glm::vec2 pointA = mvp * glm::vec4(position.x, position.y, 0.0f, 1.0f);
        glm::vec2 pointB = mvp * glm::vec4(position.x + size.x, position.y, 0.0f, 1.0f);
        glm::vec2 pointC = mvp * glm::vec4(position.x + size.x, position.y + size.y, 0.0f, 1.0f);
        glm::vec2 pointD = mvp * glm::vec4(position.x, position.y + size.y, 0.0f, 1.0f);

        float vertices[4 * 2] = {
            pointA.x, pointA.y,
            pointB.x, pointB.y,
            pointC.x, pointC.y,
            pointD.x, pointD.y
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

    void Renderer2D::DrawLine(glm::vec2 pointA, glm::vec2 pointB, float thickness, glm::vec4 color)
    {
        glm::mat4 mvp = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);

        pointA = mvp * glm::vec4(pointA.x, pointA.y, 0.0f, 1.0f);
        pointB = mvp * glm::vec4(pointB.x, pointB.y, 0.0f, 1.0f);

        float vertices[2 * 2] = {
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

    void Renderer2D::DrawImage(glm::vec2 position, glm::vec2 size, std::shared_ptr<Image> image)
    {
        glm::mat4 mvp = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);

        glm::vec2 pointA = mvp * glm::vec4(position.x, position.y, 0.0f, 1.0f);
        glm::vec2 pointB = mvp * glm::vec4(position.x + size.x, position.y, 0.0f, 1.0f);
        glm::vec2 pointC = mvp * glm::vec4(position.x + size.x, position.y + size.y, 0.0f, 1.0f);
        glm::vec2 pointD = mvp * glm::vec4(position.x, position.y + size.y, 0.0f, 1.0f);

        float vertices[4 * 4] = 
        {
            pointA.x, pointB.y, 0.0f, 0.0f,
            pointB.x, pointB.y, 1.0f, 0.0f,
            pointC.x, pointC.y, 1.0f, 1.0f, 
            pointD.x, pointD.y, 0.0f, 1.0f
        };

        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        BufferLayout layout(
            {
                {"a_Position", ShaderDataType::Float2},
                {"a_TextCoord", ShaderDataType::Float2}
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