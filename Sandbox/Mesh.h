#pragma once

#include <optional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vertex.h"
#include "Material.h"

class Camera;
class ShaderProgram;

namespace component
{
	class Mesh final
		: public Component
	{
	public:
		class Builder;

		Mesh(Entity& entity);
		void draw(const ShaderProgram& shader, const Camera& camera, const glm::mat4& transform = glm::mat4()) const;
		void setVertices(const std::vector<Vertex>& vertices);
		void setIndices(const std::vector<GLuint>& indices);

	private:
		void init();
		void bindVertexData() const;
		void bindIndexData() const;

	private:
		std::vector<Vertex> _vertices;
		std::vector<GLuint> _indices;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ebo;

		// Inherited via Component
		virtual void update(double) override;
	};
}
