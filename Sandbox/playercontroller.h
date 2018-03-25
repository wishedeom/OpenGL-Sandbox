#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera;
class Window;
enum class GameAction;

enum class AxialDirection
{
	None,
	Forward,
	Backward,
};

enum class LateralDirection
{
	None,
	Left,
	Right,
};

enum class Sign : char
{
	Negative = -1,
	Zero     =  0,
	Positive =  1,
};

constexpr Sign ToSign(const AxialDirection direction)
{
	switch (direction)
	{
	case AxialDirection::Backward:
		return Sign::Negative;
	case AxialDirection::None:
		return Sign::Zero;
	case AxialDirection::Forward:
		return Sign::Positive;
	default:
		throw 0;
	}
}

constexpr Sign ToSign(const LateralDirection direction)
{
	switch (direction)
	{
	case LateralDirection::Left:
		return Sign::Negative;
	case LateralDirection::None:
		return Sign::Zero;
	case LateralDirection::Right:
		return Sign::Positive;
	default:
		throw 0;
	}
}

class PlayerController final
{

public:
	PlayerController(const Window& window, Camera& camera);

	Camera& GetCamera();
	void UpdateTransforms();
	void Signal(const GameAction action);
	void setMousePosition(double x, double y);

private:
	glm::vec3 GetVelocity() const;

	template <typename E>
	glm::vec3 GetVelocity(E direction) const;

	template <typename E>
	glm::vec3 GetVelocityDirection() const;

	Camera* m_camera;
	GLfloat _speed = 0.025f;
	GLfloat m_sensitivity = 2.0f;
	AxialDirection _axialDirection = AxialDirection::None;
	LateralDirection _lateralDirection = LateralDirection::None;
	glm::vec2 m_mousePosition = {};
	glm::vec2 m_oldMousePosition = {};
};
