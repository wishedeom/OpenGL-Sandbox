#include "Window.h"

Window::Window(const GLint height, const GLint width, const std::string& title)
{
	_window = glfwCreateWindow(height, width, title.c_str(), nullptr, nullptr);
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

GLFWwindow* Window::get() const
{
	return _window;
}

glm::mat4 Window::projectionMatrix() const
{
	return glm::perspective(glm::radians(45.0f), _width / _height, 0.1f, 100.0f);
}
