#include "BlinkyAIComponent.h"

pacman::BaseAIComponent::BaseAIComponent(amu::GameObject* gameObjectPtr)
	: Component(gameObjectPtr)
{
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

glm::vec2 const& pacman::BlinkyAIComponent::GetOptimalDirectionToPacman(std::vector<glm::vec2> const& possibleDirections, glm::vec2 const& pacmanPos, glm::vec2 const& ghostPos, glm::vec2 const& previousDirection)
{
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
		if (preferredDirection == -previousDirection)
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

glm::vec2 const& pacman::BlinkyAIComponent::GetOptimalDirectionFromPacman(std::vector<glm::vec2> const& possibleDirections, glm::vec2 const& pacmanPos, glm::vec2 const& ghostPos, glm::vec2 const& previousDirection)
{
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
		if (preferredDirection == -previousDirection)
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