#include "BlinkyAIComponent.h"
#include "GridMovementComponent.h"

pacman::BlinkyAIComponent::BlinkyAIComponent(amu::GameObject* gameObjectPtr, amu::TransformComponent* pacmanTransformPtr)
	: Component(gameObjectPtr)
	, m_PacmanTransformPtr{ pacmanTransformPtr }
{
    m_TransformPtr = GetComponentOwner()->GetComponent<amu::TransformComponent>();
    m_GridMovementPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
    m_GridMovementPtr->ChangeMovementState(config::VEC_LEFT);
}

void pacman::BlinkyAIComponent::Notify(Event eventType, amu::Subject*)
{
    if (eventType == pacman::events::GHOST_INPUT_REQUIRED)
    {
        std::vector<glm::vec2> possibleDirectionVec{ m_GridMovementPtr->PossibleDirections() };
        glm::vec2 const& optimalDirection{ GetOptimalDirectionToPacman(possibleDirectionVec) };
        if (optimalDirection != config::VEC_INVALID)
        {
            m_GridMovementPtr->ChangeMovementState(optimalDirection);
            m_PreviousDirection = optimalDirection;
        }
        else
        {
            auto& safetyDirection = possibleDirectionVec[0];
            m_GridMovementPtr->ChangeMovementState(safetyDirection);
            m_PreviousDirection = safetyDirection;
        }
    }
}

glm::vec2 const& pacman::BlinkyAIComponent::GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections)
{
	auto& pacmanPosition = m_PacmanTransformPtr->GetWorldPosition();
    auto& ghostPosition = m_TransformPtr->GetWorldPosition();
    float deltaX = pacmanPosition.x - ghostPosition.x;
    float deltaY = pacmanPosition.y - ghostPosition.y;

    if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
    {
        m_PreferredDirectionVec[0] = (GetOptimalHorizontalDirection(deltaX));
        m_PreferredDirectionVec[1] = (GetOptimalVerticalDirection(deltaY));
        m_PreferredDirectionVec[2] = (-GetOptimalHorizontalDirection(deltaX));
        m_PreferredDirectionVec[3] = (-GetOptimalVerticalDirection(deltaY));
    }   
    else
    {
        m_PreferredDirectionVec[0] = (GetOptimalVerticalDirection(deltaY));
        m_PreferredDirectionVec[1] = (GetOptimalHorizontalDirection(deltaX));
        m_PreferredDirectionVec[2] = (-GetOptimalVerticalDirection(deltaY));
        m_PreferredDirectionVec[3] = (-GetOptimalHorizontalDirection(deltaX));
    }
    for (glm::vec2 const& preferredDirection : m_PreferredDirectionVec)
    {
        if (preferredDirection == -m_PreviousDirection)
        {
            continue;
        }
        if (std::any_of(possibleDirections.begin(), possibleDirections.end(),
                        [&](glm::vec2 const& possibleDirection) 
                        { 
                            return possibleDirection == preferredDirection; 
                        }))
        {
            return preferredDirection;
        }
    }
    return config::VEC_INVALID;
}

pacman::BlinkyAIComponent::Axis pacman::BlinkyAIComponent::GetOptimalAxis(float deltaX, float deltaY) const
{
    if (std::abs(deltaX) > std::abs(deltaY)) 
    {
        return Axis::X;   
    }
    else 
    {
        return Axis::Y;
    }
}

glm::vec2 pacman::BlinkyAIComponent::GetOptimalHorizontalDirection(float deltaX) const
{
    if (deltaX > 0)
    {
        return config::VEC_RIGHT;
    }
    else 
    {
        return config::VEC_LEFT;
    }
}

glm::vec2 pacman::BlinkyAIComponent::GetOptimalVerticalDirection(float deltaY) const
{
    if (deltaY > 0)
    {
        return config::VEC_DOWN;
    }
    else
    {
        return config::VEC_UP;
    }
}
