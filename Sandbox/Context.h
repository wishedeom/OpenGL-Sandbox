/*
*	The Context class manages GLFW initialization and termination.
*/

#pragma once

#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window;

namespace OpenGL
{
	struct Version
	{
		GLint minor;
		GLint major;
	};

	enum class Profile
		: GLint
	{
		Core           =  GLFW_OPENGL_CORE_PROFILE,
		Compatibility  =  GLFW_OPENGL_COMPAT_PROFILE,
		Any            =  GLFW_OPENGL_ANY_PROFILE,
	};
}

enum class Resizable
	: GLboolean
{
	True   = GL_TRUE,
	False  = GL_FALSE,
};

enum class GLEWExperimental
	: GLboolean
{
	True   = GL_TRUE,
	False  = GL_FALSE,
};

class Context final
{
public:
	Context(const OpenGL::Version version);
	~Context();
	void initializeGLEW(const Window& window) const;
};
