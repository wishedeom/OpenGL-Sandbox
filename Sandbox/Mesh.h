#pragma once

#include <optional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vertex.h"
#include "Material.h"

#define _USE_MATH_DEFINES
#include <math.h>

template <typename T>
constexpr T pi = T(M_PI);

class Camera;
class ShaderProgram;

class Mesh final
{
public:
	using Vertices = std::vector<Vertex>;
	using Indices = std::vector<GLuint>;

	Mesh(Vertices vertices, Indices indices);

	const Vertices& GetVertices() const;
	const Indices& GetIndices() const;

	Mesh Scale(float factor) const;
	void SetColour(const glm::vec3& colour);

private:
	void init();
	void bindVertexData() const;
	void bindIndexData() const;

public:
	Vertices _vertices;
	Indices _indices;
	
public:
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
};

Mesh MakeCube();
Mesh MakeSquare();
Mesh MakeQuad(const glm::vec3& pivot, const glm::vec3& hCorner, const glm::vec3& vCorner);

Mesh MakeSphere(float radius = 1.0f, size_t sections = 100);
