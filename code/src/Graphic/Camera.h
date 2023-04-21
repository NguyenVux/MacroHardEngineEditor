#pragma once
#include "Transform.h"
namespace Graphic
{
	class Camera {
	private:		
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_cacheMatrix;
		TransformComponent m_transform;
		bool isCamMatrixDirty = false;
		void calculateCameraMatrix();
	public:
		Camera();
		void rotate(glm::vec3 i_rot);
		void translate(glm::vec3 i_dir);
		void setProjectionMatrix(float i_fov, float i_ratio,float i_nearPlane, float i_farPlane);
		void setPosition(glm::vec3 i_pos);
		void setRotation(glm::vec3 i_rot);
		const glm::mat4& getMatrix();
	};
}