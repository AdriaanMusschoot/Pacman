#include "ScoreComponent.h"

pacman::ScoreComponent::ScoreComponent(amu::GameObject* ownerObjectPtr)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
{
	m_ScoreTextPtr = GetComponentOwner()->GetComponent<amu::TextComponent>();
}

void pacman::ScoreComponent::OnNotify(Event eventType, amu::Subject*)
{
	if (eventType == events::PACMAN_EAT_SMALL_PICKUP)
	{
		++m_NumberOfPickups;
		m_Score += m_SmallPickupScore;
		std::cout << m_NumberOfPickups << "\n";
	}
	else if (eventType == events::PACMAN_EAT_BIG_PICKUP)
	{
		++m_NumberOfPickups;
		m_Score += m_BigPickupScore;
	}
	else if (eventType == events::PACMAN_EAT_GHOST)
	{
		++m_GhostsEaten;
		m_Score += m_CurrentGhostScoreValue;
		m_CurrentGhostScoreValue *= 2;
		if (m_GhostsEaten >= 4)
		{
			m_CurrentGhostScoreValue = m_GhostScoreBaseValue;
		}
	}
	else if (eventType == events::PACMAN_COLLECT)
	{
		m_CurrentGhostScoreValue = m_GhostScoreBaseValue;
		m_GhostsEaten = 0;
	}
	if (m_NumberOfPickups >= m_PickupsPerLevel)
	{
		m_NumberOfPickups = 0;
		NotifyObservers(events::PACMAN_ATE_ALL);
	}
	if (eventType == events::PACMAN_DYING_ANIM_FINISHED)
	{
		m_NumberOfPickups = 0;
	}
	m_ScoreTextPtr->SetText(std::to_string(m_Score));
}