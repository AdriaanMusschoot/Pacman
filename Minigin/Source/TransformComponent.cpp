#include "Header/GameObject.h"
#include "Header/TransformComponent.h"

dae::TransformComponent::TransformComponent(const std::shared_ptr<GameObject>& ownerObjectSPtr, const glm::vec3& pos)
	: Component(ownerObjectSPtr)
	, m_Position{ pos }
{

}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
