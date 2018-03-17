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

	void SetAmbientLightColour(Colour colour);
	void SetAmbientLightStrength(float strength);

private:
	Colour BindAmbientLightColour(Colour colour) const;
	float BindAmbientLightStrength(float strength) const;

	const ShaderProgram& m_program;
	const Camera& m_camera;

	Colour m_ambientLightColour;
	float m_ambientLightStrength;
};
