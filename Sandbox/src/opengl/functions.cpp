#include "functions.h"
#include "error.h"
#include "../../utils.h"
#include "../colour.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <type_traits>

//template <typename F, typename... Args>
//inline auto InjectErrorChecking(const F& f, Args&&... args)
//{
//	using ReturnType = decltype(f(std::forward<Args>(args)...));
//
//	if constexpr (std::is_same_v<ReturnType, void>)
//	{
//		f(std::forward<Args>(args)...);
//		CHECK_ERRORS;
//	}
//	else
//	{
//		const auto ret = f(std::forward<Args>(args)...);
//		CHECK_ERRORS;
//		return ret;
//	}
//}

GLuint OpenGL::CreateProgram()
{
	return InjectErrorChecking(glCreateProgram);
}

GLint OpenGL::GetShaderParameter(const GLuint shader, const ShaderParameter paramName)
{
	GLint out;
	glGetShaderiv(shader, util::to_underlying(paramName), &out);
	CHECK_ERRORS;
	return out;
}

GLint OpenGL::GetProgramParameter(const GLuint programID, const ProgramParameter parameter)
{
	GLint out;
	glGetProgramiv(programID, util::to_underlying(parameter), &out);
	CHECK_ERRORS;
	return out;
}

void OpenGL::LinkProgram(const GLuint programID)
{
	InjectErrorChecking(glLinkProgram, programID);
}

std::string OpenGL::GetProgramInfoLog(const GLuint programID)
{
	const auto length = GetProgramParameter(programID, ProgramParameter::InfoLogLength);
	
	std::string log;
	log.reserve(length);
	
	glGetProgramInfoLog(programID, length, nullptr, log.data());
	CHECK_ERRORS;
	
	return log;
}

std::string OpenGL::GetShaderInfoLog(const GLuint programID)
{
	const auto length = GetShaderParameter(programID, ShaderParameter::InfoLogLength);

	std::string log;
	log.reserve(length);

	glGetShaderInfoLog(programID, length, nullptr, log.data());
	CHECK_ERRORS;

	return log;
}

void OpenGL::AttachShader(const GLuint programID, const GLuint shaderID)
{
	InjectErrorChecking(glAttachShader, programID, shaderID);
}

void OpenGL::UseProgram(const GLuint programID)
{
	InjectErrorChecking(glUseProgram, programID);
}

std::optional<GLuint> OpenGL::GetUniformLocation(const GLuint programID, const std::string_view& uniformName)
{
	const auto location = glGetUniformLocation(programID, uniformName.data());
	CHECK_ERRORS;

	if (location == -1)
	{
		return std::nullopt;
	}

	return location;
}

void OpenGL::ClearColour(const Colour& colour)
{
	InjectErrorChecking(glClearColor, colour.r, colour.g, colour.b, colour.a);
}

void OpenGL::Enable(const Capability cap)
{
	InjectErrorChecking(glEnable, util::to_underlying(cap));
}

void OpenGL::Disable(const Capability cap)
{
	InjectErrorChecking(glDisable, util::to_underlying(cap));
}

void OpenGL::Clear(const Buffer buffer)
{
	InjectErrorChecking(glClear, util::to_underlying(buffer));
}
