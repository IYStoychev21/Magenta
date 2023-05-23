#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdint>
#include <vector>
#include <memory>

#include "Buffer.h"
#include "Shader.h"
#include "Image.h"

namespace Magenta
{
    class Renderer2D
    {
    public:
        Renderer2D();
        ~Renderer2D();

        void Clear();
        void ClearColor(float r, float g, float b, float a);

        void DrawTriangle2D(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC, glm::vec4 color);
        void DrawBox2D(glm::vec2 position, glm::vec2 size, glm::vec4 color);
        void DrawLine2D(glm::vec2 pointA, glm::vec2 pointB, float thickness, glm::vec4 color);
        void DrawImage2D(glm::vec2 position, glm::vec2 size, std::shared_ptr<Image> image);

        static Renderer2D* CreateRenderer2D()
        {
            return new Renderer2D();
        }
    };
}