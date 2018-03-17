#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "VAOBinding.h"
#include "src/opengl/error.h"

Mesh::Mesh(Vertices vertices, Indices indices)
	: _vertices(std::move(vertices))
	, _indices(std::move(indices))
{
	init();
}

const Mesh::Vertices& Mesh::GetVertices() const
{
	return _vertices;
}

const Mesh::Indices& Mesh::GetIndices() const
{
	return _indices;
}

Mesh Mesh::Scale(const float factor) const
{
	Vertices vertices;
	vertices.reserve(_vertices.size());

	for (auto& vertex : _vertices)
	{
		Vertex v = vertex;
		v.position *= factor;
		vertices.push_back(v);
	}

	return { std::move(vertices), _indices };
}

void Mesh::SetColour(const glm::vec3& colour)
{
	for (auto& vertex : _vertices)
	{
		vertex.colour = colour;
	}

	bindVertexData();
}

void Mesh::bindVertexData() const
{
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

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
	glGenVertexArrays(1, &_vao); CHECK_ERRORS;
	glGenBuffers(1, &_vbo); CHECK_ERRORS;
	glGenBuffers(1, &_ebo); CHECK_ERRORS;

	bindVertexData();
	bindIndexData();

	// Prepare vertex attribute pointers
	// Positions
	glBindVertexArray(_vao); CHECK_ERRORS;

	glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(decltype(Vertex::position)::value_type), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position)); CHECK_ERRORS;
	glVertexAttribPointer(1, sizeof(Vertex::normal) / sizeof(decltype(Vertex::normal)::value_type), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal)); CHECK_ERRORS;
	glVertexAttribPointer(2, sizeof(Vertex::colour) / sizeof(decltype(Vertex::colour)::value_type), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, colour)); CHECK_ERRORS;
	//glEnableVertexAttribArray(1); CHECK_ERRORS;

	glEnableVertexAttribArray(0); CHECK_ERRORS;
	glEnableVertexAttribArray(1); CHECK_ERRORS;
	glEnableVertexAttribArray(2); CHECK_ERRORS;

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

Mesh MakeSphere(float radius /*= 1.0f*/, size_t sections /*= 100*/)
{
	// Positions
	std::vector<Vertex> vertices;
	vertices.push_back({ { 0.0f, -radius, 0.0f } });

	for (int level = 0; level < sections; ++level)
	{
		const auto azimuth = (level + 1.0f) / (sections + 1.0f) * pi<float> - pi<float> / 2;
		const auto y = radius * std::sin(azimuth);
		const auto r = radius * std::cos(azimuth);
		for (int i = 0; i < sections; ++i)
		{
			const auto angle = 2.0f * pi<float> * i / sections;
			const auto x = r * std::cos(angle);
			const auto z = r * std::sin(angle);

			Vertex vertex;
			vertex.position = { x, y, z };
			
			vertices.push_back(vertex);
		}
	}
	vertices.push_back({ { 0.0f, radius, 0.0f } });

	// Normals
	for (auto& vertex : vertices)
	{
		vertex.normal = glm::normalize(vertex.position);
	}
	
	std::vector<GLuint> indices;
	for (int i = 1; i < sections; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(sections);

	for (int level = 0; level < sections; ++level)
	{
		for (int i = (level - 1) * sections + 1; i < level * sections + 1; ++i)
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + sections);

			indices.push_back(i);
			indices.push_back(i + sections);
			indices.push_back(i + sections - 1);
		}

		indices.push_back(vertices.size() - 2);
		indices.push_back((sections - 1) * sections + 1);
		indices.push_back(vertices.size() - 1);
	}

	for (int i = (sections - 1) * sections + 1; i < (sections) * sections + 1; ++i)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(vertices.size() - 1);
	}

	indices.push_back(vertices.size() - 2);
	indices.push_back((sections - 1) * sections + 1);
	indices.push_back(vertices.size() - 1);

	return { std::move(vertices), std::move(indices) };
}
