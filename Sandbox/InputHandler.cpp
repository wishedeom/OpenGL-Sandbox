#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "InputHandler.h"
#include "Window.h"

//static void keyCallback(GLFWwindow* const window, const GLint key, const GLint scancode, const GLint action, const GLint mode);

InputHandler::InputHandler(const Window& window, Camera& camera)
	: _camera { camera }
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window.get(), keyCallback);
}

Camera& InputHandler::camera()
{
	return _camera;
}

//LateralDirection InputHandler::lateralDirection() const
//{
//	return LateralDirection();
//}
//
//void InputHandler::lateralDirection(const LateralDirection& direction)
//{
//	_lateralDirection = direction;
//}

void InputHandler::update()
{
	switch (_axialDirection)
	{
		case AxialDirection::Forward:
			_camera.translate({ 0.0f, 0.0f, _speed });
			break;
		case AxialDirection::Backward:
			_camera.translate({ 0.0f, 0.0f, -_speed });;
			break;
	}
	switch (_lateralDirection)
	{
		case LateralDirection::Left:
			_camera.translate({ _speed, 0.0f, 0.0f });
			break;
		case LateralDirection::Right:
			_camera.translate({ -_speed, 0.0f, 0.0f });
			break;
	}
}

static void keyCallback(GLFWwindow* const window, const GLint key, const GLint, const GLint action, const GLint)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	static auto& camera = handler.camera();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
		{
			handler._axialDirection = AxialDirection::Forward;
		}
		else if (action == GLFW_RELEASE)
		{
			handler._axialDirection = AxialDirection::None;
		}
	}
	if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
		{
			handler._axialDirection = AxialDirection::Backward;
		}
		else if (action == GLFW_RELEASE)
		{
			handler._axialDirection = AxialDirection::None;
		}
	}
	if (key == GLFW_KEY_A)
	{
		if (action == GLFW_PRESS)
		{
			handler._lateralDirection = LateralDirection::Left;
		}
		else if (action == GLFW_RELEASE)
		{
			handler._lateralDirection = LateralDirection::None;
		}
	}
	if (key == GLFW_KEY_D)
	{
		if (action == GLFW_PRESS)
		{
			handler._lateralDirection = LateralDirection::Right;
		}
		else if (action == GLFW_RELEASE)
		{
			handler._lateralDirection = LateralDirection::None;
		}
	}
}
