#include "Material.h"
#include "ShaderProgram.h"
#include "utils.h"

void Material::bind(const ShaderProgram& shader) const
{
	// Bind diffuse texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(shader.GetUniformLocation("material.diffuse"), 0);
	glBindTexture(GL_TEXTURE_2D, diffuse);


	// Bind specular texture
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(shader.GetUniformLocation("material.specular"), 1);
	glBindTexture(GL_TEXTURE_2D, specular);

	// Bind shininess
	glUniform1f(shader.GetUniformLocation("material.shininess"), shininess);
}
