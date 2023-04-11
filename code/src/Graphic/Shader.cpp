#include "Shader.h"

namespace Graphic
{

Shader::Shader(GLuint i_shaderid, ShaderType i_type): m_shaderId(i_shaderid), m_shadertype(i_type)
{

}
CreateShaderResult Shader::CreateShader(std::string i_path, ShaderType i_type)
{
	GLuint shaderId = glCreateShader(static_cast<GLenum>(i_type));
	std::ifstream file(i_path);
	if (!file.is_open())
	{
		return CreateShaderError(CreateShaderErrorCode::CannotOpenShaderFile, i_path);
	}

	std::string shaderText((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	
	const GLchar* shaderTextPtr = shaderText.c_str();
	glShaderSource(shaderId, 1, &shaderTextPtr, 0);
	glCompileShader(shaderId);
	
	GLint compileStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		char buffer[1000];
		GLsizei outputLength;
		glGetShaderInfoLog(shaderId,sizeof(buffer),&outputLength,buffer);
		std::string compileMessage(buffer, outputLength);
		return CreateShaderError(CreateShaderErrorCode::CompileError, compileMessage);
	}


	return Shader(shaderId, i_type);
}
}
