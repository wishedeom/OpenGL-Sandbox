#include "Window.h"

Window::Window(const GLint height, const GLint width, const std::string& title, const bool fullScreen /*= true*/)
{
	auto monitor = fullScreen ? glfwGetPrimaryMonitor() : nullptr;
	_window = glfwCreateWindow(height, width, title.c_str(), monitor, nullptr);
	if (!_window)
	{
		throw std::runtime_error("Failed to create OpenGL window.\n");
	}
	int iwidth, iheight;
	glfwGetFramebufferSize(_window, &iwidth, &iheight);
	_width = static_cast<float>(iwidth);
	_height = static_cast<float>(iheight);
	makeContextCurrent();
}

void Window::makeContextCurrent() const
{
	glfwMakeContextCurrent(_window);
}

void Window::close() const
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(_window);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(_window);
}

Window::operator GLFWwindow*() const
{
	return get();
}

GLFWwindow* Window::get() const
{
	return _window;
}

GLfloat Window::height() const
{
	return _height;
}

GLfloat Window::width() const
{
	return _width;
}
