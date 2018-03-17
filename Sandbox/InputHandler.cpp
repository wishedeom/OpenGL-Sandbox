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
	const auto& window = _playerController->GetCamera().window();
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetScrollCallback(window, scrollWheelCallback);
	glfwSetWindowUserPointer(playerController.GetCamera().window(), this);
}

void InputHandler::Signal(const InputAction inputAction)
{
	_playerController->Signal(_inputScheme[inputAction]);
	
	m_generalCallbacks(inputAction);
	
	const auto it = m_specificCallbacks.find(inputAction);
	if (it != m_specificCallbacks.end())
	{
		it->second();
	}
}

EventRegistrar<InputAction> InputHandler::Callbacks()
{
	return m_generalCallbacks;
}

EventRegistrar<> InputHandler::Callbacks(const InputAction action)
{
	return m_specificCallbacks[action];
}

void InputHandler::keyboardCallback(GLFWwindow* const window, const GLint key, const GLint scancode, const GLint action, const GLint mods)
{
	static auto& inputHandler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	inputHandler.Signal(ToInputAction(key, scancode, action, mods));
}

static void cursorPositionCallback(GLFWwindow* const window, const double x, const double y)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	handler._playerController->setMousePosition(x, y);
}

void scrollWheelCallback(GLFWwindow * const window, const double /*x*/, const double y)
{
	static auto& handler = *static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	static auto& camera = handler._playerController->GetCamera();
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
