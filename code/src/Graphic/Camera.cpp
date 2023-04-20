#include "Camera.h"
#include "glm/gtx/quaternion.hpp"

namespace Graphic
{
	Camera::Camera() : position(glm::zero<glm::vec3>()), angular_velocity(glm::zero<glm::vec3>())
	{
	}
	void Camera::rotate(float i_pitch, float i_yaw, float i_roll)
	{
		isCamMatrixDirty = true;
		angular_velocity.x += i_pitch;
		angular_velocity.y += i_yaw;
		angular_velocity.z += i_roll;
	}
	void Camera::translate(glm::vec3 i_dir)
	{
		isCamMatrixDirty = true;
		position += i_dir;
	}
	const glm::mat4& Camera::getMatrix()
	{
		calculateCameraMatrix();
		return m_cacheMatrix;
	}

	void Camera::calculateCameraMatrix() {
		if (!isCamMatrixDirty && glm::length2(angular_velocity) > 0.0001f)
		{
			return;
		}
		auto rot = glm::toMat4(glm::qua<float>(angular_velocity));
		auto translate = glm::translate(glm::mat4(1.0f), position);
		m_cacheMatrix = m_projectionMatrix * translate *rot;
		isCamMatrixDirty = false;
	}

	void Camera::setProjectionMatrix(float i_fov, float i_ratio, float i_nearPlane, float i_farPlane)
	{
		isCamMatrixDirty = true;
		m_projectionMatrix = glm::perspective(i_fov, i_ratio, i_nearPlane, i_farPlane);
	}
	void Camera::setPosition(glm::vec3 i_pos)
	{
		isCamMatrixDirty = true;
		position = i_pos;
	}
}