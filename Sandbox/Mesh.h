#pragma once

#include <optional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vertex.h"
#include "Material.h"

class Camera;
class ShaderProgram;

class Mesh final
{
public:
	class Builder;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Material& material);
	void draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& transform) const;

private:
	void init();

private:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	Material _material;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
};

class Mesh::Builder final
{
public:
	Builder();
	Builder& setVertices(const std::vector<Vertex>& vertices);
	Builder& setIndices(const std::vector<GLuint>& indices);
	Builder& setMaterial(const Material& material);
	Builder& addVertex(const Vertex& vertex);
	Builder& addIndex(GLuint index);
	Mesh build() const;

private:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	std::optional<Material> _material;
};
