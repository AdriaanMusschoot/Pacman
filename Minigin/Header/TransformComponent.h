#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace amu
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject * ownerObjectSPtr, const glm::vec3& pos = { 0, 0, 0 });

		const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(const glm::vec3& newPosition);
		const glm::vec3& GetWorldPosition() const;

		void SetTransformDirty();
	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;

		bool m_TransformDirty;

		void UpdateWorldPosition();
	};
}