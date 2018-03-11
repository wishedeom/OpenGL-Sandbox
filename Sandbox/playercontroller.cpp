#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "playercontroller.h"
#include "gameaction.h"
#include "Window.h"

//static void keyCallback(GLFWwindow* const window, const GLint key, const GLint scancode, const GLint action, const GLint mode);

PlayerController::PlayerController(const Window& window, Camera& camera)
	: _camera { &camera }
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera& PlayerController::GetCamera()
{
	return *_camera;
}

void PlayerController::update()
{
	switch (_axialDirection)
	{
		case AxialDirection::Forward:
			_camera->translate(_speed * _camera->forward());
			break;
		case AxialDirection::Backward:
			_camera->translate(-_speed * _camera->forward());;
			break;
	}
	switch (_lateralDirection)
	{
		case LateralDirection::Left:
			_camera->translate(-_speed * _camera->right());
			break;
		case LateralDirection::Right:
			_camera->translate(_speed * _camera->right());
			break;
	}

	const auto diff = _mousePosition - _oldMousePosition;
	_oldMousePosition = _mousePosition;
	_camera->rotateRight(glm::sign(diff.x) * glm::radians(_sensitivity));
	_camera->rotateUp(glm::sign(diff.y) * glm::radians(_sensitivity));
}

void PlayerController::signal(const GameAction action)
{
	switch (action)
	{
		case GameAction::MoveAxialForward:
			_axialDirection = AxialDirection::Forward;
			break;
		case GameAction::MoveAxialBackward:
			_axialDirection = AxialDirection::Backward;
			break;
		case GameAction::MoveAxialNone:
			_axialDirection = AxialDirection::None;
			break;
		case GameAction::MoveLateralRight:
			_lateralDirection = LateralDirection::Right;
			break;
		case GameAction::MoveLateralLeft:
			_lateralDirection = LateralDirection::Left;
			break;
		case GameAction::MoveLateralNone:
			_lateralDirection = LateralDirection::None;
			break;
		case GameAction::CloseWindow:
			_camera->window().close();
			break;
	}
}

void PlayerController::setMousePosition(const double x, const double y)
{
	_mousePosition = { x, y };
}
