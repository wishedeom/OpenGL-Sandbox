#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera;
class Window;
enum class GameAction;

class PlayerController final
{
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

public:
	PlayerController(const Window& window, Camera& camera);

	Camera& GetCamera();
	void Update();
	void Signal(const GameAction action);
	void setMousePosition(double x, double y);

private:
	Camera* _camera;
	GLfloat _speed = 0.025f;
	GLfloat _sensitivity = 2.0f;
	AxialDirection _axialDirection = AxialDirection::None;
	LateralDirection _lateralDirection = LateralDirection::None;
	glm::vec2 _mousePosition = {};
	glm::vec2 _oldMousePosition = {};
};
