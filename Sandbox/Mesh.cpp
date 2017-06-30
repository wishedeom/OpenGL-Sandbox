#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Material& material)
	: _vertices { vertices }
	, _indices { indices }
	, _material { material }
{
	init();
}

void Mesh::draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& transform) const
{
	// Bind material to shader
	_material.bind(shader);

	// Bind camera to shader
	camera.bind(shader);

	// Bind model-space transform to shader
	glUniformMatrix4fv(shader.getUniform("model"), 1, GL_FALSE, glm::value_ptr(transform));

	// Draw mesh
	glBindVertexArray(_vao);
	if (_indices.empty())
	{
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
		//reportOpenGLErrors();
	}
	glBindVertexArray(0);
}

void Mesh::init()
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

Mesh::Builder::Builder() = default;

Mesh::Builder& Mesh::Builder::setVertices(const std::vector<Vertex>& vertices)
{
	_vertices = vertices;
	return *this;
}

Mesh::Builder& Mesh::Builder::setIndices(const std::vector<GLuint>& indices)
{
	_indices = indices;
	return *this;
}

Mesh::Builder& Mesh::Builder::setMaterial(const Material& material)
{
	_material = material;
	return *this;
}

Mesh::Builder& Mesh::Builder::addVertex(const Vertex& vertex)
{
	_vertices.push_back(vertex);
	return *this;
}

Mesh::Builder& Mesh::Builder::addIndex(GLuint index)
{
	_indices.push_back(index);
	return *this;
}

Mesh Mesh::Builder::build() const
{
	return Mesh(_vertices, _indices, *_material);
}
