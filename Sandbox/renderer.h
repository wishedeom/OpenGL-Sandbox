#pragma once

#include "src/colour.h"

struct Entity;

class Camera;
class ShaderProgram;

class Renderer final
{
public:
	Renderer(const ShaderProgram& program, const Camera& camera);
	void Draw(const Entity& entity);

	void SetLightColour(Colour colour);

private:
	void BindLightColour() const;

	const ShaderProgram& m_program;
	const Camera& m_camera;

	Colour m_lightColour;
};
