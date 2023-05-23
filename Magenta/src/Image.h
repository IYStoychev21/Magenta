#pragma once 

#include <stb_image.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Magenta
{
    class Image
    {
    public:
        Image(std::string path);
        ~Image();

        void Bind(uint32_t slot = 0);
        void SetBlendMode(uint32_t mode) { blendMode = mode; }
    private:
        std::string m_Path;
        uint32_t m_TextureID;

        uint32_t m_Width;
        uint32_t m_Height;

        uint32_t blendMode = GL_LINEAR;
    };
}