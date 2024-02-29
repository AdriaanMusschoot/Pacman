#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(const std::shared_ptr<GameObject>& parentObjectSPtr, const glm::vec3& pos = { 0, 0, 0 });

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_position;
	};
}