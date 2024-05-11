#pragma once
#include <string>

#include "Component.h"
#include "TextComponent.h"

namespace pacman
{

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject * ownerObjectPtr);
		virtual ~FPSComponent() override = default;
	
		FPSComponent(FPSComponent const& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(FPSComponent const& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	
		void Update() override;
	private:
		TextComponent* m_TextPtr{ nullptr };

		std::string m_FPSCountToDisplay{ "" };
	
		int m_TicksPassed{ 0 };
	
		const double m_MaxRefreshTime{ 0.2 };
		double m_CurrentRefreshTime{ 0.0 };

		double m_PreviousFPSCount{ 0 };

	};
}
