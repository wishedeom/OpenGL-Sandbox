#include "Shader.h"
#include "ShaderProgram.h"
#include "utils.h"
#include "src/opengl/error.h"
#include "src/opengl/functions.h"

ShaderProgram::ShaderProgram()
	: m_id(OpenGL::CreateProgram())
{}

ShaderProgram::ShaderProgram(ShaderProgram&& rhs)
{
	*this = std::move(rhs);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs)
{
	m_id = rhs.m_id;
	rhs.m_id = 0;

	return *this;
}

ShaderProgram& ShaderProgram::AttachShader(const Shader& shader) &
{
	OpenGL::AttachShader(m_id, shader);
	return *this;
}

ShaderProgram& ShaderProgram::Link() &
{
	using namespace OpenGL;

	LinkProgram(m_id);

	const bool linkStatus = GetParameter(ProgramParameter::LinkStatus);
	if (!linkStatus)
	{
		throw std::runtime_error("Error: Program linking failed.\n" + GetInfoLog() + '\n');
	}

	return *this;
}

ShaderProgram&& ShaderProgram::AttachShader(const Shader& shader) &&
{
	return std::move(this->AttachShader(shader));
}

ShaderProgram&& ShaderProgram::Link() &&
{
	return std::move(this->Link());
}

void ShaderProgram::Use() const
{
	OpenGL::UseProgram(m_id);
}

GLuint ShaderProgram::GetUniformLocation(const std::string_view& name) const
{
	const auto location = OpenGL::GetUniformLocation(m_id, name);
	if (!location.has_value())
	{
		throw std::runtime_error("Uniform " + std::string(name) + " not found.\n");
	}

	return location.value();
}

GLuint ShaderProgram::GetIndex() const
{
	return m_id;
}

GLuint ShaderProgram::GetParameter(const OpenGL::ProgramParameter parameter) const
{
	return GetProgramParameter(m_id, parameter);
}

ShaderProgram::operator GLuint() const
{
	return GetIndex();
}

void ShaderProgram::SetUniformFloat(const std::string_view& name, float value) const
{
	const auto location = GetUniformLocation(name);
	Use();
	OpenGL::SetFloat(location, value);
}

void ShaderProgram::SetUniformVec3(const std::string_view& name, const glm::vec3& vector) const
{
	const auto location = GetUniformLocation(name);
	Use();
	OpenGL::SetVec3(location, vector);
}

void ShaderProgram::SetUniformMat4(const std::string_view& name, const glm::mat4& matrix) const
{
	const auto location = GetUniformLocation(name);
	Use();
	OpenGL::SetMat4(location, matrix);
}

std::string ShaderProgram::GetInfoLog() const
{
	return OpenGL::GetProgramInfoLog(m_id);
}
