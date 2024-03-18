#include "Base/GameObject.h"
#include "Components/TransformComponent.h"

amu::TransformComponent::TransformComponent(GameObject* ownerObjectPtr, const glm::vec2& pos)
	: Component(ownerObjectPtr)
	, m_LocalPosition{ pos }
	, m_WorldPosition{ pos }
	, m_TransformDirty{ false }
{
}

const glm::vec2& amu::TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

void amu::TransformComponent::SetLocalPosition(const glm::vec2& newPosition)
{
	m_LocalPosition = newPosition;

    SetTransformDirty();
}

const glm::vec2& amu::TransformComponent::GetWorldPosition() const
{
    if (m_TransformDirty)
    {
        const_cast<TransformComponent*>(this)->UpdateWorldPosition();
    }
	return m_WorldPosition;
}

void amu::TransformComponent::Translate(const glm::vec2& offset)
{
    SetLocalPosition(GetLocalPosition() + offset);
}

void amu::TransformComponent::UpdateWorldPosition()
{
	if (const GameObject* parentPtr = GetOwnerGameObject()->GetParent(); parentPtr == nullptr)
    {
        m_WorldPosition = m_LocalPosition;
    }
    else
    {
        m_WorldPosition = parentPtr->GetComponent<TransformComponent>()->GetWorldPosition() + m_LocalPosition;
    }
    m_TransformDirty = true;
}

void amu::TransformComponent::SetTransformDirty()
{
    m_TransformDirty = true;
    const GameObject* ownerPtr = GetOwnerGameObject();

    for(size_t idx{}; idx < ownerPtr->GetChildCount(); ++idx)
    {
        ownerPtr->GetChildAt(static_cast<unsigned int>(idx))->GetComponent<TransformComponent>()->SetTransformDirty();
    }
}
