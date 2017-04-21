#include "Window.h"

Window::Window(const GLint height, const GLint width, const std::string& title)
{
	_window = glfwCreateWindow(height, width, title.c_str(), nullptr, nullptr);
	if (!_window)
	{
		throw std::runtime_error("Failed to create OpenGL window.\n");
	}
	glfwGetFramebufferSize(_window, &_width, &_height);
	makeContextCurrent();
}

void Window::makeContextCurrent() const
{
	glfwMakeContextCurrent(_window);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(_window);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(_window);
}
