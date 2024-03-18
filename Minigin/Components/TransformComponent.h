#pragma once
#include <glm/glm.hpp>

#include "Base/Component.h"

namespace amu
{
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(GameObject * ownerObjectPtr, const glm::vec2& pos);

		const glm::vec2& GetLocalPosition() const;
		void SetLocalPosition(const glm::vec2& newPosition);
		const glm::vec2& GetWorldPosition() const;
		void Translate(const glm::vec2& offset);
		void SetTransformDirty();
	private:
		glm::vec2 m_LocalPosition{ 0, 0 };
		glm::vec2 m_WorldPosition{ 0, 0 };

		bool m_TransformDirty;

		void UpdateWorldPosition();
	};
}