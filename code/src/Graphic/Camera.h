#pragma once

namespace Graphic
{
	class Camera {
	private:		
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_cacheMatrix;

		glm::vec3 rotation;
		glm::vec3 position;
		bool isCamMatrixDirty = false;
		void calculateCameraMatrix();
	public:
		Camera();
		void rotate(glm::vec3 i_rot);
		void translate(glm::vec3 i_dir);
		void LookAt(glm::vec3 i_dir);
		void setProjectionMatrix(float i_fov, float i_ratio,float i_nearPlane, float i_farPlane);
		void setPosition(glm::vec3 i_pos);
		void setRotation(glm::vec3 i_rot);
		const glm::mat4& getMatrix();
	};
}