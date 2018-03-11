#include "error.h"
#include "C:/Projects/Sandbox/Sandbox\utils.h"

#include <iostream>
#include <sstream>

void OpenGL::ClearErrorFlag()
{
	glGetError();
}

OpenGL::Error OpenGL::GetError()
{
	return Error(glGetError());
}

void OpenGL::PrintErrors()
{
	for (auto err = GetError(); err != Error::NoError; err = GetError())
	{
		std::cout << ToString(err) << '\n';
	}

}

void OpenGL::CheckErrors(const std::string_view& file, const size_t line)
{
	const auto error = GetError();
	if (error != Error::NoError)
	{
		throw Exception(error, file, line);
	}
}

constexpr const char* OpenGL::ToString(const Error error)
{
	switch (error)
	{
		case Error::NoError:
			return "NoError";
		case Error::ContextLost:
			return "ContextLost";
		case Error::InvalidEnum:
			return "InvalidEnum";
		case Error::InavlidValue:
			return "InavlidValue";
		case Error::InvalidOperation:
			return "InvalidOperation";
		case Error::InvalidFramebufferOperation:
			return "InvalidFramebufferOperation";
		case Error::OutOfMemory:
			return "OutOfMemory";
		case Error::StackOverflow:
			return "StackOverflow";
		case Error::StackUnderflow:
			return "StackUnderflow";
		default:
			return "(Inexhaustive pattern)";
	}
}

OpenGL::Exception::Exception(const Error error, const std::string_view& file, const size_t line)
	: m_message(MakeMessage(error, file, line))
{}

std::string OpenGL::Exception::MakeMessage(const Error error, const std::string_view& file, size_t line)
{
	std::stringstream ss;
	ss << "OpenGL error: " << file << ':' << line << ": (" << util::to_underlying(error) << "): " << ToString(error);
	return ss.str();
}

const char* OpenGL::Exception::what() const
{
	return m_message.c_str();
}
