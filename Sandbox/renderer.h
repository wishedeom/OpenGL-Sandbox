#pragma once

#include "src/colour.h"

struct Entity;

class Camera;
class ShaderProgram;

class Renderer final
{
public:
	Renderer(const ShaderProgram& program, const Camera& camera);
	void Draw(const Entity& entity) const;

	void SetAmbientLightColour(Colour colour);
	void SetAmbientLightStrength(float strength);
	
	void SetLightColour(const Colour& colour);
	void SetLightPosition(const glm::vec3& position);

private:
	Colour BindAmbientLightColour(Colour colour) const;
	float BindAmbientLightStrength(float strength) const;
	Colour BindLightColour(const Colour& colour) const;
	glm::vec3 BindLightPosition(const glm::vec3& position) const;

	const ShaderProgram& m_program;
	const Camera& m_camera;

	Colour m_ambientLightColour;
	float m_ambientLightStrength;
	
	Colour m_lightColour;
	glm::vec3 m_lightPosition;
};
