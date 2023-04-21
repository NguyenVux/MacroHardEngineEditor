#include "Camera.h"
#include "glm/gtx/quaternion.hpp"

namespace Graphic
{
	Camera::Camera() : position(glm::zero<glm::vec3>()), rotation(glm::zero<glm::vec3>()), m_cacheMatrix(0.0f), m_projectionMatrix(0.0f)
	{
	}
	void Camera::rotate(glm::vec3 i_dir)
	{
		isCamMatrixDirty = true;
		rotation += i_dir;
	}
	void Camera::translate(glm::vec3 i_dir)
	{
		isCamMatrixDirty = true;
		position -= i_dir;
	}
	const glm::mat4& Camera::getMatrix()
	{
		calculateCameraMatrix();
		return m_cacheMatrix;
	}

	void Camera::calculateCameraMatrix() {
		if (!isCamMatrixDirty)
		{
			return;
		}
		glm::vec3 direction;
		direction.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		direction.y = sin(glm::radians(rotation.x));
		direction.z = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));

		glm::mat4 view_matrix = glm::lookAt(position,position+direction ,glm::vec3(0.0f, 1.0f, 0.0f));
		m_cacheMatrix = m_projectionMatrix*view_matrix;
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

	void Camera::setRotation(glm::vec3 i_rot)
	{
		isCamMatrixDirty = true;
		rotation = i_rot;
	}
	void Camera::LookAt(glm::vec3 i_pos)
	{
		isCamMatrixDirty = true;
		glm::vec3 direction = glm::normalize(i_pos - position);

		rotation.x = asin(direction.y);
		rotation.y = asin(direction.x / cos(rotation.x));
		rotation.z = 0.0f;

		rotation = glm::degrees(rotation);
	}
}