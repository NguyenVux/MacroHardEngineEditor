#pragma once

namespace Graphic {
	class TransformComponent {
	public:
		enum class TransformMode {
			LOCAL_COORD,
			GLOBAL_COORD
		};
	private:
		glm::vec3 m_rotation;
		glm::quat m_quatRotation;

		glm::vec3 m_position;

		glm::vec3 m_front;
		glm::vec3 m_right;
		glm::vec3 m_up;
		void UpdateAxis();
	public:
		TransformComponent();
		void Translate(glm::vec3 i_direction, TransformMode i_mode);
		void SetPosition(glm::vec3 i_direction);
		void SetBaseAxis(glm::mat4 i_axis) const;
		void Rotate(glm::vec3 i_rot, TransformMode i_mode);
		void SetRotation(glm::vec3 i_rot);
		const glm::vec3& GetPosition() const;
		const glm::vec3& GetRotation() const;
		const glm::vec3& GetFront() const;
		glm::mat4 GetRotationMatrix() const;
	};
}