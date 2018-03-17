#include "renderer.h"
#include "ShaderProgram.h"
#include "camera.h"
#include "entity.h"
#include "src/opengl/error.h"
#include "src/opengl/uniformsetters.h"
#include "VAOBinding.h"

Renderer::Renderer(const ShaderProgram& program, const Camera& camera)
	: m_program(program)
	, m_camera(camera)
	, m_ambientLightColour(BindAmbientLightColour(Colour::White))
	, m_ambientLightStrength(BindAmbientLightStrength(1.0f))
	, m_lightColour(BindLightColour(Colour::White))
	, m_lightPosition(BindLightPosition({ 0.0f, 0.0f, 0.0f }))
{}

void Renderer::Draw(const Entity& entity)
{
	// Use shader program
	m_program.Use();

	// Bind camera to shader
	m_program.SetUniformMat4("projection", m_camera.projection());

	glUniformMatrix4fv(m_program.GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(m_camera.projection()));
	CHECK_ERRORS;

	glUniformMatrix4fv(m_program.GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(m_camera.view()));
	CHECK_ERRORS;

	// Bind model-space transform to shader
	//glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));
	glUniformMatrix4fv(m_program.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(entity.transform));
	CHECK_ERRORS;

	// Draw mesh
	VAOBinding vaoBinding(entity.mesh._vao);
	CHECK_ERRORS;

	glDrawElements(GL_TRIANGLES, entity.mesh._indices.size(), GL_UNSIGNED_INT, 0);
	CHECK_ERRORS;
}

void Renderer::SetAmbientLightColour(const Colour colour)
{
	m_ambientLightColour = BindAmbientLightColour(colour);
}

void Renderer::SetAmbientLightStrength(const float strength)
{
	m_ambientLightStrength = BindAmbientLightStrength(strength);
}

void Renderer::SetLightColour(const Colour& colour)
{
	m_lightColour = BindLightColour(colour);
}

void Renderer::SetLightPosition(const glm::vec3& position)
{
	m_lightPosition = BindLightPosition(position);
}

Colour Renderer::BindAmbientLightColour(const Colour colour) const
{
	m_program.SetUniformVec3("ambientLightColour", colour);
	return colour;
}

float Renderer::BindAmbientLightStrength(const float strength) const
{
	m_program.SetUniformFloat("ambientLightStrength", strength);
	return strength;
}

Colour Renderer::BindLightColour(const Colour& colour) const
{
	m_program.SetUniformVec3("lightColour", colour);
	return colour;
}

glm::vec3 Renderer::BindLightPosition(const glm::vec3& position) const
{
	m_program.SetUniformVec3("lightPosition", position);
	return position;
}
