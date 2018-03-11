#pragma once

#include <exception>
#include <string>
#include <string_view>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define DEBUG

#ifdef DEBUG
#define CHECK_ERRORS OpenGL::CheckErrors(__FILE__, __LINE__)
#else
#define CHECK_ERRORS do {} while(false)
#endif

namespace OpenGL
{
	enum class Error : GLenum;
	class Exception;

	void ClearErrorFlag();
	Error GetError();
	void PrintErrors();
	void CheckErrors(const std::string_view& file, size_t line);
	constexpr const char* ToString(Error error);
}

enum class OpenGL::Error
	: GLenum
{
	NoError                     = GL_NO_ERROR,
	ContextLost                 = GL_CONTEXT_LOST,
	InvalidEnum                 = GL_INVALID_ENUM,
	InavlidValue                = GL_INVALID_VALUE,
	InvalidOperation            = GL_INVALID_OPERATION,
	InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
	OutOfMemory                 = GL_OUT_OF_MEMORY,
	StackOverflow               = GL_STACK_OVERFLOW,
	StackUnderflow              = GL_STACK_UNDERFLOW,
};

class OpenGL::Exception final
	: public std::exception
{
public:
	Exception(Error error, const std::string_view& file, size_t line);
	virtual const char* what() const override;

private:
	static std::string MakeMessage(Error error, const std::string_view& file, size_t line);

	Error m_error;
	std::string m_message;
};
