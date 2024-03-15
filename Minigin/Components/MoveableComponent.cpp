#include "MoveableComponent.h"
#include "Singletons/Time.h"

amu::MoveableComponent::MoveableComponent(GameObject* ownerObjectPtr, int speed)
	: Component(ownerObjectPtr)
	, m_TransformPtr{ GetOwnerGameObject()->GetComponent<TransformComponent>() }
	, m_Speed{ speed }
{
}

void amu::MoveableComponent::MoveRight()
{
	if (m_TransformPtr)
	{
		const glm::vec3 directionUpdate{ m_Speed * GameTime::GetInstance().GetDeltaTime(), 0, 0 };
		const glm::vec3 newPostion{ m_TransformPtr->GetLocalPosition() + directionUpdate };
		m_TransformPtr->SetLocalPosition(newPostion);
	}
}

void amu::MoveableComponent::MoveLeft()
{
	if (m_TransformPtr)
	{
		const glm::vec3 directionUpdate{ -m_Speed * GameTime::GetInstance().GetDeltaTime(), 0, 0 };
		const glm::vec3 newPostion{ m_TransformPtr->GetLocalPosition() + directionUpdate };
		m_TransformPtr->SetLocalPosition(newPostion);
	}
}

void amu::MoveableComponent::MoveUp()
{
	if (m_TransformPtr)
	{
		const glm::vec3 directionUpdate{ 0, -m_Speed * GameTime::GetInstance().GetDeltaTime(), 0 };
		const glm::vec3 newPostion{ m_TransformPtr->GetLocalPosition() + directionUpdate };
		m_TransformPtr->SetLocalPosition(newPostion);
	}
}

void amu::MoveableComponent::MoveDown()
{
	if (m_TransformPtr)
	{
		const glm::vec3 directionUpdate{ 0, m_Speed * GameTime::GetInstance().GetDeltaTime(), 0 };
		const glm::vec3 newPostion{ m_TransformPtr->GetLocalPosition() + directionUpdate };
		m_TransformPtr->SetLocalPosition(newPostion);
	}
}
