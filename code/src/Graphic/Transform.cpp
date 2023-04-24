#include "Transform.h"
#include "glm/gtx/quaternion.hpp"

namespace Graphic {
	void TransformComponent::UpdateAxis()
	{
		m_quatRotation = glm::quat(glm::radians(m_rotation));
		m_right = glm::vec3(1.0f, 0.0f, 0.0f) * m_quatRotation;
		m_up = glm::vec3(0.0f, 1.0f, 0.0f) * m_quatRotation;
		m_front = glm::vec3(0.0f, 0.0f, 1.0f) * m_quatRotation;
		
	}
	TransformComponent::TransformComponent():
		m_rotation(0.0f),
		m_position(0.0f),
		m_front(0.0f),
		m_right(0.0f),
		m_up(0.0f),
		m_quatRotation(m_rotation)
	{

	}
	void TransformComponent::Translate(glm::vec3 i_direction, TransformMode i_mode)
	{

		if (i_mode == TransformMode::GLOBAL_COORD)
		{
			m_position += i_direction;
			return;
		}

		m_position +=  m_quatRotation*i_direction;
	
	}
	void TransformComponent::Rotate(glm::vec3 i_rot, TransformMode i_mode)
	{
		if (i_mode == TransformMode::GLOBAL_COORD)
		{
			m_rotation += i_rot;
			UpdateAxis();
			return;
		}
		glm::quat r(glm::radians(i_rot));
		m_rotation = glm::degrees(glm::eulerAngles(m_quatRotation * r));
		UpdateAxis();
	}
	void TransformComponent::SetPosition(glm::vec3 i_direction)
	{
		m_position = i_direction;
	}
	void TransformComponent::SetBaseAxis(glm::mat4 i_axis) const
	{
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
	const glm::vec3& TransformComponent::GetFront() const
	{
		return m_front;
	}
	glm::mat4 TransformComponent::GetRotationMatrix() const
	{
		return glm::toMat4(m_quatRotation);
	}
}