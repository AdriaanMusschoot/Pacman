#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(const std::shared_ptr<GameObject>& ownerObjectSPtr, const glm::vec3& pos = { 0, 0, 0 });

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& newPosition);
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetWorldPosition(float x, float y, float z);
		void SetWorldPosition(const glm::vec3& newPosition);
	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
	};
}