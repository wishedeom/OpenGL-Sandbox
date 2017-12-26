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
Context::Context(const Version version)
{
	glfwInit();
	setVersion(version.major, version.minor);
	setProfile(Profile::Core);
	setResizable(Resizable::False);
}

Context::~Context()
{
	glfwTerminate();
}

void Context::initializeGLEW(const Window&) const
{
	glewExperimental = util::to_underlying(GLEWExperimental::True);
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, util::to_underlying(profile));
}

void setResizable(const Resizable isResizable)
{
	glfwWindowHint(GLFW_RESIZABLE, util::to_underlying(isResizable));
}
