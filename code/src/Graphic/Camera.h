#pragma once

namespace Graphic
{
	class Camera {
	private:		
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_cacheMatrix;
		glm::vec3 angular_velocity;
		glm::vec3 position;
		bool isCamMatrixDirty = false;
		void calculateCameraMatrix();
	public:
		Camera();
		void rotate(float i_pitch, float i_yaw, float i_roll);
		void translate(glm::vec3 i_dir);
		void setProjectionMatrix(float i_fov, float i_ratio,float i_nearPlane, float i_farPlane);
		void setPosition(glm::vec3 i_pos);
		const glm::mat4& getMatrix();
	};
}