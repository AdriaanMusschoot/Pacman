#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "TextComponent.h"

namespace amu
{

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject * ownerObjectPtr);
		~FPSComponent() override = default;
	
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	
		void Update() override;
	private:
		std::string m_FPSCountToDisplay = "";
	
		int m_TicksPassed = 0;
	
		const double m_MaxRefreshTime = 0.2;
		double m_CurrentRefreshTime = 0.0;

		double m_PreviousFPSCount = 0;

		TextComponent* m_TextPtr = nullptr;
	};
}