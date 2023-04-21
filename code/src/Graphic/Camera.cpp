#include "Camera.h"
#include "glm/gtx/quaternion.hpp"

namespace Graphic
{
	Camera::Camera() : m_cacheMatrix(0.0f), m_projectionMatrix(0.0f)
	{
	}
	void Camera::rotate(glm::vec3 i_dir)
	{
		isCamMatrixDirty = true;
		m_transform.Rotate(-i_dir, TransformComponent::TransformMode::GLOBAL_COORD);
	}
	void Camera::translate(glm::vec3 i_dir)
	{
		isCamMatrixDirty = true;
		i_dir.z = -i_dir.z;
		m_transform.Translate(i_dir, TransformComponent::TransformMode::LOCAL_COORD);
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
		glm::mat4 aview_matrix = glm::mat4(m_transform.GetAxis());
		m_cacheMatrix = m_projectionMatrix* aview_matrix*glm::translate(glm::mat4(1.0f),-m_transform.GetPosition());
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
		m_transform.SetPosition(i_pos);
	}

	void Camera::setRotation(glm::vec3 i_rot)
	{
		isCamMatrixDirty = true;
		m_transform.SetRotation(i_rot);
	}
}