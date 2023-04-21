#include "Gizmo.h"
#include "Camera.h"

namespace Graphic {
	Gizmo::Gizmo(std::shared_ptr<Camera> i_cam): GizmoVAO(0),
		lines({
			0,1,
			0,2,
			0,3
		}),
		m_mainCam(i_cam)
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
		std::array<glm::vec3, 4> gizmo = {
			glm::vec3(0.0f,0.0f, 0.0f), // Vertex 0
			glm::vec3(10.0f,0.0f, 0.0f), // Vertex 0
			glm::vec3(0.0f,10.0f, 0.0f), // Vertex 0
			glm::vec3(0.0f,0.0f, 10.0f), // Vertex 0
		};

		GLuint GizmoVBO;
		GLuint GizmoEBO;
		glGenVertexArrays(1, &GizmoVAO);
		glBindVertexArray(GizmoVAO);
		glGenBuffers(1, &GizmoVBO);
		glBindBuffer(GL_ARRAY_BUFFER, GizmoVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(gizmo), gizmo.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &GizmoEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GizmoEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lines), lines.data(), GL_STATIC_DRAW);

		m_gizmoShaderProgram.Use();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	void Gizmo::Draw() {
		m_gizmoShaderProgram.Use();
		glBindVertexArray(GizmoVAO);
		glBindVertexArray(GizmoVAO);
		GLint prjPos = m_gizmoShaderProgram.GetUniformLocation("projectionMatrix");
		GLint colorPos = m_gizmoShaderProgram.GetUniformLocation("uvert_c");
		glUniformMatrix4fv(prjPos, 1, GL_FALSE, glm::value_ptr(m_mainCam->getMatrix()));

		int pos = 0;
		glUniform4fv(colorPos, 1, glm::value_ptr(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
		pos += 2;
		glUniform4fv(colorPos, 1, glm::value_ptr(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, reinterpret_cast<void*>(2 * sizeof(GLuint)));
		pos += 2;
		glUniform4fv(colorPos, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, reinterpret_cast<void*>(4 * sizeof(GLuint)));
	}
}