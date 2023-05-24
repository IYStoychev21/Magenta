#include "Shader.h"

namespace Magenta
{
    Shader::Shader(std::string vertSource, std::string fragSource)
    {
        // Read our shaders into the appropriate buffers
		std::string vertexSource = vertSource;
		std::string fragmentSource = fragSource;

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}


		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
        }
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind()
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

	void Shader::SetUniform(ShaderDataType type, std::string uniformName, int32_t value) 
	{
		int32_t location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform1i(location, value);
	}

	void Shader::SetUniform(ShaderDataType type, std::string uniformName, float value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform1f(location, value);
	}

	void Shader::SetUniform(ShaderDataType type, std::string uniformName, glm::vec2 value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void Shader::SetUniform(ShaderDataType type, std::string uniformName, glm::vec3 value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::SetUniform(ShaderDataType type, std::string uniformName, glm::vec4 value)
	{
		int32_t location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniform(ShaderDataType type, std::string uniformName, const glm::mat4& value)
	{

		int32_t location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
}