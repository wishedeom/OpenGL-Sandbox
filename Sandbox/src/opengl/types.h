#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGL
{
	struct Version;
	
	enum class Profile : GLint;
	enum class ProgramParameter : GLint;
	enum class ShaderParameter : GLint;
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
	: GLint
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
