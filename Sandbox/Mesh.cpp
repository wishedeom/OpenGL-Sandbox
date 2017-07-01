#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"

using namespace component;

Mesh::Mesh(Entity& entity)
	: Component(entity)
{
	init();
}

void Mesh::draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& /*transform*/ /*= glm::mat4()*/) const
{
	// Use shader program
	shader.use();

	// Bind camera to shader
	camera.bind(shader);

	// Bind model-space transform to shader
	//glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));
	glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, glm::value_ptr(entity().get<Transform>().matrix()));

	// Draw mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void component::Mesh::setVertices(const std::vector<Vertex>& vertices)
{
	_vertices = vertices;
	bindVertexData();
}

void component::Mesh::setIndices(const std::vector<GLuint>& indices)
{
	_indices = indices;
	bindIndexData();
}

void component::Mesh::bindVertexData() const
{
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(decltype(_vertices)::value_type), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(decltype(_vertices)::value_type), _vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void component::Mesh::bindIndexData() const
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(decltype(_indices)::value_type), _indices.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Mesh::init()
{
	// Setup mesh
	// Generate OpenGL objects
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	bindVertexData();
	bindIndexData();

	// Prepare vertex attribute pointers
	// Positions
	glBindVertexArray(_vao);
	glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(decltype(Vertex::position)::value_type), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void component::Mesh::update(double)
{

}
