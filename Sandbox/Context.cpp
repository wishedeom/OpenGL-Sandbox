#include <stdexcept>

#include "Context.h"
#include "utils.h"

using namespace OpenGL;

/*
*	Helper forwards declarations
*/
void setVersion(const GLint major, const GLint minor);
void setProfile(const Profile profile);
void setResizable(const Resizable isResizable);


/*
*	Member implementations
*/
Context::Context(const Version version, const Profile profile, const Resizable isResizable)
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
	glewExperimental = toIntegral(experimental);
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

void setProfile(const Profile profile)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, toIntegral(profile));
}

void setResizable(const Resizable isResizable)
{
	glfwWindowHint(GLFW_RESIZABLE, toIntegral(isResizable));
}
