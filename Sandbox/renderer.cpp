#include "renderer.h"
#include "ShaderProgram.h"
#include "camera.h"
#include "entity.h"
#include "src/opengl/error.h"
#include "VAOBinding.h"

Renderer::Renderer(const ShaderProgram& program, const Camera& camera)
	: m_program(program)
	, m_camera(camera)
{}

void Renderer::Draw(const Entity& entity)
{
	// Use shader program
	m_program.Use();

	// Bind camera to shader
	m_program.SetUniform("projection", m_camera.projection());

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

	float f;
	glGetVertexAttribfv(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &f);
	volatile float g = f;

	float a[] = { 1.0f, 1.0f, 1.0f };
	glVertexAttrib3fv(1, a);

	glDrawElements(GL_TRIANGLES, entity.mesh._indices.size(), GL_UNSIGNED_INT, 0);
	CHECK_ERRORS;
}
