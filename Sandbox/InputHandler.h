#pragma once

class Camera;
class Window;

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

class PlayerController final
{
private:
	friend static void KeyboardCallback(GLFWwindow* const window, const GLint key, const GLint, const GLint action, const GLint);
	friend static void CursorPositionCallback(GLFWwindow* const window, const double x, const double y);
	friend static void ScrollWheelCallback(GLFWwindow* const window, const double x, const double y);

public:
	PlayerController(const Window& window, Camera& camera);
	Camera& camera();
	//LateralDirection lateralDirection() const;
	//void lateralDirection(const LateralDirection& direction);
	void update();

private:
	Camera& _camera;
	GLfloat _speed = 0.025f;
	GLfloat _sensitivity = 2.0f;
	AxialDirection _axialDirection = AxialDirection::None;
	LateralDirection _lateralDirection = LateralDirection::None;
	glm::vec2 _mousePosition = {};
	glm::vec2 _oldMousePosition = {};
};
