#include "Window.h"
#include "src/opengl/error.h"

#include <tuple>

static std::pair<int, int> GetFrameBufferSize(GLFWwindow& window);

Window::Window(const GLint height, const GLint width, const std::string& title, bool fullScreen /*= true*/)
{
	auto monitor = fullScreen ? glfwGetPrimaryMonitor() : nullptr;
	m_window = glfwCreateWindow(height, width, title.c_str(), monitor, nullptr);
	if (!m_window)
	{
		throw std::runtime_error("Failed to create OpenGL window.\n");
	}

	InitializeDimensions();
	makeContextCurrent();

	CHECK_ERRORS;
}

void Window::makeContextCurrent() const
{
	glfwMakeContextCurrent(m_window);
}

void Window::close() const
{
	glfwSetWindowShouldClose(m_window, GL_TRUE);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_window);
}

Window::operator GLFWwindow*() const
{
	return get();
}

GLFWwindow* Window::get() const
{
	return m_window;
}

GLfloat Window::height() const
{
	return _height;
}

GLfloat Window::width() const
{
	return _width;
}

void Window::InitializeDimensions()
{
	const auto [width, height] = GetFrameBufferSize(*m_window);
	_width = static_cast<float>(width);
	_height = static_cast<float>(height);
}

std::pair<int, int> GetFrameBufferSize(GLFWwindow& window)
{
	int width, height;
	glfwGetFramebufferSize(&window, &width, &height);
	return { width, height };
}
