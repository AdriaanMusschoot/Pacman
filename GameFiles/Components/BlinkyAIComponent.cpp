#include "BlinkyAIComponent.h"
#include "GridMovementComponent.h"

pacman::BlinkyAIComponent::BlinkyAIComponent(amu::GameObject* gameObjectPtr, amu::TransformComponent* pacmanTransformPtr)
	: Component(gameObjectPtr)
	, m_PacmanTransformPtr{ pacmanTransformPtr }
{
    m_TransformPtr = GetComponentOwner()->GetComponent<amu::TransformComponent>();
    m_GridMovementPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
    m_GridMovementPtr->ChangeMovementState(glm::vec2{ 1, 0 });
}

void pacman::BlinkyAIComponent::Notify(Event eventType, amu::Subject*)
{
    if (eventType == pacman::events::GHOST_INPUT_REQUIRED)
    {
        glm::vec2 const optimalDirection{ GetOptimalDirectionToPacman(m_GridMovementPtr->PossibleDirections()) };
        m_GridMovementPtr->ChangeMovementState(optimalDirection);
        m_PreviousDirection = optimalDirection;
    }
}

glm::vec2 pacman::BlinkyAIComponent::GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections) const
{
	auto& pacmanPosition = m_PacmanTransformPtr->GetWorldPosition();
    auto& ghostPosition = m_TransformPtr->GetWorldPosition();
    float deltaX = pacmanPosition.x - ghostPosition.x;
    float deltaY = pacmanPosition.y - ghostPosition.y;

    std::vector<glm::vec2> preferredDirectionVec{};
    if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
    {
        preferredDirectionVec.emplace_back(GetOptimalHorizontalDirection(deltaX));
        preferredDirectionVec.emplace_back(GetOptimalVerticalDirection(deltaY));
        preferredDirectionVec.emplace_back(-GetOptimalHorizontalDirection(deltaX));
        preferredDirectionVec.emplace_back(-GetOptimalVerticalDirection(deltaY));
    }
    else
    {
        preferredDirectionVec.emplace_back(GetOptimalVerticalDirection(deltaY));
        preferredDirectionVec.emplace_back(GetOptimalHorizontalDirection(deltaX));
        preferredDirectionVec.emplace_back(-GetOptimalVerticalDirection(deltaY));
        preferredDirectionVec.emplace_back(-GetOptimalHorizontalDirection(deltaX));
    }
    for (glm::vec2 const& preferredDirection : preferredDirectionVec)
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
    return glm::vec2{ -1, -1 };
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
    glm::vec2 left{ -1, 0 };
    glm::vec2 right{ 1, 0 };

    if (deltaX > 0)
    {
        return right;
    }
    else 
    {
        return left;
    }
}

glm::vec2 pacman::BlinkyAIComponent::GetOptimalVerticalDirection(float deltaY) const
{
    glm::vec2 up{ 0, -1 };
    glm::vec2 down{ 0, 1 };
    if (deltaY > 0)
    {
        return down;
    }
    else
    {
        return up;
    }
}
