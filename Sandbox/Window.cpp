#include "Window.h"
#include "src/opengl/error.h"

#include <tuple>

static std::pair<int, int> GetFrameBufferSize(GLFWwindow& window);

Window::Window(const GLint height, const GLint width, const std::string_view& title, bool fullScreen /*= true*/)
{
	auto monitor = fullScreen ? glfwGetPrimaryMonitor() : nullptr;
	m_window = glfwCreateWindow(height, width, title.data(), monitor, nullptr);
	if (!m_window)
	{
		throw std::runtime_error("Failed to create OpenGL window.\n");
	}

	InitializeDimensions();
	MakeContextCurrent();

	CHECK_ERRORS;
}

Window::Window(Window&& rhs)
{
	*this = std::move(rhs);
}

Window& Window::operator=(Window&& rhs)
{
	m_window = rhs.m_window;
	rhs.m_window = nullptr;
	return *this;
}

void Window::MakeContextCurrent() const
{
	glfwMakeContextCurrent(m_window);
}

void Window::Close() const
{
	glfwSetWindowShouldClose(m_window, GL_TRUE);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers() const
{
	glfwSwapBuffers(m_window);
}

Window::operator GLFWwindow*() const
{
	return Get();
}

GLFWwindow* Window::Get() const
{
	return m_window;
}

GLfloat Window::Height() const
{
	return m_height;
}

GLfloat Window::Width() const
{
	return m_width;
}

void Window::InitializeDimensions()
{
	const auto [width, height] = GetFrameBufferSize(*m_window);
	m_width = static_cast<float>(width);
	m_height = static_cast<float>(height);
}

std::pair<int, int> GetFrameBufferSize(GLFWwindow& window)
{
	int width, height;
	glfwGetFramebufferSize(&window, &width, &height);
	return { width, height };
}
