#pragma once

#include "inputscheme.h"

class PlayerController;

class InputHandler
{
public:
	InputHandler(PlayerController& playerController, const InputScheme& inputScheme);
	void signal(InputAction inputAction);

private:
	static void keyboardCallback(GLFWwindow* const window, const GLint key, const GLint, const GLint action, const GLint);
	friend static void cursorPositionCallback(GLFWwindow* const window, const double x, const double y);
	friend static void scrollWheelCallback(GLFWwindow* const window, const double x, const double y);

	PlayerController* _playerController;
	InputScheme _inputScheme;
};

