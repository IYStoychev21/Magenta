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
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void Clear();
        void ClearColor(float r, float g, float b, float a);

        void DrawTriangle2D(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC, glm::vec4 color);
        void DrawBox2D(glm::vec2 position, glm::vec2 size, glm::vec4 color);

        static Renderer* CreateRenderer()
        {
            return new Renderer();
        }
    };
}