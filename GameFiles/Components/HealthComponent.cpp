#include "HealthComponent.h"

amu::HealthComponent::HealthComponent(GameObject* ownerObjectPtr, int health, int lives)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
	, m_MaxHealth{ health }
	, m_CurrentHealth{ health }
	, m_MaxLives{ lives }
	, m_CurrentLives{ lives }
{
}

void amu::HealthComponent::ReduceHealth(int value)
{
	m_CurrentHealth -= value;
	if (m_CurrentHealth <= 0)
	{
		m_CurrentLives -= 1;
		if (m_CurrentLives <= 0)
		{
			m_CurrentLives = 0;
		}
		m_CurrentHealth = m_MaxHealth;
		NotifyObservers(Observer::EventType::PacmanDied);
	}
}

void amu::HealthComponent::IncreaseHealth(int value)
{
	m_CurrentHealth += value;
	if (m_CurrentHealth >= m_MaxHealth)
	{
		m_CurrentHealth = m_MaxHealth;
	}
}
