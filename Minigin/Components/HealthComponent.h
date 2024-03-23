#pragma once
#include "Base/Component.h"
#include "Base/GameObject.h"

namespace amu
{

	class HealthComponent final : public Component
	{
	public:
		explicit HealthComponent(GameObject * ownerObjectPtr, int health);
		virtual ~HealthComponent() override = default;

		HealthComponent(const HealthComponent&) = delete;
		HealthComponent& operator= (const HealthComponent&) = delete;
		HealthComponent(HealthComponent&&) = delete;
		HealthComponent& operator= (const HealthComponent&&) = delete;

		void ReduceHealth(int value);
		void IncreaseHealth(int value);
	private:
		const int m_MaxHealth{ 2 };
		int m_CurrentHealth{ 2 };

		const int m_MaxLives{ 3 };
		int m_CurrentLives{ 3 };
	};

}