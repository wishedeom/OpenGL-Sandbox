#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#pragma warning (push, 0)
#include "stb_image.h"
#pragma warning (pop)
#endif // !STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

Texture::Texture(const std::string& filename, const Components req, const Type type)
	: _type { type }
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	stbi_set_flip_vertically_on_load(1);
	const auto image = stbi_load(filename.c_str(), &_width, &_height, &_channels, toIntegral(req));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::id() const
{
	return _id;
}

Texture::operator GLuint() const
{
	return id();
}

Texture::Type Texture::type() const
{
	return _type;
}
