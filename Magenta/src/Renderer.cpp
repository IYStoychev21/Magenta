#include "Renderer.h"
#include "iostream"

namespace Magenta
{
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
            pointA.x, pointA.y, /*color.r, color.g, color.b, color.a,*/
            pointB.x, pointB.y, /*color.r, color.g, color.b, color.a,*/
            pointC.x, pointC.y, /*color.r, color.g, color.b, color.a*/
        };

        uint32_t indices[] = {
            0, 1, 2
        };

        Magenta::VertexBuffer* vertexBuffer = Magenta::VertexBuffer::CreateVertexBuffer();
        vertexBuffer->Bind();
        vertexBuffer->SetData(vertices, sizeof(vertices));

        Magenta::IndexBuffer* indexBuffer = Magenta::IndexBuffer::CreateIndexBuffer();
        indexBuffer->Bind();
        indexBuffer->SetData(indices, sizeof(indices));

        glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }
}