#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>
#include <vector>

namespace Magenta
{
    class Shader
    {
    public:
        Shader(std::string vertSource, std::string fragSource);
        ~Shader();

        void Bind();
        void Unbind();

        uint32_t GetRendererID() const { return m_RendererID; }

    private:
        uint32_t m_RendererID = 0;
    };
}