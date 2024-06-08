#include "GhostAIComponents.h"
#include "GhostFSM.h"

pacman::BaseAIComponent::BaseAIComponent(amu::GameObject* gameObjectPtr)
	: Component(gameObjectPtr)
{
	m_SpawnPos = gameObjectPtr->GetComponent<amu::TransformComponent>()->GetWorldPosition();
	GetComponentOwner()->AddComponent<amu::DistanceComponent>(gameObjectPtr);
	m_DistancePtr = gameObjectPtr->GetComponent<amu::DistanceComponent>();
	assert(m_DistancePtr);
}

glm::vec2 const& pacman::BaseAIComponent::GetOptimalDirectionToSpawn(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr)
{
	glm::vec2 const& ghostPos{ fsmPtr->GetGhostPosition() };
	float deltaX = m_SpawnPos.x - ghostPos.x;
	float deltaY = m_SpawnPos.y - ghostPos.y;

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
		if (preferredDirection == -fsmPtr->GetPreviousDirection())
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

bool pacman::BaseAIComponent::IsAtSpawnPos(glm::vec2 const& ghostPos)
{
	return m_DistancePtr->Check(m_SpawnPos, ghostPos, 5);
}

pacman::BaseAIComponent::Axis pacman::BaseAIComponent::GetOptimalAxis(float deltaX, float deltaY) const
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

glm::vec2 pacman::BaseAIComponent::GetOptimalHorizontalDirection(float deltaX) const
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

glm::vec2 pacman::BaseAIComponent::GetOptimalVerticalDirection(float deltaY) const
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

pacman::BlinkyAIComponent::BlinkyAIComponent(amu::GameObject* gameObjectPtr)
	: BaseAIComponent(gameObjectPtr)
{
}

glm::vec2 const& pacman::BlinkyAIComponent::GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr)
{
	glm::vec2 const& ghostPos{ fsmPtr->GetGhostPosition() };
	glm::vec2 const& pacmanPos{ fsmPtr->GetPacmanPosition() };
	float deltaX = pacmanPos.x - ghostPos.x;
	float deltaY = pacmanPos.y - ghostPos.y;

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
		if (preferredDirection == -fsmPtr->GetPreviousDirection())
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

glm::vec2 const& pacman::BlinkyAIComponent::GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr)
{
	glm::vec2 const& ghostPos{ fsmPtr->GetGhostPosition() };
	glm::vec2 const& pacmanPos{ fsmPtr->GetPacmanPosition() };
	float deltaX = pacmanPos.x - ghostPos.x;
	float deltaY = pacmanPos.y - ghostPos.y;

	if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
	{
		m_PreferredDirectionVec[0] = (-GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[1] = (-GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[2] = (GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[3] = (GetOptimalHorizontalDirection(deltaX));
	}
	else
	{
		m_PreferredDirectionVec[0] = (-GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[1] = (-GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[2] = (GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[3] = (GetOptimalVerticalDirection(deltaY));
	}
	for (glm::vec2 const& preferredDirection : m_PreferredDirectionVec)
	{
		if (preferredDirection == -fsmPtr->GetPreviousDirection())
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

pacman::InkyPinkyAIComponent::InkyPinkyAIComponent(amu::GameObject* gameObjectPtr, float distanceToCheck)
	: BaseAIComponent(gameObjectPtr)
	, m_DistanceToCheck{ distanceToCheck }
{
}

glm::vec2 const& pacman::InkyPinkyAIComponent::GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr)
{
	glm::vec2 const& ghostPos{ fsmPtr->GetGhostPosition() };
	glm::vec2 const& pacmanPos{ fsmPtr->GetPacmanPosition() };
	glm::vec2 const& pacmanDir{ fsmPtr->GetPacmanDirection() };
	float deltaX = pacmanPos.x + m_DistanceToCheck * pacmanDir.x - ghostPos.x;
	float deltaY = pacmanPos.y + m_DistanceToCheck * pacmanDir.y - ghostPos.y;

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
		if (preferredDirection == -fsmPtr->GetPreviousDirection())
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

glm::vec2 const& pacman::InkyPinkyAIComponent::GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, GhostFSMComponent* fsmPtr)
{
	glm::vec2 const& ghostPos{ fsmPtr->GetGhostPosition() };
	glm::vec2 const& pacmanPos{ fsmPtr->GetPacmanPosition() };
	glm::vec2 const& pacmanDir{ fsmPtr->GetPacmanDirection() };
	float deltaX = pacmanPos.x + pacmanDir.x - ghostPos.x;
	float deltaY = pacmanPos.y + pacmanDir.x - ghostPos.y;

	if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
	{
		m_PreferredDirectionVec[0] = (-GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[1] = (-GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[2] = (GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[3] = (GetOptimalHorizontalDirection(deltaX));
	}
	else
	{
		m_PreferredDirectionVec[0] = (-GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[1] = (-GetOptimalVerticalDirection(deltaY));
		m_PreferredDirectionVec[2] = (GetOptimalHorizontalDirection(deltaX));
		m_PreferredDirectionVec[3] = (GetOptimalVerticalDirection(deltaY));
	}
	for (glm::vec2 const& preferredDirection : m_PreferredDirectionVec)
	{
		if (preferredDirection == -fsmPtr->GetPreviousDirection())
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
