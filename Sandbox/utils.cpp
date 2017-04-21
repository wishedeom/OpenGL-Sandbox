#include <fstream>
#include <sstream>

#include "utils.h"

std::string fromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		throw std::runtime_error("File '" + filename + "'not found.");
	}
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}
