#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "playercontroller.h"
#include "gameaction.h"
#include "Window.h"

//static void keyCallback(GLFWwindow* const window, const GLint key, const GLint scancode, const GLint action, const GLint mode);

PlayerController::PlayerController(const Window& window, Camera& camera)
	: m_camera(&camera)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera& PlayerController::GetCamera()
{
	return *m_camera;
}

void PlayerController::UpdateTransforms()
{
	const auto velocity = GetVelocity();
	m_camera->translate(velocity);

	const auto diff = m_mousePosition - m_oldMousePosition;
	m_oldMousePosition = m_mousePosition;
	m_camera->rotateRight(glm::sign(diff.x) * glm::radians(m_sensitivity));
	m_camera->rotateUp(glm::sign(diff.y) * glm::radians(m_sensitivity));
}

void PlayerController::Signal(const GameAction action)
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
			m_camera->window().Close();
			break;
	}
}

void PlayerController::setMousePosition(const double x, const double y)
{
	m_mousePosition = { x, y };
}

template <typename E>
constexpr float GetDirectionFactor(const E direction)
{
	const auto sign = ToSign(direction);
	return util::to_underlying(sign);
}

glm::vec3 PlayerController::GetVelocity() const
{
	const auto axialVelocity = GetVelocity(_axialDirection);
	const auto lateralVelocity = GetVelocity(_lateralDirection);
	return axialVelocity + lateralVelocity;
}

template <typename E>
inline glm::vec3 PlayerController::GetVelocityDirection() const
{
	if constexpr (std::is_same_v<E, AxialDirection>)
	{
		return m_camera->forward();
	}
	else if constexpr (std::is_same_v<E, LateralDirection>)
	{
		return m_camera->right();
	}
	else
	{
		static_assert(false);
	}
}

template <typename E>
glm::vec3 PlayerController::GetVelocity(const E direction) const
{
	return GetDirectionFactor(direction) * _speed * GetVelocityDirection<E>();
}
