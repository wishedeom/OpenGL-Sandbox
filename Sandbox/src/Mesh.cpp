#include "Mesh.h"
//#include "ShaderProgram.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Material& material)
	: _vertices { vertices }
	, _indices { indices }
	, _material { material }
{
	_init();
}

void Mesh::draw(const ShaderProgram& shader) const
{
	// Bind material to shader
	_material.bind(shader);

	// Draw mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::_init()
{
	// Setup mesh
	// Generate OpenGL objects
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	// Bind VAO
	glBindVertexArray(_vao);
	
	// Send vertex data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(decltype(_vertices)::value_type), _vertices.data(), GL_STATIC_DRAW);

	// Send index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ARRAY_BUFFER, _indices.size() * sizeof(decltype(_indices)::value_type), _indices.data(), GL_STATIC_DRAW);

	// Prepare vertex attribute pointers
	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(decltype(Vertex::position)::value_type), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));

	// Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(Vertex::normal) / sizeof(decltype(Vertex::normal)::value_type), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));

	// Texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(Vertex::texture) / sizeof(decltype(Vertex::texture)::value_type), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, texture));

	// Unbind VAO
	glBindVertexArray(0);
}
