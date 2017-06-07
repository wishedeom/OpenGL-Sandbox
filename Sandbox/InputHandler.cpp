#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

#include "inputhandler.h"
#include "gameaction.h"
#include "playercontroller.h"
#include "Camera.h"
#include "Window.h"

InputHandler::InputHandler(PlayerController& playerController, const InputScheme& inputScheme)
	: _playerController { &playerController }
	, _inputScheme { inputScheme }
{
	const auto& window = _playerController->camera().window();
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetScrollCallback(window, scrollWheelCallback);
	glfwSetWindowUserPointer(playerController.camera().window(), this);
}

void InputHandler::signal(const InputAction inputAction)
{
	_playerController->signal(_inputScheme[inputAction]);
}

void InputHandler::keyboardCallback(GLFWwindow* const window, const GLint key, const GLint, const GLint action, const GLint)
{
	static auto& inputHandler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		inputHandler.signal(InputAction::EscPress);
	}
	else if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
		{
			inputHandler.signal(InputAction::WPress);
		}
		else if (action == GLFW_RELEASE)
		{
			inputHandler.signal(InputAction::WRelease);
		}
	}
	else if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
		{
			inputHandler.signal(InputAction::SPress);
		}
		else if (action == GLFW_RELEASE)
		{
			inputHandler.signal(InputAction::SRelease);
		}
	}
	else if (key == GLFW_KEY_A)
	{
		if (action == GLFW_PRESS)
		{
			inputHandler.signal(InputAction::APress);
		}
		else if (action == GLFW_RELEASE)
		{
			inputHandler.signal(InputAction::ARelease);
		}
	}
	else if (key == GLFW_KEY_D)
	{
		if (action == GLFW_PRESS)
		{
			inputHandler.signal(InputAction::DPress);
		}
		else if (action == GLFW_RELEASE)
		{
			inputHandler.signal(InputAction::DRelease);
		}
	}
}

static void cursorPositionCallback(GLFWwindow* const window, const double x, const double y)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	handler._playerController->setMousePosition(x, y);
}

void scrollWheelCallback(GLFWwindow * const window, const double /*x*/, const double y)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	static auto& camera = handler._playerController->camera();
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
