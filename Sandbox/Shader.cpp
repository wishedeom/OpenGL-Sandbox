#include "Shader.h"
#include "utils.h"

GLuint createShader(const std::string& source, const ShaderType type);

Shader::Shader(const std::string& source, const ShaderType type)
	: _id { createShader(source, type) }
{}

Shader::~Shader()
{
	glDeleteShader(_id);
}

GLuint Shader::index() const
{
	return _id;
}

Shader::operator GLuint() const
{
	return index();
}

GLuint createShader(const std::string& source, const ShaderType type)
{
	// Reference to OpenGL shader object
	const auto id = glCreateShader(util::to_underlying(type));

	// Shader source code as c-style array
	const auto src = source.c_str();
	
	// Send source to OpenGL - array is copied, no lifetime issues
	glShaderSource(id, 1, &src, nullptr);
	
	// Attempt to compile the array
	glCompileShader(id);
	
	// Error checking
	util::checkShaderCompilationErrors(id, type);
	
	return id;
}
