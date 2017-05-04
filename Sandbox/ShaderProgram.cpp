#include "Shader.h"
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
	: _id { glCreateProgram() }
{
	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_id, 512, nullptr, infoLog);
		throw std::runtime_error("Error: shader program linking failed.\n" + std::string(infoLog) + '\n');
	}
}

ShaderProgram& ShaderProgram::attach(const Shader& shader)
{
	glAttachShader(_id, shader);
	return *this;
}

ShaderProgram& ShaderProgram::link()
{
	glLinkProgram(_id);
	return *this;
}

ShaderProgram& ShaderProgram::use()
{
	glUseProgram(_id);
	return *this;
}

ShaderProgram& ShaderProgram::operator()()
{
	return use();
}

GLuint ShaderProgram::getUniform(const std::string& name) const
{
	const auto loc = glGetUniformLocation(_id, name.c_str());
	if (loc == -1)
	{
		throw std::runtime_error("Uniform " + name + " not found.\n");
	}
	return loc;
}

GLuint ShaderProgram::index() const
{
	return _id;
}

ShaderProgram::operator GLuint() const
{
	return index();
}
