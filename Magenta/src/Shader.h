#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include "Buffer.h"

namespace Magenta
{
    class Shader
    {
    public:
        Shader(std::string vertSource, std::string fragSource);
        ~Shader();

        void Bind();
        void Unbind();

		void SetUniform(ShaderDataType type, std::string uniformName, int32_t value);
		void SetUniform(ShaderDataType type, std::string uniformName, float value);
		void SetUniform(ShaderDataType type, std::string uniformName, glm::vec2 value);
		void SetUniform(ShaderDataType type, std::string uniformName, glm::vec3 value);
		void SetUniform(ShaderDataType type, std::string uniformName, glm::vec4 value);
		void SetUniform(ShaderDataType type, std::string uniformName, const glm::mat4& value);

        uint32_t GetRendererID() const { return m_RendererID; }
        
        static Shader* CreateShader(std::string vertSource, std::string fragSource)
        {
            return new Shader(vertSource, fragSource);
        }


    private:
        uint32_t m_RendererID = 0;
    };
}