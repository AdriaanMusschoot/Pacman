#include "BlinkyAIComponent.h"

pacman::BlinkyAIComponent::BlinkyAIComponent(amu::GameObject* gameObjectPtr, amu::TransformComponent* pacmanTransformPtr)
	: Component(gameObjectPtr)
	, m_PacmanTransformPtr{ pacmanTransformPtr }
{
    m_TransformPtr = GetComponentOwner()->GetComponent<amu::TransformComponent>();
    m_GridMovementPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
}

void pacman::BlinkyAIComponent::Update()
{
	m_GridMovementPtr->ChangeMovementState(FindPacman());
}

glm::vec2 pacman::BlinkyAIComponent::FindPacman()
{
	auto& pacmanPosition = m_PacmanTransformPtr->GetWorldPosition();
    auto& ghostPosition = m_TransformPtr->GetWorldPosition();
    float deltaX = pacmanPosition.x - ghostPosition.x;
    float deltaY = pacmanPosition.y - ghostPosition.y;

    if (std::abs(deltaX) > std::abs(deltaY)) 
    {
        if (deltaX > 0) 
        {
            return glm::vec2{ 1, 0 };
        }
        else 
        {
            return glm::vec2{ -1, 0 };
        }
    }
    else
    {
        if (deltaY > 0) 
        {
            return glm::vec2{ 0, 1 };
        }
        else 
        {
            return glm::vec2{ 0, -1 };
        }
    }
}
