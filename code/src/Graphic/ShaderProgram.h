#pragma once
#include "Shader.h"

namespace Graphic
{
	enum LinkShaderProgramErrorCode {
		LinkProgramError
	};
	using LinkShaderProgramError = MHTL::error<LinkShaderProgramErrorCode>;
	using LinkShaderProgramResult = MHTL::result<void, LinkShaderProgramError>;

	class ShaderProgram {
	private:
		GLuint m_progId;
		std::vector<std::unique_ptr<Shader>> m_usedShader;
	public:
		ShaderProgram();
		LinkShaderProgramResult LinkProgram();
		void AttachShader(std::unique_ptr<Shader> i_shader);
		GLint GetUniformLocation(std::string i_name);
		void Use();
		~ShaderProgram();
	};
}