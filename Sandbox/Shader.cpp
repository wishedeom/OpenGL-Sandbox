#include <map>

#include "Shader.h"
#include "utils.h"

const std::map<ShaderType, std::string> shaderTypeNames
{
	{ ShaderType::Vertex,   "vertex"   },
	{ ShaderType::Fragment, "fragment" },
};

constexpr GLsizei infoLogLength = 512;

GLuint createShader(const std::string& source, const ShaderType type);

Shader::Shader(const std::string& source, const ShaderType type)
	: _index { createShader(source, type) }
{}

Shader::~Shader()
{
	glDeleteShader(_index);
}

GLuint Shader::index() const
{
	return _index;
}

Shader::operator GLuint() const
{
	return index();
}

GLuint createShader(const std::string& source, const ShaderType type)
{
	// Reference to OpenGL shader object
	const auto idx = glCreateShader(castToUnderlying(type));
	// Shader source code as c-style array
	const auto src = source.c_str();
	// Send source to OpenGL - array is copied, no lifetime issues
	glShaderSource(idx, 1, &src, nullptr);
	// Attempt to compile the array
	glCompileShader(idx);
	// Error checking
	GLint success;
	glGetShaderiv(idx, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(idx, sizeof(infoLog), nullptr, infoLog);
		throw std::runtime_error("Error: " + shaderTypeNames.at(type) + " shader compilation failed.\n" +  std::string(infoLog) +  '\n');
	}
	return idx;
}
