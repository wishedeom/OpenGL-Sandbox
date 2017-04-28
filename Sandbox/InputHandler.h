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

class InputHandler final
{
private:
	friend static void keyCallback(GLFWwindow* const window, const GLint key, const GLint, const GLint action, const GLint);

public:
	InputHandler(const Window& window, Camera& camera);
	Camera& camera();
	//LateralDirection lateralDirection() const;
	//void lateralDirection(const LateralDirection& direction);
	void update();

private:
	Camera& _camera;
	GLfloat _speed = 0.005f;
	AxialDirection _axialDirection = AxialDirection::None;
	LateralDirection _lateralDirection = LateralDirection::None;
};
