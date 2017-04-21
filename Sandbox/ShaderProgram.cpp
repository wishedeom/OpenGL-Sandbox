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

Uniform ShaderProgram::addUniform(const std::string& name, const UniformType type)
{
	if (_uniforms.find(name) != _uniforms.end())
	{
		throw std::runtime_error("Uniform " + name + " already exists.");
	}
	const auto loc = glGetUniformLocation(_id, name.c_str());
	if (loc == -1)
	{
		throw std::runtime_error("Uniform " + name + " not found or has reserved prefix 'gl_'.\n");
	}
	return _uniforms[name] = { static_cast<GLuint>(loc), type };
}

Uniform ShaderProgram::uniform(const std::string& name) const
{
	const auto& it = _uniforms.find(name);
	if (it == _uniforms.end())
	{
		throw std::runtime_error("No uniform " + name + " exists.\n");
	}
	return it->second;
}

GLuint ShaderProgram::index() const
{
	return _id;
}

ShaderProgram::operator GLuint() const
{
	return index();
}
