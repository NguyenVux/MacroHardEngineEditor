#include "Gizmo.h"
#include "Camera.h"

namespace Graphic {
	Gizmo::Gizmo(std::shared_ptr<Camera> i_cam) : GizmoVAO(0),
		lines({
			0,1,
			}),
			m_identity(1.0f),
			m_mainCam(i_cam)
	{
		{
			auto v = Graphic::Shader::CreateShader("../../../../data/gizmoVert.glsl", Graphic::ShaderType::VertexShader);
			auto s = Graphic::Shader::CreateShader("../../../../data/gizmoFrag.glsl", Graphic::ShaderType::FragmentShader);
			if (v != MHTL::success)
			{
				LOG_ERROR(v.error().what(), "GLFWApplication");
				return;
			}
			if (s != MHTL::success)
			{
				LOG_ERROR(s.error().what(), "GLFWApplication");
				return;
			}
			m_gizmoShaderProgram.AttachShader(v.extract_payload());
			m_gizmoShaderProgram.AttachShader(s.extract_payload());
			auto r = m_gizmoShaderProgram.LinkProgram();
			if (r != MHTL::success)
			{
				LOG_ERROR(r.error().what(), "GLFWApplication");
				return;
			}
		}


		{
			auto v = Graphic::Shader::CreateShader("../../../../data/gridVert.glsl", Graphic::ShaderType::VertexShader);
			auto s = Graphic::Shader::CreateShader("../../../../data/gridFrag.glsl", Graphic::ShaderType::FragmentShader);
			if (v != MHTL::success)
			{
				LOG_ERROR(v.error().what(), "GLFWApplication");
				return;
			}
			if (s != MHTL::success)
			{
				LOG_ERROR(s.error().what(), "GLFWApplication");
				return;
			}
			m_gridShaderProgram.AttachShader(v.extract_payload());
			m_gridShaderProgram.AttachShader(s.extract_payload());
			auto r = m_gridShaderProgram.LinkProgram();
			if (r != MHTL::success)
			{
				LOG_ERROR(r.error().what(), "GLFWApplication");
				return;
			}
		}
		std::array<GLfloat, 2> gizmo = {
			0.0f,20.0f
		};



		GLuint GizmoVBO;
		GLuint GizmoEBO;
		glGenVertexArrays(1, &GizmoVAO);
		glBindVertexArray(GizmoVAO);
		glGenBuffers(1, &GizmoVBO);
		glBindBuffer(GL_ARRAY_BUFFER, GizmoVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(gizmo), gizmo.data(), GL_STATIC_DRAW);

		m_gizmoShaderProgram.Use();
		glVertexAttribPointer(0,1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		m_gridShaderProgram.Use();
		glVertexAttribPointer(0,1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	void Gizmo::Draw() {
		m_gizmoShaderProgram.Use();
		glBindVertexArray(GizmoVAO);
		GLint prjPos = m_gizmoShaderProgram.GetUniformLocation("projectionMatrix");
		GLint axisPos = m_gizmoShaderProgram.GetUniformLocation("axis");
		glUniformMatrix4fv(prjPos, 1, GL_FALSE, glm::value_ptr(m_mainCam->getMatrix()));
		glUniform4fv(axisPos, 3, glm::value_ptr(m_identity));
		glDrawArraysInstanced(GL_LINES, 0, 2, 3);

		m_gridShaderProgram.Use();
		prjPos = m_gridShaderProgram.GetUniformLocation("projectionMatrix");
		glUniformMatrix4fv(prjPos, 1, GL_FALSE, glm::value_ptr(m_mainCam->getMatrix()));
		glDrawArraysInstanced(GL_LINES, 0, 2, 22);
	}
}