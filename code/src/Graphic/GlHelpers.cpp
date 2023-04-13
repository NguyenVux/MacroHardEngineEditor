#include "GlHelpers.h"
#include <string>

namespace Graphic
{
std::string Graphic::Helpers::GetShaderInfoLog(GLuint i_shaderId)
{
	char buffer[1000];
	GLsizei outputLength;
	glGetShaderInfoLog(i_shaderId, sizeof(buffer), &outputLength, buffer);
	std::string compileMessage(buffer, outputLength);
	return compileMessage;
}

std::string Graphic::Helpers::GetProgramlInfoLog(GLuint i_shaderId)
{
	char buffer[1000];
	GLsizei outputLength;
	glGetProgramInfoLog(i_shaderId, sizeof(buffer), &outputLength, buffer);
	std::string compileMessage(buffer, outputLength);
	return compileMessage;
}

}
