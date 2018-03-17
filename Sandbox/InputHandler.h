#pragma once

#include "inputscheme.h"
#include "src/opengl/event.h"
#include "src/opengl/eventregistrar.h"

#include <map>

class PlayerController;

class InputHandler
{
public:
	InputHandler(PlayerController& playerController, const InputScheme& inputScheme);
	void Signal(InputAction inputAction);
	EventRegistrar<InputAction> Callbacks();
	EventRegistrar<> Callbacks(InputAction action);

private:
	static void keyboardCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
	friend static void cursorPositionCallback(GLFWwindow* window, double x, double y);
	friend static void scrollWheelCallback(GLFWwindow* window, double x, double y);

	PlayerController* _playerController;
	InputScheme _inputScheme;
	Event<InputAction> m_generalCallbacks;
	std::map<InputAction, Event<>> m_specificCallbacks;
};

