#pragma once

#include <string_view>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning (pop)

class Window final
{
public:
	friend class Context;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&& rhs);
	Window& operator=(Window&& rhs);

	void Close() const;
	bool ShouldClose() const;
	void SwapBuffers() const;
	operator GLFWwindow*() const;
	GLFWwindow* Get() const;
	GLfloat Height() const;
	GLfloat Width() const;

private:
	Window(const GLint height, const GLint width, const std::string_view& title, bool fullScreen = true);

	void MakeContextCurrent() const;
	void InitializeDimensions();

	GLFWwindow* m_window;
	GLfloat m_height;
	GLfloat m_width;
};
