#pragma once 
#include <string>
#include <fstream>
namespace Graphic
{
class Shader;
enum CreateShaderErrorCode {
	CompileError,
	CannotOpenShaderFile
};
using CreateShaderError = MHTL::error<CreateShaderErrorCode>;
using CreateShaderResult = MHTL::result<Shader, CreateShaderError>;
enum class ShaderType : GLenum
{
	FragmentShader = GL_FRAGMENT_SHADER,
	VertexShader = GL_VERTEX_SHADER
};
class Shader {
private:
	GLuint m_shaderId;
	ShaderType m_shadertype;
	Shader(GLuint i_shaderId, ShaderType i_type);
public:
	static CreateShaderResult CreateShader(std::string i_path, ShaderType i_type);
};
}