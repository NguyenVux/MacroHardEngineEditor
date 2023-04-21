#include "Transform.h"
#include "glm/gtx/quaternion.hpp"

namespace Graphic {
	void TransformComponent::UpdateAxis()
	{
		glm::mat4 rotMat = glm::toMat4(glm::quat(glm::radians(m_rotation)));
		m_front.x = rotMat[0][2];
		m_front.y = rotMat[1][2];
		m_front.z = rotMat[2][2];

		m_up.x = rotMat[0][1];
		m_up.y = rotMat[1][1];
		m_up.z = rotMat[2][1];

		m_right.x = rotMat[0][0];
		m_right.y = rotMat[1][0];
		m_right.z = rotMat[2][0];
	}
	TransformComponent::TransformComponent():
		m_rotation(0.0f),
		m_position(0.0f),
		m_front(0.0f),
		m_right(0.0f),
		m_up(0.0f)
	{

	}
	void TransformComponent::Translate(glm::vec3 i_direction, TransformMode i_mode)
	{

		if (i_mode == TransformMode::GLOBAL_COORD)
		{
			m_position += i_direction;
			return;
		}

		m_position += m_front * i_direction.z;
		m_position += m_up * i_direction.y;
		m_position += m_right * i_direction.x;
	
	}
	void TransformComponent::Rotate(glm::vec3 i_rot, TransformMode i_mode = TransformMode::GLOBAL_COORD)
	{
		m_rotation += i_rot;
		UpdateAxis();
	}
	void TransformComponent::SetPosition(glm::vec3 i_direction)
	{
		m_position = i_direction;
	}
	void TransformComponent::SetRotation(glm::vec3 i_rot)
	{
		m_rotation = i_rot;
		UpdateAxis();
	}
	const glm::vec3& TransformComponent::GetPosition() const
	{
		return m_position;
	}
	const glm::vec3& TransformComponent::GetRotation() const
	{
		return m_rotation;
	}
	glm::mat3 TransformComponent::GetAxis() const
	{
		glm::mat3 m(1.0f);
		m[0][0] = m_right.x; // First column, first row
		m[1][0] = m_right.y;
		m[2][0] = m_right.z;
		m[0][1] = m_up.x; // First column, second row
		m[1][1] = m_up.y;
		m[2][1] = m_up.z;
		m[0][2] = m_front.x; // First column, third row
		m[1][2] = m_front.y;
		m[2][2] = m_front.z;
		return m;
		/*return glm::mat3(
			m_right, 
			m_up, 
			m_front);*/
	}
}