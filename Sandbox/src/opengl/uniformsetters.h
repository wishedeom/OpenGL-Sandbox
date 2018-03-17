#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning (push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#pragma warning (pop)

namespace OpenGL
{
	void SetVec3(GLint location, const glm::vec3& vector);
	void SetMat4(GLint location, const glm::mat4& matrix);
}
