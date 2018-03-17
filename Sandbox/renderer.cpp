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
	, m_lightColour(Colour::White)
{
	BindLightColour();
}

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

void Renderer::SetLightColour(Colour colour)
{
	m_lightColour = colour;
	BindLightColour();
}

void Renderer::BindLightColour() const
{
	const auto loc = m_program.GetUniformLocation("lightColour");
	const glm::vec3 colour = m_lightColour;
	m_program.Use();

	OpenGL::SetVec3(loc, m_lightColour);
	//glUniform3fv(loc, 1, value_ptr(glm::vec3(m_lightColour)));
	//CHECK_ERRORS;
}
