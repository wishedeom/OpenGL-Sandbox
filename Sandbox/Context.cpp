#include <type_traits>

#include "Context.h"
#include "utils.h"

/*
*	Helper forwards declarations
*/
void setVersion(const GLint major, const GLint minor);
void setProfile(const OpenGLProfile profile);
void setResizable(const Resizable isResizable);

Context::Context(const GLint minorVersion, const GLint majorVersion, const OpenGLProfile profile, const Resizable isResizable)
{
	glfwInit();
	setVersion(minorVersion, majorVersion);
	setProfile(profile);
	setResizable(isResizable);
}

Context::Context(const std::pair<GLint, GLint> version, const OpenGLProfile profile, const Resizable isResizable)
	: Context { version.first, version.second, profile, isResizable }
{}

Context::~Context()
{
	glfwTerminate();
}

/*
*	Helper function implementations
*/

void setVersion(const GLint major, const GLint minor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void setProfile(const OpenGLProfile profile)
{
	using T = std::underlying_type<OpenGLProfile>::type;
	glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<T>(profile));
}

void setResizable(const Resizable isResizable)
{
	using T = std::underlying_type<Resizable>::type;
	glfwWindowHint(GLFW_RESIZABLE, static_cast<T>(isResizable));
}
