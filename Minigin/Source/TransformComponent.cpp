#include "Header/GameObject.h"
#include "Header/TransformComponent.h"

dae::TransformComponent::TransformComponent(const std::shared_ptr<GameObject>& parentObjectSPtr, const glm::vec3& pos)
	: Component(parentObjectSPtr)
	, m_position{ pos }
{

}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
