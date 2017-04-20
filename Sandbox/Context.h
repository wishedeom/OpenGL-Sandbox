/*
*	The Context class manages GLFW initialization and termination.
*/

#pragma once

#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class OpenGLProfile
	: GLint
{
	Core   = GLFW_OPENGL_CORE_PROFILE,
	Compat = GLFW_OPENGL_COMPAT_PROFILE,
	Any    = GLFW_OPENGL_ANY_PROFILE,
};

enum class Resizable
	: GLboolean
{
	True   = GL_TRUE,
	False  = GL_FALSE,
};

class Context final
{
public:
	Context(const GLint minorVersion, const GLint majorVersion, const OpenGLProfile profile, const Resizable isResizable);
	Context(const std::pair<GLint, GLint> version, const OpenGLProfile profile, const Resizable isResizable);
	~Context();
};
