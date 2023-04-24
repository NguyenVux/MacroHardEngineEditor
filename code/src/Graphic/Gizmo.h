#pragma once
#include "IDrawable.h"
#include "ShaderProgram.h"
namespace Graphic {

	class Camera;
	class Gizmo : public IDrawable {
	private:
		Graphic::ShaderProgram m_gizmoShaderProgram;
		Graphic::ShaderProgram m_gridShaderProgram;
		GLuint GizmoVAO;
		std::array<GLuint, 2> lines;
		std::vector<GLuint> gridIndices;
		std::shared_ptr<Camera> m_mainCam;
		glm::mat4 m_identity;
	public:
		Gizmo(std::shared_ptr<Camera> i_cam);
		void Draw() override;
	};
}