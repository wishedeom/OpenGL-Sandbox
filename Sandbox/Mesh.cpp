#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "VAOBinding.h"
#include "src/opengl/error.h"

#define _USE_MATH_DEFINES
#include <math.h>

template <typename T>
constexpr T pi = T(M_PI);

using namespace component;

Mesh::Mesh(Vertices vertices, Indices indices)
	: _vertices(std::move(vertices))
	, _indices(std::move(indices))
{
	init();
}

void Mesh::draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& transform)
{
	// TEMP
	//setVertices(_data.vertices);
	//setIndices(_data.indices);

	static_cast<const Mesh&>(*this).draw(shader, camera, transform);
}

void Mesh::draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& transform /*= glm::mat4()*/) const
{
	// Use shader program
	shader.Use();

	// Bind camera to shader
	camera.bind(shader);

	// Bind model-space transform to shader
	//glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));
	glUniformMatrix4fv(shader.GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(transform));
	CHECK_ERRORS;

	// Draw mesh
	VAOBinding vaoBinding(_vao);
	CHECK_ERRORS;
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	CHECK_ERRORS;
}

void Mesh::setVertices(const std::vector<Vertex>& vertices)
{
	_vertices = vertices;
	bindVertexData();
}

void Mesh::setIndices(const std::vector<GLuint>& indices)
{
	_indices = indices;
	bindIndexData();
}

void Mesh::bindVertexData() const
{
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(decltype(_vertices)::value_type), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(decltype(_vertices)::value_type), _vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::bindIndexData() const
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

Mesh MakeCube()
{
	std::vector<Vertex> vertices;
	for (float k = -0.5f; k <= 0.5f; ++k)
	{
		for (float j = -0.5f; j <= 0.5f; ++j)
		{
			for (float i = -0.5f; i <= 0.5f; ++i)
			{
				vertices.push_back({ { i, j, k } });
			}
		}
	}

	const std::vector<GLuint> indices
	{
		0, 1, 2,
		2, 1, 3,
		6, 5, 4,
		7, 5, 6,
		2, 3, 6,
		6, 3, 7,
		0, 1, 4,
		4, 1, 5,
		0, 4, 6,
		2, 0, 6,
		5, 1, 3,
		5, 3, 7,
	};

	return { std::move(vertices), std::move(indices) };
}

Mesh MakeSquare()
{
	std::vector<Vertex> vertices;
	vertices.reserve(4);
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			const glm::vec3 point = { i, j, 0.0f };
			const Vertex v = { 0.5f * point };
			vertices.push_back(v);
		}
	}
	const std::vector<GLuint> indices = { 0, 1, 2, 1, 3, 2 };
	return { vertices, indices };
}

Mesh MakeQuad(const glm::vec3& pivot, const glm::vec3& hCorner, const glm::vec3& vCorner)
{
	const glm::vec3 lastCorner = vCorner + hCorner - pivot;
	Mesh::Vertices vertices = { pivot, hCorner, vCorner, lastCorner };
	Mesh::Indices indices = { 0, 2, 1, 1, 2, 3 };
	return { std::move(vertices), std::move(indices) };
}

Mesh MakeSphere()
{
	static constexpr auto rotationalSections = 10;
	static constexpr auto horizontalSections = 10;

	std::vector<Vertex> vertices;
	vertices.push_back({ 0.0f, -1.0f, 0.0f });
	
	for (int level = 0; level < horizontalSections; ++level)
	{
		const auto azimuth = (level + 1.0f) / (horizontalSections + 1.0f) * pi<float> - pi<float> / 2;
		const auto y = std::sin(azimuth);
		const auto radius = std::cos(azimuth);
		for (int i = 0; i < rotationalSections; ++i)
		{
			const auto angle = 2.0f * pi<float> * i / rotationalSections;
			const auto x = radius * std::cos(angle);
			const auto z = radius * std::sin(angle);

			vertices.push_back({ x, y, z });
		}
	}
	vertices.push_back({ 0.0f, 1.0f, 0.0f });

	std::vector<GLuint> indices;
	for (int i = 1; i < rotationalSections; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(rotationalSections);
	
	for (int level = 0; level < horizontalSections; ++level)
	{
		for (int i = (level - 1) * rotationalSections + 1; i < level * rotationalSections + 1; ++i)
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + rotationalSections);

			indices.push_back(i);
			indices.push_back(i + rotationalSections);
			indices.push_back(i + rotationalSections - 1);
		}

		indices.push_back(vertices.size() - 2);
		indices.push_back((horizontalSections - 1) * rotationalSections + 1);
		indices.push_back(vertices.size() - 1);
	}

	for (int i = (horizontalSections - 1) * rotationalSections + 1; i < (horizontalSections) * rotationalSections + 1; ++i)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(vertices.size() - 1);
	}

	indices.push_back(vertices.size() - 2);
	indices.push_back((horizontalSections - 1) * rotationalSections + 1);
	indices.push_back(vertices.size() - 1);

	return { std::move(vertices), std::move(indices) };
}
