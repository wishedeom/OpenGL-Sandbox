#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vertex.h"
#include "Material.h"

class ShaderProgram;

class Mesh final
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Material& material);
	void draw(const ShaderProgram& shader) const;

private:
	void _init();

private:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	Material _material;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
};
