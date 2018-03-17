#pragma once

#include "types.h"
#include "error.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#pragma warning (pop)

#include <string>
#include <string_view>
#include <optional>
#include <type_traits>

struct Colour;

namespace OpenGL
{
	GLuint CreateProgram();
	GLint GetShaderParameter(GLuint shaderID, ShaderParameter paramName);
	GLint GetProgramParameter(GLuint programID, ProgramParameter parameter);
	void LinkProgram(GLuint programID);

	std::string GetProgramInfoLog(GLuint programID);
	std::string GetShaderInfoLog(GLuint programID);

	void AttachShader(GLuint programID, GLuint shaderID);
	void UseProgram(GLuint programID);
	std::optional<GLuint> GetUniformLocation(GLuint programID, const std::string_view& uniformName);

	GLuint CreateShader();
	void ClearColour(const Colour& colour);

	void Enable(Capability cap);
	void Disable(Capability cap);
	void Clear(Buffer buffer);

	template <typename F, typename... Args>
	inline auto InjectErrorChecking(const F& f, Args&&... args);
}

template <typename F, typename... Args>
inline auto OpenGL::InjectErrorChecking(const F& f, Args&&... args)
{
	using ReturnType = decltype(f(std::forward<Args>(args)...));

	if constexpr (std::is_same_v<ReturnType, void>)
	{
		f(std::forward<Args>(args)...);
		CHECK_ERRORS;
	}
	else
	{
		const auto ret = f(std::forward<Args>(args)...);
		CHECK_ERRORS;
		return ret;
	}
}
