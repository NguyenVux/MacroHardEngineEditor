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
		m_transform.Rotate(glm::vec3(i_dir.x,i_dir.y,0.0f), TransformComponent::TransformMode::GLOBAL_COORD);
		//m_transform.Rotate(glm::vec3(, 0.0f, 0.0f), TransformComponent::TransformMode::LOCAL_COORD);
	}
	void Camera::translate(glm::vec3 i_dir)
	{
		isCamMatrixDirty = true;
		////i_dir.x *= -1;
		//glm::vec3 front = glm::normalize(m_transform.GetFront());
		//glm::vec3 right = glm::normalize(glm::cross(front,glm::vec3(0.0f,1.0f,0.0f)));
		//glm::vec3 position = m_transform.GetPosition();
		//position += i_dir * glm::quat(m_transform.GetRotation());
		//m_transform.SetPosition(position);
		i_dir.z *= -1;
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
		glm::vec3 position = m_transform.GetPosition();
		glm::vec3 direction = m_transform.GetFront();/*
		glm::vec3 rotation = m_transform.GetRotation();
		direction.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		direction.y = sin(glm::radians(rotation.x));
		direction.z = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));*/

		//glm::mat4 view_mat = glm::lookAt(position, position + direction,glm::vec3(0.0f,1.0f,0.0f));
		glm::mat4 view_mat =  glm::translate(glm::mat4(1.0f),m_transform.GetPosition())* m_transform.GetRotationMatrix();
		m_cacheMatrix = m_projectionMatrix * glm::inverse(view_mat);
		isCamMatrixDirty = false;
	}

	void Camera::setProjectionMatrix(float i_fov, float i_ratio, float i_nearPlane, float i_farPlane)
	{
		isCamMatrixDirty = true;
		m_projectionMatrix = glm::perspective(i_fov, i_ratio, i_nearPlane, i_farPlane);
		//m_projectionMatrix = glm::ortho(0.f, 400.f, 0.f, 400.f, -1.f, 1.f);
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