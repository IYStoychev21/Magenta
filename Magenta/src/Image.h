#pragma once 

#include <stb_image.h>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace Magenta
{
    class Image
    {
    public:
        Image(std::string path, uint32_t format);
        Image(uint32_t* imageData, glm::vec2 dim, uint32_t format);
        ~Image();

        void Bind(uint32_t slot = 0);
        void SetBlendMode(uint32_t mode) { blendMode = mode; }

        uint32_t GetWidth() { return m_Width; }
        uint32_t GetHeight() { return m_Height; }

        uint32_t GetTextureID() { return m_TextureID; }
    private:
        std::string m_Path;
        uint32_t m_TextureID;

        uint32_t m_Width;
        uint32_t m_Height;

        uint32_t blendMode = GL_LINEAR;
    };
}