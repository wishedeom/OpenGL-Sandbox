#include "inputaction.h"

InputAction ToInputAction(const GLint key, const GLint scancode, const GLint action, const GLint mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		return InputAction::EscPress;
	}
	else if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
		{
			return InputAction::WPress;
		}
		else if (action == GLFW_RELEASE)
		{
			return InputAction::WRelease;
		}
	}
	else if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
		{
			return InputAction::SPress;
		}
		else if (action == GLFW_RELEASE)
		{
			return InputAction::SRelease;
		}
	}
	else if (key == GLFW_KEY_A)
	{
		if (action == GLFW_PRESS)
		{
			return InputAction::APress;
		}
		else if (action == GLFW_RELEASE)
		{
			return InputAction::ARelease;
		}
	}
	else if (key == GLFW_KEY_D)
	{
		if (action == GLFW_PRESS)
		{
			return InputAction::DPress;
		}
		else if (action == GLFW_RELEASE)
		{
			return InputAction::DRelease;
		}
	}
	else if (key == GLFW_KEY_SPACE)
	{
		if (action == GLFW_PRESS)
		{
			return InputAction::SpacePress;
		}
	}

	return InputAction::None;
}
