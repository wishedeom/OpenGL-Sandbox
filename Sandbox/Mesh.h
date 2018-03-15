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
	using Vertices = std::vector<Vertex>;
	using Indices = std::vector<GLuint>;

	Mesh(Vertices vertices, Indices indices);
	void draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& transform = glm::mat4());
	void draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& transform = glm::mat4()) const;
	void setVertices(const std::vector<Vertex>& vertices);
	void setIndices(const std::vector<GLuint>& indices);

private:
	void init();
	void bindVertexData() const;
	void bindIndexData() const;

private:
	Vertices _vertices;
	Indices _indices;
	
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
};

Mesh MakeCube();
Mesh MakeSquare();
Mesh MakeQuad(const glm::vec3& pivot, const glm::vec3& hCorner, const glm::vec3& vCorner);

Mesh MakeSphere(float radius = 1.0f, size_t sections = 100);
Mesh MakeSphere();
