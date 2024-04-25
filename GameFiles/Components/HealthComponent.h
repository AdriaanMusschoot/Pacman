#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Subject.h"

namespace amu
{

	class HealthComponent final : public Component, public Subject
	{
	public:
		explicit HealthComponent(GameObject * ownerObjectPtr, int health, int lives);
		virtual ~HealthComponent() override = default;

		HealthComponent(const HealthComponent&) = delete;
		HealthComponent& operator= (const HealthComponent&) = delete;
		HealthComponent(HealthComponent&&) = delete;
		HealthComponent& operator= (const HealthComponent&&) = delete;

		void ReduceHealth(int value);
		void IncreaseHealth(int value);

		int GetHealth() const
		{
			return m_CurrentHealth;
		}

		int GetLives() const
		{
			return m_CurrentLives;
		}

	private:
		const int m_MaxHealth{ 2 };
		int m_CurrentHealth{ 2 };

		const int m_MaxLives{ 3 };
		int m_CurrentLives{ 3 };

	};

}