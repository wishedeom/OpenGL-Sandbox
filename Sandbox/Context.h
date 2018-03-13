#pragma once

#include "src/opengl/types.h"
#include "Window.h"

#include <GLFW/glfw3.h>

#include <utility>
#include <string_view>

class Window;

// A singleton class to manage GLFW and GLEW initialization and termination, and the creation of windows.
class Context final
{
public:
	static const OpenGL::Version version;

	static Context& Get();

	Context(const Context&) = delete;
	Context(Context&&) = delete;
	Context& operator=(const Context&) = delete;
	Context& operator=(Context&&) = delete;

	Window MakeWindow(GLint height, GLint width, const std::string_view& title, bool fullScreen = false) const;

private:
	Context();
	~Context();

	void InitializeGLEW() const;

	mutable bool m_isGLEWInitialized = false;
};
