#pragma once
#include "IDrawable.h"
#include "ShaderProgram.h"
namespace Graphic {

	class Camera;
	class Gizmo : public IDrawable {
	private:
		Graphic::ShaderProgram m_gizmoShaderProgram;
		GLuint GizmoVAO;
		std::array<GLuint, 2 * 3> lines;
		std::shared_ptr<Camera> m_mainCam;
	public:
		Gizmo(std::shared_ptr<Camera> i_cam);
		void Draw() override;
	};
}