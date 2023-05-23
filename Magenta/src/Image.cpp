#include "Image.h"
#include <iostream>

namespace Magenta
{
    Image::Image(std::string path)
    {
        m_Path = path;

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

        m_Width = width;
        m_Height = height;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        if(data)
        {
            GLenum format;
            if(channels == 1)
                format = GL_RED;
            else if(channels == 3)
                format = GL_RGB;
            else if(channels == 4)
                format = GL_RGBA;

            glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, blendMode);
            glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, blendMode);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }

    Image::~Image()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void Image::Bind(uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }
}