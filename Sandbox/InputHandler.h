#pragma once

#include "inputscheme.h"
#include "src/opengl/event.h"
#include "src/opengl/eventregistrar.h"

class PlayerController;

class InputHandler
{
public:
	InputHandler(PlayerController& playerController, const InputScheme& inputScheme);
	void signal(InputAction inputAction);
	EventRegistrar<InputAction> Callbacks();

private:
	static void keyboardCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
	friend static void cursorPositionCallback(GLFWwindow* const window, const double x, const double y);
	friend static void scrollWheelCallback(GLFWwindow* const window, const double x, const double y);

	PlayerController* _playerController;
	InputScheme _inputScheme;
	Event<InputAction> m_callbacks;
};

