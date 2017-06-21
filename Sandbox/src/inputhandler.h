#pragma once

#include "inputscheme.h"

class PlayerController;

class InputHandler
{
public:
	InputHandler(PlayerController& playerController, const InputScheme& inputScheme);
	void signal(InputAction inputAction);

private:
	static void keyboardCallback(GLFWwindow*window, GLint key, GLint, GLint action, GLint);
	friend static void cursorPositionCallback(GLFWwindow* window, double x, double y);
	friend static void scrollWheelCallback(GLFWwindow* window, double x, double y);

	PlayerController* _playerController;
	InputScheme _inputScheme;
};

