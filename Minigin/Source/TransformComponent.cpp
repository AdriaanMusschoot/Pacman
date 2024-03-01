#include "Header/GameObject.h"
#include "Header/TransformComponent.h"

dae::TransformComponent::TransformComponent(const std::shared_ptr<GameObject>& ownerObjectSPtr, const glm::vec3& pos)
	: Component(ownerObjectSPtr)
	, m_LocalPosition{ pos }
	, m_WorldPosition{ }
{
}

void dae::TransformComponent::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& newPosition)
{
	m_LocalPosition = newPosition;
}

void dae::TransformComponent::SetWorldPosition(const float x, const float y, const float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void dae::TransformComponent::SetWorldPosition(const glm::vec3& newPosition)
{
	m_WorldPosition = newPosition;
}
