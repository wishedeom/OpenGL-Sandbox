#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "InputHandler.h"
#include "Window.h"

//static void keyCallback(GLFWwindow* const window, const GLint key, const GLint scancode, const GLint action, const GLint mode);

InputHandler::InputHandler(const Window& window, Camera& camera)
	: _camera { camera }
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, _keyboardCallback);
	glfwSetCursorPosCallback(window, _cursorPositionCallback);
	glfwSetScrollCallback(window, _scrollWheelCallback);
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
			_camera.translate(_speed * _camera.forward());
			break;
		case AxialDirection::Backward:
			_camera.translate(-_speed * _camera.forward());;
			break;
	}
	switch (_lateralDirection)
	{
		case LateralDirection::Left:
			_camera.translate(-_speed * _camera.right());
			break;
		case LateralDirection::Right:
			_camera.translate(_speed * _camera.right());
			break;
	}

	const auto diff = _mousePosition - _oldMousePosition;
	_oldMousePosition = _mousePosition;
	_camera.rotateRight(glm::sign(diff.x) * glm::radians(_sensitivity));
	_camera.rotateUp(glm::sign(diff.y) * glm::radians(_sensitivity));
} 

static void _keyboardCallback(GLFWwindow* const window, const GLint key, const GLint, const GLint action, const GLint)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
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

static void _cursorPositionCallback(GLFWwindow* const window, const double x, const double y)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	handler._mousePosition = { x, y };
}

void _scrollWheelCallback(GLFWwindow * const window, const double /*x*/, const double y)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	static auto& camera = handler.camera();
	const auto fov = camera.fov();
	if (fov >= 1.0f && fov <= 45.0f)
	{
		camera.setFov(static_cast<float>(fov - y));
	}
	else if (fov < 1.0f)
	{
		camera.setFov(1.0f);
	}
	else if (fov >= 45.0f)
	{
		camera.setFov(45.0f);
	}

}
