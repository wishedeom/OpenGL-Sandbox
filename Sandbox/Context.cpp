#include <stdexcept>

#include "Context.h"
#include "utils.h"

/*
*	Helper forwards declarations
*/
void setVersion(const GLint major, const GLint minor);
void setProfile(const OpenGLProfile profile);
void setResizable(const Resizable isResizable);


/*
*	Member implementations
*/
Context::Context(const OpenGLVersion version, const OpenGLProfile profile, const Resizable isResizable)
{
	glfwInit();
	setVersion(version.major, version.minor);
	setProfile(profile);
	setResizable(isResizable);
}

Context::~Context()
{
	glfwTerminate();
}

void Context::initializeGLEW(const Window&, const GLEWExperimental experimental) const
{
	glewExperimental = glCast(experimental);
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW.\n");
	}
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, glCast(profile));
}

void setResizable(const Resizable isResizable)
{
	glfwWindowHint(GLFW_RESIZABLE, glCast(isResizable));
}
