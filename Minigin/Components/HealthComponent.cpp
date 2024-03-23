#include "HealthComponent.h"

amu::HealthComponent::HealthComponent(GameObject* ownerObjectPtr, int health)
	: Component(ownerObjectPtr)
	, m_MaxHealth{ health }
	, m_CurrentHealth{ health }
{
}

void amu::HealthComponent::ReduceHealth(int value)
{
	for (int idx{ 1 }; idx <= value; ++idx)
	{
		if (m_CurrentHealth - 1 < 0) 
		{
			return;
		}
		m_CurrentHealth -= 1;
	}
}

void amu::HealthComponent::IncreaseHealth(int value)
{
	for (int idx{ 1 }; idx <= value; ++idx)
	{
		if (m_CurrentHealth + 1 > m_MaxHealth)
		{
			return;
		}
		m_CurrentHealth += 1;
	}
}
