#include "ShaderProgram.h"
#include "GlHelpers.h"
namespace Graphic {

ShaderProgram::ShaderProgram()
{
	m_progId = glCreateProgram();
}

LinkShaderProgramResult ShaderProgram::LinkProgram()
{
	glLinkProgram(m_progId);
	GLint linkResult;
	glGetProgramiv(m_progId, GL_LINK_STATUS, &linkResult);
	std::string errorMessage = Helpers::GetProgramlInfoLog(m_progId);
	if (linkResult == GL_FALSE)
	{
		LOG_ERROR(errorMessage, "GRAPHIC::ShaderProgram");
		return LinkShaderProgramError(LinkProgramError,errorMessage);
	}
	m_usedShader.clear();
	return LinkShaderProgramResult();
}

void ShaderProgram::AttachShader(std::unique_ptr<Shader> i_shader)
{
	glAttachShader(m_progId,i_shader->GetShaderID());
	m_usedShader.push_back(std::move(i_shader));
	LOG_DEBUG("std::move(std::unique<Shader>)", "GRAPHIC::ShaderProgram");
}
GLint ShaderProgram::GetUniformLocation(std::string i_name)
{
	return glGetUniformLocation(m_progId, i_name.c_str());
}
void ShaderProgram::Use()
{
	glUseProgram(m_progId);
}
ShaderProgram::~ShaderProgram()
{
}
}
