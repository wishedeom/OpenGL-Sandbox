#include "Shader.h"
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
	: _index { glCreateProgram() }
{
	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(_index, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_index, 512, nullptr, infoLog);
		throw std::runtime_error("Error: shader program linking failed.\n" + std::string(infoLog) + '\n');
	}
}

void ShaderProgram::attach(const Shader& shader) const
{
	glAttachShader(_index, shader);
}

void ShaderProgram::link() const
{
	glLinkProgram(_index);
}

void ShaderProgram::use() const
{
	glUseProgram(_index);
}
