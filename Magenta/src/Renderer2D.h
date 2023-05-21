#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Buffer.h"
#include "Shader.h"

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
        void DrawCirle2D(glm::vec2 position, float radius, glm::vec4 color);

        static Renderer2D* CreateRenderer2D()
        {
            return new Renderer2D();
        }
    };
}