#include "uniformsetters.h"
#include "functions.h"

void OpenGL::SetVec3(const GLint location, const glm::vec3& vector)
{
	InjectErrorChecking(glUniform3fv, location, 1, value_ptr(vector));
}

void OpenGL::SetMat4(const GLint location, const glm::mat4& matrix)
{
	InjectErrorChecking(glUniformMatrix4fv, location, 1, false, value_ptr(matrix));
}
