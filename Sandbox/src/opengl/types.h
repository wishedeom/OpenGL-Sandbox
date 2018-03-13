#pragma once

#include "../clamped.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGL
{
	using Clampf = ClampUnit<float>;

	struct Version;
	
	enum class Profile : GLint;
	enum class ProgramParameter : GLenum;
	enum class ShaderParameter : GLenum;
	enum class ShaderType : GLenum;

	constexpr const char* ToString(ShaderType type);
}

enum class OpenGL::ShaderType
	: GLenum
{
	Vertex   = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
};

inline constexpr const char* OpenGL::ToString(const ShaderType type)
{
	switch (type)
	{
		case ShaderType::Vertex:
			return "vertex";
		case ShaderType::Fragment:
			return "fragment";
		default:
			return "(Error: Invalid shader type)";
	}
}

struct OpenGL::Version
{
	GLint minor;
	GLint major;
};

enum class OpenGL::Profile
	: GLint
{
	Core          = GLFW_OPENGL_CORE_PROFILE,
	Compatibility = GLFW_OPENGL_COMPAT_PROFILE,
	Any           = GLFW_OPENGL_ANY_PROFILE,
};

enum class OpenGL::ProgramParameter
	: GLenum
{
	DeleteStatus             = GL_DELETE_STATUS,
	LinkStatus               = GL_LINK_STATUS,
	ValidateStatus           = GL_VALIDATE_STATUS,
	InfoLogLength            = GL_INFO_LOG_LENGTH,
	AttachedShaders          = GL_ATTACHED_SHADERS,
	ActiveAttributes         = GL_ACTIVE_ATTRIBUTES,
	ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
	ActiveUniforms           = GL_ACTIVE_UNIFORMS,
	ActiveUniformMaxLength   = GL_ACTIVE_UNIFORM_MAX_LENGTH,
};

enum class OpenGL::ShaderParameter
	: GLenum
{
	ShaderType         = GL_SHADER_TYPE,
	DeleteStatus       = GL_DELETE_STATUS,
	CompileStatus      = GL_COMPILE_STATUS,
	InfoLogLength      = GL_INFO_LOG_LENGTH,
	ShaderSourceLength = GL_SHADER_SOURCE_LENGTH,
};
