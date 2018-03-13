#include <stdexcept>

#include "Context.h"
#include "utils.h"

#include <GL/glew.h>

#include "src/opengl/error.h"
#include "src/opengl/util.h"

DEFINE_STRONG_OGL_BOOL(Resizable);
DEFINE_STRONG_OGL_BOOL(GLEWExperimental);

namespace OpenGL
{
	static void SetVersion(GLint major, GLint minor);
	static void SetProfile(Profile profile);
	static void SetIsResizable(Resizable isResizable);
}

using namespace OpenGL;

const OpenGL::Version Context::version = { 3, 3 };

Context& Context::Get()
{
	static Context context;
	return context;
}

Context::Context()
{
	glfwSetErrorCallback([](const int errCode, const char* const errMsg)
	{
		throw std::runtime_error("GLFW Error (" + std::to_string(errCode) + "): " + errMsg + '\n');
	});
	
	const bool success = glfwInit();
	if (!success)
	{
		throw std::runtime_error("GLFW Initialization failed.\n");
	}

	SetVersion(version.major, version.minor);
	SetProfile(Profile::Core);
	SetIsResizable(Resizable::False);
}

Context::~Context()
{
	glfwTerminate();
}

Window Context::MakeWindow(const GLint height, const GLint width, const std::string_view& title, const bool fullScreen /*= false*/) const
{
	Window window(height, width, title, fullScreen);
	if (!m_isGLEWInitialized)
	{
		InitializeGLEW();
	}
	return window;
}

void Context::InitializeGLEW() const
{
	glewExperimental = util::to_underlying(GLEWExperimental::True);

	const auto initSuccess = glewInit();
	if (initSuccess != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW.\n");
	}

	m_isGLEWInitialized = true;
}

void OpenGL::SetVersion(const GLint major, const GLint minor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void OpenGL::SetProfile(const Profile profile)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, util::to_underlying(profile));
}

void OpenGL::SetIsResizable(const Resizable isResizable)
{
	glfwWindowHint(GLFW_RESIZABLE, util::to_underlying(isResizable));
}
